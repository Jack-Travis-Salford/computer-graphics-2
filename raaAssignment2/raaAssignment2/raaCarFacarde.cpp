
#include <windows.h>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Shape>
#include <osg/Material>
#include <osg/Switch>
#include <cmath>
#include "raaTrafficSystem.h"
#include "raaFinder.h"
#include "raaCarFacarde.h"
#include "raaAnimationPathCallback.h"
#include <iostream>

raaCarFacarde::raaCarFacarde(osg::Node* pWorldRoot, osg::Node* pPart, osg::AnimationPath* ap, double dSpeed, double maxAcc): raaAnimatedFacarde(pPart, ap, dSpeed, maxAcc)
{
	raaTrafficSystem::addTarget(this); // adds the car to the traffic system (static class) which holds a reord of all the dynamic parts in the system
    chosenOne = false;
    lastPos = { 0.0f,0.0f,0.0f };
    lastVelocity = { 0.1f,0.1f,0.0f };
}
raaCarFacarde::raaCarFacarde(osg::Node* pWorldRoot, osg::Node* pPart, osg::AnimationPath* ap, double dSpeed, double maxAcc, bool theChosenOne) : raaAnimatedFacarde(pPart, ap, dSpeed, maxAcc)
{
    raaTrafficSystem::addTarget(this); // adds the car to the traffic system (static class) which holds a reord of all the dynamic parts in the system
    chosenOne = theChosenOne;
    lastPos = { 0.0f,0.0f,0.0f };
    lastVelocity = { 0.1f,0.1f,0.0f };
}

raaCarFacarde::~raaCarFacarde()
{
	raaTrafficSystem::removeTarget(this); // removes the car from the traffic system (static class) which holds a reord of all the dynamic parts in the system
}

void raaCarFacarde::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
   
    bool obstructionFound = false;
    float closestFoundObstruction = 0.0f;
    raaCollisionTarget* obstructionCollider = this;


    float rotationDegreeBounds = 60;
    float rot = getObjRotation() +rotationDegreeBounds;

    float minRotBound = rot - rotationDegreeBounds;
    float maxRotBound = rot + rotationDegreeBounds;
    auto thisPos = this->getWorldDetectionPoint();
    if (thisPos != lastPos)
    {
        lastVelocity = thisPos - lastPos;
    }
    
    for (auto it = raaTrafficSystem::colliders().begin(); it != raaTrafficSystem::colliders().end(); it++)

    {      
        auto collider = *it;

        if (collider == this) //cannot collide with itself
        {
            continue;
        }

        osg::Vec3 colliderPos = collider->getWorldDetectionPoint();
        auto vecDist = colliderPos - thisPos;
        float absDist = sqrt((vecDist.x() * vecDist.x())+(vecDist.y()*vecDist.y()));
        float absDistTest = sqrt((colliderPos.x() * thisPos.x()) + (colliderPos.y() * thisPos.y()));

        if (absDist < 501)
        {
            float targetRot = collider->getObjRotation() + rotationDegreeBounds;
            if (targetRot >= 360)
            {
                targetRot -= 360;
            }
        

            if (targetRot >= minRotBound && targetRot <= maxRotBound )
            {
                float dotValue = (lastVelocity * (colliderPos - thisPos));
                

                if (dotValue>=0)
                {
                    if (obstructionFound)
                    {
                        if (absDist < closestFoundObstruction)
                        {
                            closestFoundObstruction = absDist;
                            obstructionCollider = collider;
                        }
                    }
                    else 
                    {
                        obstructionFound = true;
                        closestFoundObstruction = absDist;
                        obstructionCollider = collider;
                    }
                }                   
            }
        }
    }
    
    if (obstructionFound)
    {
        //Decrease speed until at obstructioncollider speed
        //setCurrentSpeed(obstructionCollider->getCurrentSpeed());

        double maxDist = ((double)closestFoundObstruction - 100.0);
        if (maxDist <= 0)
        {
            maxDist = 0.00001f;
        }
        setObstructionAheadDistance(maxDist, obstructionCollider->getCurrentSpeed());
    }
    if (!obstructionFound)
    {
        //accelerate 
        setObstructionAhead(false);
    }

    //Distance between Car and Traffic light
    if ((obstructionFound && !obstructionCollider->isHandlingTrafficLight) || !obstructionFound)
    {
        //If a traffic light has focus it until it gets too close
        //If traffic light is passed, remove focus when 400 units away
        //Else, check for traffic lights
        if (isHandlingTrafficLight)
        {
            osg::Vec3 colliderPos = obstructingTrafficLight->getWorldDetectionPoint();
            auto vecDist = colliderPos - thisPos;
            float absDist = sqrt((vecDist.x() * vecDist.x()) + (vecDist.y() * vecDist.y()));
            //printf("%f\n", absDist);
            if (absDist < 150)
            {
                //printf("Traffic Light passed\n");
                isHandlingTrafficLight = false;
            }
            else if (absDist > 450) {
                isHandlingTrafficLight = false;
                isInTrafficLightRange = false;
                //printf("Traffic Light lost focus: case 1\n");
            }
            else { //In range: Handle
                int status = obstructingTrafficLight->getLightStatus();
                if (status != 2)
                {
                    float dist = absDist - 150;
                    if (dist <= 0)
                    {
                        dist = 0.00001f;
                    }
                    setObstructionAheadDistance(dist, 0);
                }
                else if(!obstructionFound) {
                    setObstructionAhead(false);
                }
            }


        }
        else if (isInTrafficLightRange) {
            osg::Vec3 colliderPos = obstructingTrafficLight->getWorldDetectionPoint();
            auto vecDist = colliderPos - thisPos;
            float absDist = sqrt((vecDist.x() * vecDist.x()) + (vecDist.y() * vecDist.y()));
             if (absDist > 800) 
             {
                isHandlingTrafficLight = false;
                isInTrafficLightRange = false;
                //printf("Traffic Light lost focus: case 2\n");
             }
        }
        else 
        {
            for (auto it = raaTrafficSystem::trafficColliders().begin(); it != raaTrafficSystem::trafficColliders().end(); it++) //traffic light logic
            {
                //rot -= rotationDegreeBounds;
                //rotationDegreeBounds = 15;
                //rot += rotationDegreeBounds;
                auto trafficLight = *it;

                osg::Vec3 colliderPos = trafficLight->getWorldDetectionPoint();
                auto vecDist = colliderPos - thisPos;

                float absDist = sqrt((vecDist.x() * vecDist.x()) + (vecDist.y() * vecDist.y()));
                //printf("%f\n", absDist);
                if (absDist < 401)
                {
                    float targetRot = trafficLight->getObjRotation() + rotationDegreeBounds;
                    if (targetRot >= minRotBound && targetRot <= maxRotBound) {
                        obstructingTrafficLight = trafficLight;
                        isHandlingTrafficLight = true;
                        isInTrafficLightRange = true;
                        //printf("Traffic Light found\n");
                        //printf(trafficLight.)
                        break;
                    }
                }
            }
        }
    }


    


    lastPos = thisPos;
    raaAnimationPathCallback::operator()(node, nv);

}

float raaCarFacarde::getObjRotation() 
{
    osg::Matrixd worldMat = m_pRoot->getWorldMatrices()[0];
    osg::Quat quatRot = worldMat.getRotate();
    double w = quatRot.w();
    double x = quatRot.x();
    double y = quatRot.y();
    double z = quatRot.z();
    
    double siny_cosp = 2 * (w * z + x * y);
    double cosy_cosp = 1 - 2 * (y * y + z * z);
    double rot = std::atan2(siny_cosp, cosy_cosp);


    return abs((rot * (180/ 3.14159265f)) - 90.0f);
    //return rot;
}

osg::Vec3f raaCarFacarde::getWorldDetectionPoint()
{
	//return osg::Vec3(); // should return the world position of the detection point for this subtree
    
	return this->raaFacarde::m_pRoot->getBound().center(); // should return the world position of the detection point for this subtree
}

osg::Vec3f raaCarFacarde::getWorldCollisionPoint()
{
	return osg::Vec3(); // should return the world position of the collision point for this subtree
}

double raaCarFacarde::getCurrentSpeed() {

    return currentSpeed;
}

int raaCarFacarde::getLightStatus() {
    return -1;
}


