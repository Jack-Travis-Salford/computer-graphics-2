#include "ManualTrafficControllerHandler.h"
#include <list>
#include "raaTrafficSystem.h"

//lstManualLightControllers ManualTrafficControllerHandler::manualListControllers;

/*bool ManualTrafficControllerHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (ea.getEventType() == osgGA::GUIEventAdapter::KEYDOWN)
	{
		switch (ea.getKey())
		{
		case 'p':
		case 'P':
			printf("P Pressed");
			return true;
		return true;
		}
	}

	return false;
}*/

/*void ManualTrafficControllerHandler::start()
{
	manualListControllers.clear();
}

void ManualTrafficControllerHandler::end()
{
	manualListControllers.clear();
}*/

void ManualTrafficControllerHandler::addTrafficController(TrafficLightControl* tlc)
{
}

ManualTrafficControllerHandler::~ManualTrafficControllerHandler()
{
}
