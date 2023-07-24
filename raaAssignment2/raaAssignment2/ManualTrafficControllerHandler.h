#pragma once

#include <list>
#include <osgGA/GUIEventHandler>
#include <windows.h>


typedef std::list<class TrafficLightControl*> lstManualLightControllers;

class ManualTrafficControllerHandler//: public osgGA::GUIEventHandler 
{
public:
	//virtual bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&);
	void addTrafficController(TrafficLightControl* tlc);
	lstManualLightControllers manualListControllers;
	virtual ~ManualTrafficControllerHandler();
};