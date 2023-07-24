#pragma once

#include <windows.h>
#include <osg/switch>
#include <list>
#include <cmath>
#include "raaAnimatedFacarde.h"
#include "raaCollisionTarget.h"


// a facarde for the cars in the scene - note this also inherets from collision target to provide support for collision management

class raaCarFacarde: public raaAnimatedFacarde, public raaCollisionTarget
{
public:
	raaCarFacarde(osg::Node* pWorldRoot, osg::Node* pPart, osg::AnimationPath* ap, double dSpeed, double maxAcc);
	raaCarFacarde(osg::Node* pWorldRoot, osg::Node* pPart, osg::AnimationPath* ap, double dSpeed, double maxAcc, bool theChosenOne);
	virtual ~raaCarFacarde();
	void operator()(osg::Node* node, osg::NodeVisitor* nv) override;
	

	virtual osg::Vec3f getWorldDetectionPoint(); // from raaCollisionTarget
	virtual osg::Vec3f getWorldCollisionPoint(); // from raaCollisionTarget
	virtual float getObjRotation();// from raaCollisionTarget
	virtual double getCurrentSpeed();// from raaCollisionTarget
	virtual int getLightStatus();// from raaCollisionTarget

	raaCollisionTarget* obstructingTrafficLight;
	bool isHandlingTrafficLight;
	bool isInTrafficLightRange;
protected:
	bool chosenOne;
	osg::Vec3 lastPos;
	osg::Vec3 lastVelocity;

};

