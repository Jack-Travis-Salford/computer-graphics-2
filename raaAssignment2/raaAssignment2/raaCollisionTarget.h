#pragma once

#include <windows.h>
#include <osg/Vec3f>
#include <osg/Transform>

// a pure virtual base class (interface) to provide support for collidable objects

class raaCollisionTarget
{
public:
	virtual osg::Vec3f getWorldDetectionPoint()=0;
	virtual osg::Vec3f getWorldCollisionPoint()=0;
	virtual float getObjRotation() = 0;
	virtual double getCurrentSpeed() = 0;
	virtual int getLightStatus() = 0;
	bool isHandlingTrafficLight = 0;
};

