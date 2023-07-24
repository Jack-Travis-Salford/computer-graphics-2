#pragma once

#include <windows.h>
#include <osgGA/GUIEventHandler>
#include <list>


typedef std::list<class TrafficLightControl*> lstManualLightSystem;

// the basic input controller. You should extend and enhance this for your user input

class raaInputController: public osgGA::GUIEventHandler
{
public:
	virtual bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&);
	raaInputController(osg::Node* pWorldRoot, osg::Node* rainNode, osg::Node* fogNode);
	virtual ~raaInputController();
	static lstManualLightSystem manualLightSystems;
	static void addTarget(TrafficLightControl* pTarget);
protected:
	bool m_bShowAnimationPoints;
	bool m_bShowAnimationNames;
	bool m_bShowCollisionObjects;
	bool m_bShowAssetName;
	osg::Node* m_pWorldRoot;
	osg::Node* rainNode;
	osg::Node* fogNode;
};

