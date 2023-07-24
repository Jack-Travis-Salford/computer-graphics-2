#include "TrafficLightControl.h"
#include "raaInputController.h"


TrafficLightControl::TrafficLightControl(osg::Node* pPart, osg::Vec3 vTrans, float fRot, float fScale, bool isManual) : raaNodeCallbackFacarde(pPart, vTrans, fRot, fScale)
{
	timeCount = 0;
	currentLightPos = 0;
	lightChangeSpeed[0] = 100; // Red
	lightChangeSpeed[1] = 100; //Red-Amber
	lightChangeSpeed[2] = 400; //Green
	lightChangeSpeed[3] = 100; //Yellow
	currentLight = 0;
	raaInputController::addTarget(this);
	manualJunction = isManual;	

	if (!manualJunction)
	{
		currentLightStage = 0;
	}
	else {
		currentLightStage = 2;
	}
}


void TrafficLightControl::operator() (osg::Node* node, osg::NodeVisitor* nv)
{

	if (m_lTrafficLights.size() == 0) { return; }

	if (!manualJunction) {
		if (timeCount == lightChangeSpeed[currentLightStage])
		{
			int iterator = 0;
			for (trafficLightList::iterator it = m_lTrafficLights.begin(); it != m_lTrafficLights.end(); it++)
			{
				if (currentLight == iterator)
				{
					changeTrafficLight(*it);
					break;
				}
				iterator++;
			}
			timeCount = 0;
		}
		timeCount++;
	}
	else if (currentLightStage != 2) {

		int framesForStage = lightChangeSpeed[currentLightStage];
		framesForStage *= (currentLightStage == 0) ? 4 : 1;
		
		if (timeCount == framesForStage)
		{
			for (trafficLightList::iterator it = m_lTrafficLights.begin(); it != m_lTrafficLights.end(); it++)
			{
				changeTrafficLight(*it);
			}
			timeCount = 0;
		}
		timeCount++;
	}
}

void TrafficLightControl::changeTrafficLight(TrafficLightFacarde* pTrafficLight)
{
	pTrafficLight->m_iTrafficLightStatus = (pTrafficLight->m_iTrafficLightStatus+1)%4;
	switch (pTrafficLight->m_iTrafficLightStatus)
	{
	case 0:
		pTrafficLight->setRedTrafficLight();
		if (!manualJunction)
		{
			currentLight = (currentLight + 1) % m_lTrafficLights.size();
		}
		currentLightStage = 0;
		break;
	case 1:
		pTrafficLight->setRedAmberTrafficLight();
		currentLightStage = 1;
		break;
	case 2:
		pTrafficLight->setGreenTrafficLight();
		currentLightStage = 2;
		break;
	case 3:
		pTrafficLight->setAmberTrafficLight();
		currentLightStage = 3;
		break;
	default:
		pTrafficLight->setRedTrafficLight();
		if (!manualJunction)
		{
			currentLight = (currentLight + 1) % m_lTrafficLights.size();
		}
		currentLightStage = 0;
		break;
	}
}

void TrafficLightControl::addTrafficLight(TrafficLightFacarde* pTrafficLight)
{
	m_lTrafficLights.push_back(pTrafficLight);
	if (manualJunction)
	{
		pTrafficLight->setGreenTrafficLight();
	}
}

void TrafficLightControl::manualTrigger() {
	if (manualJunction && currentLightStage == 2)
	{
		for (trafficLightList::iterator it = m_lTrafficLights.begin(); it != m_lTrafficLights.end(); it++)
		{
			changeTrafficLight(*it);
		}
	}
}
