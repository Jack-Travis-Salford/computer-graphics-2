#pragma once
#include "raaNodeCallBackFacarde.h"
#include "TrafficLightFacarde.h"
#include <list>
#include <iterator>

typedef std::list<TrafficLightFacarde*> trafficLightList;

class TrafficLightControl : public raaNodeCallbackFacarde
{
public:
	TrafficLightControl(osg::Node* pPart, osg::Vec3 vTrans, float fRot, float fScale, bool isManual);
	void operator() (osg::Node* node, osg::NodeVisitor* nv) override;
	void addTrafficLight(TrafficLightFacarde* pTrafficLight);
	void changeTrafficLight(TrafficLightFacarde* pTrafficLight);
	void manualTrigger();

protected:
	trafficLightList m_lTrafficLights;
	int lightChangeSpeed[4];
	int timeCount;
	int currentLightPos;
	int currentLight;
	int currentLightStage;
	bool manualJunction;
};

