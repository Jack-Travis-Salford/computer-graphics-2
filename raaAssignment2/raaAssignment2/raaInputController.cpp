#include "raaFacarde.h"
#include "raaSwitchActivator.h"
#include "raaAssetLibrary.h"
#include "raaInputController.h"
#include "TrafficLightControl.h"

/*
pTileIDS->setName("IDSwitch");
pAnimPointS->setName("AnimationPointSwitch");
pAnimIDS->setName("AnimationIDSwitch");
*/


lstManualLightSystem raaInputController::manualLightSystems;


bool raaInputController::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if(ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN)
	{
		switch(ea.getKey())
		{
		case 't':
		case 'T':
			raaFacarde::toggleNames(); // shows names of the facade objects			
			return true;
		case 'a':
		case 'A':
		{
			raaSwitchActivator a("AnimationPointSwitch", raaAssetLibrary::getAssetsRoot(), m_bShowAnimationPoints = !m_bShowAnimationPoints);
		}
			return true;
		case 'n':
		case 'N':
		{
			raaSwitchActivator n("AnimationIDSwitch", raaAssetLibrary::getAssetsRoot(), m_bShowAnimationNames = !m_bShowAnimationNames);
		}
			return true;
		case 'i':
		case 'I':
		{
			raaSwitchActivator i("IDSwitch", raaAssetLibrary::getAssetsRoot(), m_bShowAssetName = !m_bShowAssetName);
		}
		case 'p':
		case 'P':
		{
			if (manualLightSystems.size() != 0)
			{
				for (lstManualLightSystem::iterator it = manualLightSystems.begin(); it != manualLightSystems.end(); it++)
				{
					auto lightController = *it;
					lightController->manualTrigger();
				}
			}
			
			return true;
		}
		case 'r':
		case 'R':
		{

		}
			return true;
		}
		
	}

	return false;
}

raaInputController::raaInputController(osg::Node* pWorldRoot,osg::Node* rainNode, osg::Node* fogNode ) : m_pWorldRoot(pWorldRoot), m_bShowAnimationPoints(false), m_bShowAnimationNames(false), m_bShowCollisionObjects(false), m_bShowAssetName(false), fogNode(fogNode), rainNode(rainNode)
{
}


raaInputController::~raaInputController()
{
}

void raaInputController::addTarget(TrafficLightControl* pTarget)
{
	if (pTarget && std::find(manualLightSystems.begin(), manualLightSystems.end(), pTarget) == manualLightSystems.end()) manualLightSystems.push_back(pTarget);
}
