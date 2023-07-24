#include <windows.h>
#include <iostream>
#include <math.h>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osg/Texture2D>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osg/AnimationPath>
#include <osg/Matrix>
#include <osgParticle/PrecipitationEffect>
#include <osgGA/NodeTrackerManipulator>
#include <osg/Node>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include "raaInputController.h"
#include "raaAssetLibrary.h"
#include "raaFacarde.h"
#include "raaSwitchActivator.h"
#include "raaRoadTileFacarde.h"
#include "raaAnimationPointFinder.h"
#include "raaAnimatedFacarde.h"
#include "raaCarFacarde.h"
#include "raaTrafficSystem.h"
#include "TrafficLightControl.h"
#include "TrafficLightFacarde.h"
#include "PathGenerator.h"
#include <osg/Fog>
#include <osgDB/ReadFile>


typedef std::vector<raaAnimationPointFinder>raaAnimationPointFinders;
osg::Group* g_pRoot = 0; // root of the sg
float g_fTileSize = 472.441f; // width/depth of the standard road tiles
std::string g_sDataPath = "../../Data/";

enum raaRoadTileType
{
	Normal,
	LitTJunction,
	LitXJunction,
};

void addRoadTile(std::string sAssetName, std::string sPartName, int xUnit, int yUnit, float fRot, osg::Group* pParent)
{
	raaFacarde* pFacarde = new raaRoadTileFacarde(raaAssetLibrary::getNamedAsset(sAssetName, sPartName), osg::Vec3(g_fTileSize * xUnit, g_fTileSize * yUnit, 0.0f), fRot);
	pParent->addChild(pFacarde->root());
}

TrafficLightFacarde* addTrafficLight(std::string sPartName, osg::Vec3 assetPos, float fRot, float fScale, osg::Group* pParent)
{
	TrafficLightFacarde* tlFacard = new TrafficLightFacarde(raaAssetLibrary::getClonedAsset("trafficLight", sPartName), assetPos, fRot, fScale);

	
	pParent->addChild(tlFacard->root());
	return tlFacard;
}

osg::Node* buildAnimatedVehicleAsset()
{
	osg::Group* pGroup = new osg::Group();

	osg::Geode* pGB = new osg::Geode();
	osg::ShapeDrawable* pGeomB = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 100.0f, 60.0f, 40.0f));
	osg::Material* pMat = new osg::Material();
	pMat->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(0.3f, 0.3f, 0.1f, 1.0f));
	pMat->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(0.8f, 0.8f, 0.3f, 1.0f));
	pMat->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f, 1.0f, 0.6f, 1.0f));

	pGroup->addChild(pGB);
	pGB->addDrawable(pGeomB);

	pGB->getOrCreateStateSet()->setAttribute(pMat, osg::StateAttribute::ON || osg::StateAttribute::OVERRIDE);
	pGB->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE), osg::StateAttribute::ON || osg::StateAttribute::OVERRIDE);

	return pGroup;
}



osg::AnimationPath* createAnimationPath(raaAnimationPointFinders apfs, osg::Group* pRoadGroup)
{
	float fAnimTime = 0.0f;
	osg::AnimationPath* ap = new osg::AnimationPath();

	for (int i = 0; i < apfs.size(); i++)
	{
		float fDistance = 0.0f;
		osg::Vec3 vs;
		osg::Vec3 ve;

		vs.set(apfs[i].translation().x(), apfs[i].translation().y(), apfs[i].translation().z());

		if (i == apfs.size() - 1)
			ve.set(apfs[0].translation().x(), apfs[0].translation().y(), apfs[0].translation().z());
		else
			ve.set(apfs[i + 1].translation().x(), apfs[i + 1].translation().y(), apfs[i + 1].translation().z());

		float fXSqr = pow((ve.x() - vs.x()), 2);
		float fYSqr = pow((ve.y() - vs.y()), 2);
		float fZSqr = pow((ve.z() - vs.z()), 2);

		fDistance = sqrt(fXSqr + fYSqr);
		ap->insert(fAnimTime, osg::AnimationPath::ControlPoint(apfs[i].translation(), apfs[i].rotation()));
		fAnimTime += (fDistance / 10.0f);
	}

	return ap;
}

void buildRoad(osg::Group* pRoadGroup)
{
	addRoadTile("roadStraight", "tile0", 0, 0, 0.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile1", 1, 0, 90.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile2", 1, 1, 90.0f, pRoadGroup);
	addRoadTile("roadTJunction", "tile3", 1, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile4", 1, 3, 90.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile5", 1, 4, 90.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile6", 1, 5, 180.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile7", 0, 5, 180.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile8", -1, 5, 180.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile9", -2, 5, 180.0f, pRoadGroup);
	addRoadTile("roadTJunction", "tile10", -3, 5, 180.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile11", -3, 6, 90.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile12", -3, 7, 180.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile13", -4, 7, 180.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile14", -5, 7, 180.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile15", -6, 7, 270.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile16", -6, 6, 90.0f, pRoadGroup);
	addRoadTile("roadTJunction", "tile17", -6, 5, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile18", -7, 5, 180.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile19", -8, 5, 180.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile20", -9, 5, 270.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile21", -9, 4, 270.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile22", -9, 3, 270.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile23", -9, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile24", -8, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile25", -7, 2, 0.0f, pRoadGroup);
	addRoadTile("roadXJunction", "tile26", -6,2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile27", -6, 1, 90.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile28", -6, 0, 90.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile29", -6, -1, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile30", -5, -1, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile31", -4, -1, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile32", -3, -1, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile33", -2, -1, 0.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile34", -1, -1, 90.0f, pRoadGroup);
	addRoadTile("roadTJunction", "tile35", -1, 0, 90.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile36", -2, 0, 0.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile37", -2, 1, 180.0f, pRoadGroup);
	addRoadTile("roadCurve", "tile38", -3, 1, 0.0f, pRoadGroup);
	addRoadTile("roadXJunction", "tile39", -3, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile40", -3, 3, 90.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile41", -3, 4, 90.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile42", -2, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile43", -1, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile44", -0, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile45", -4, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile46", -5, 2, 0.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile47", -6, 3, 90.0f, pRoadGroup);
	addRoadTile("roadStraight", "tile48", -6, 4, 90.0f, pRoadGroup);
}

void BuildTrafficLights(osg::Group* pTlGroup) 
{
	TrafficLightFacarde* tf1 = addTrafficLight("trafficLight0", osg::Vec3(-250.0f, -150.0f, 0.0f), 90.0f, .08f, pTlGroup);
	TrafficLightFacarde* tf2 = addTrafficLight("trafficLight1", osg::Vec3(-625.0f, -205.0f, 0.0f), 0.0f, 0.08f, pTlGroup);
	TrafficLightFacarde* tf3 = addTrafficLight("trafficLight2", osg::Vec3(-690.0f, 150.0f, 0.0f), 270.0f, 0.08f, pTlGroup);

	TrafficLightControl* pJunction = new TrafficLightControl(raaAssetLibrary::getNamedAsset("roadTJunction", "lightController1"), osg::Vec3(0.0f, -1000.0f, 0.0f), 0.0f, 0.0f, false);
	pTlGroup->addChild(pJunction->root());
	pJunction->addTrafficLight(tf1);
	pJunction->addTrafficLight(tf2);
	pJunction->addTrafficLight(tf3);


	TrafficLightFacarde* tf4 = addTrafficLight("trafficLight3", osg::Vec3(-2610.0f, 800.0f, 0.0f), 90.0f, .08f, pTlGroup);
	TrafficLightFacarde* tf5 = addTrafficLight("trafficLight4", osg::Vec3(-2980.0f, 740.0f, 0.0f), 0.0f, .08f, pTlGroup);
	TrafficLightFacarde* tf6 = addTrafficLight("trafficLight5", osg::Vec3(-2700.0f, 1150.0f, 0.0f), 180.0f, .08f, pTlGroup);
	TrafficLightFacarde* tf7 = addTrafficLight("trafficLight6", osg::Vec3(-3050.0f, 1080.0f, 0.0f), 270.0f, .08f, pTlGroup);
	TrafficLightControl* pJunction1 = new TrafficLightControl(raaAssetLibrary::getNamedAsset("roadTJunction", "lightController2"), osg::Vec3(0.0f, -1000.0f, 0.0f), 0.0f, 0.0f, false);
	pTlGroup->addChild(pJunction1->root());
	pJunction1->addTrafficLight(tf4);
	pJunction1->addTrafficLight(tf5);
	pJunction1->addTrafficLight(tf6);
	pJunction1->addTrafficLight(tf7);

	TrafficLightFacarde* tf8 = addTrafficLight("trafficLight7", osg::Vec3(-1270.0f, 2590.0f, 0.0f), 180.0f, .08f, pTlGroup);
	TrafficLightFacarde* tf9 = addTrafficLight("trafficLight8", osg::Vec3(-1550.0f, 2140.0f, 0.0f), 0.0f, .08f, pTlGroup);
	TrafficLightFacarde* tf10 = addTrafficLight("trafficLight9", osg::Vec3(-1180.0f, 2220.0f, 0.0f), 90.0f, .08f, pTlGroup);
	TrafficLightControl* pJunction2 = new TrafficLightControl(raaAssetLibrary::getNamedAsset("roadTJunction", "lightController3"), osg::Vec3(0.0f, -1000.0f, 0.0f), 0.0f, 0.0f, false);
	pTlGroup->addChild(pJunction2->root());
	pJunction2->addTrafficLight(tf8);
	pJunction2->addTrafficLight(tf9);
	pJunction2->addTrafficLight(tf10);


	TrafficLightFacarde* tf11 = addTrafficLight("trafficLight10", osg::Vec3(-4110.0f, 1800.0f, 0.0f), 180.0f, .08f, pTlGroup);
    TrafficLightFacarde* tf12 = addTrafficLight("trafficLight9", osg::Vec3(-4400.0f, 1600.0f, 0.0f), 0.0f, .08f, pTlGroup);
	TrafficLightControl* pJunction3 = new TrafficLightControl(raaAssetLibrary::getNamedAsset("roadTJunction", "lightController4"), osg::Vec3(0.0f, -1000.0f, 0.0f), 0.0f, 0.0f, true);
	pTlGroup->addChild(pJunction3->root());
	pJunction3->addTrafficLight(tf11);
	pJunction3->addTrafficLight(tf12);
}
void createCarOne(osg::Group* pRoadGroup)
{
	raaAnimationPointFinders apfs;
	osg::AnimationPath* ap = new osg::AnimationPath();
	apfs.push_back(raaAnimationPointFinder("tile0", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile0", 3, pRoadGroup));
	PathGenerator* pg = new PathGenerator(0, 1, apfs, pRoadGroup);
	pg->tile35PathDecider(0);
	ap = createAnimationPath(pg->createPath(), pRoadGroup);
	// NOTE: you will need to extend or develop the car facarde to manage the animmation speed and events

	raaCarFacarde* pCar = new raaCarFacarde(g_pRoot, raaAssetLibrary::getNamedAsset("vehicle", "car1"), ap, 100.0, 10);
	g_pRoot->addChild(pCar->root());
}

void createCarTwo(osg::Group* pRoadGroup)
{
	raaAnimationPointFinders apfs;
	osg::AnimationPath* ap = new osg::AnimationPath();
	apfs.push_back(raaAnimationPointFinder("tile5", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile5", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile6", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile6", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile6", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile7", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile7", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile8", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile8", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile9", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile9", 0, pRoadGroup));
	PathGenerator* pg = new PathGenerator(5, 4, apfs, pRoadGroup);
	pg->tile10PathDecider(9);
	ap = createAnimationPath(pg->createPath(), pRoadGroup);
	// NOTE: you will need to extend or develop the car facarde to manage the animmation speed and events
	raaCarFacarde* pCar = new raaCarFacarde(g_pRoot, raaAssetLibrary::getNamedAsset("vehicle", "car2"), ap, 125.0, 12.5);
	g_pRoot->addChild(pCar->root());
}
void createCarThree(osg::Group* pRoadGroup)
{
	raaAnimationPointFinders apfs;
	osg::AnimationPath* ap = new osg::AnimationPath();
	apfs.push_back(raaAnimationPointFinder("tile19", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile19", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile18", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile18", 3, pRoadGroup));
	PathGenerator* pg = new PathGenerator(19, 20, apfs, pRoadGroup);
	pg->tile17PathDecider(18);
	ap = createAnimationPath(pg->createPath(), pRoadGroup);
	// NOTE: you will need to extend or develop the car facarde to manage the animmation speed and events
	raaCarFacarde* pCar = new raaCarFacarde(g_pRoot, raaAssetLibrary::getNamedAsset("vehicle", "car3"), ap, 75.0, 7.5);
	g_pRoot->addChild(pCar->root());
}

void createCarFour(osg::Group* pRoadGroup)
{
	raaAnimationPointFinders apfs;
	osg::AnimationPath* ap = new osg::AnimationPath();
	apfs.push_back(raaAnimationPointFinder("tile30", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile30", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile29", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile29", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile29", 5, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile28", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile28", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile27", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile27", 0, pRoadGroup));
	PathGenerator* pg = new PathGenerator(30, 31, apfs, pRoadGroup);
	pg->tile26PathDecider(27);
	ap = createAnimationPath(pg->createPath(), pRoadGroup);
	// NOTE: you will need to extend or develop the car facarde to manage the animmation speed and events
	raaCarFacarde* pCar = new raaCarFacarde(g_pRoot, raaAssetLibrary::getNamedAsset("vehicle", "car4"), ap, 150.0, 15);
	g_pRoot->addChild(pCar->root());
}

void createCarFive(osg::Group* pRoadGroup)
{
	raaAnimationPointFinders apfs;
	osg::AnimationPath* ap = new osg::AnimationPath();
	apfs.push_back(raaAnimationPointFinder("tile48", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile48", 0, pRoadGroup));
	PathGenerator* pg = new PathGenerator(48, 47, apfs, pRoadGroup);
	pg->tile17PathDecider(48);
	ap = createAnimationPath(pg->createPath(), pRoadGroup);
	// NOTE: you will need to extend or develop the car facarde to manage the animmation speed and events
	raaCarFacarde* pCar = new raaCarFacarde(g_pRoot, raaAssetLibrary::getNamedAsset("vehicle", "car5"), ap, 130.0, 20);
	g_pRoot->addChild(pCar->root());
}


int main(int argc, char** argv)
{
	raaAssetLibrary::start();
	raaTrafficSystem::start();

	osgViewer::Viewer viewer;

	for (int i = 0; i < argc; i++)
	{
		if (std::string(argv[i]) == "-d") g_sDataPath = argv[++i];
	}

	// the root of the scene - use for rendering
	g_pRoot = new osg::Group();
	g_pRoot->ref();

	// build asset library - instances or clones of parts can be created from this
	raaAssetLibrary::loadAsset("roadStraight", g_sDataPath + "roadStraight.osgb");
	raaAssetLibrary::loadAsset("roadCurve", g_sDataPath + "roadCurve.osgb");
	raaAssetLibrary::loadAsset("roadTJunction", g_sDataPath + "roadTJunction.osgb");
	raaAssetLibrary::loadAsset("roadXJunction", g_sDataPath + "roadXJunction.osgb");
	raaAssetLibrary::loadAsset("trafficLight", g_sDataPath + "raaTrafficLight.osgb");

	
	raaAssetLibrary::insertAsset("vehicle", buildAnimatedVehicleAsset());

	// add a group node to the scene to hold the road sub-tree
	osg::Group* pRoadGroup = new osg::Group();
	g_pRoot->addChild(pRoadGroup);
	// add a group node to the scene to hold the traffic light sub-tree
	osg::Group* trafficLightGroup = new osg::Group();
	g_pRoot->addChild(trafficLightGroup);

	printf("Building road...");
	// Create road
	buildRoad(pRoadGroup);
	printf("Complete\n");

	printf("Building Traffic Lights...");
	//Create traffic lights
	BuildTrafficLights(trafficLightGroup);
	printf("Complete\n");


	
	// Add cars
	printf("Creating path for car 1...");
	createCarOne(pRoadGroup);
	printf("Complete\n");
	printf("Creating path for car 2...");
	createCarTwo(pRoadGroup);
	printf("Complete\n");
	printf("Creating path for car 3...");
	createCarThree(pRoadGroup);
	printf("Complete\n");
	printf("Creating path for car 4...");
	createCarFour(pRoadGroup);
	printf("Complete\n");
	printf("Creating path for car 5...");
	createCarFive(pRoadGroup);
	printf("Complete\n");


	osg::Group* pRainGroup = new osg::Group();
	g_pRoot->addChild(pRainGroup);
	osg::ref_ptr<osgParticle::PrecipitationEffect> rainNode = new osgParticle::PrecipitationEffect;
	rainNode->rain(0.3);
	pRainGroup->addChild(rainNode.get());


	osg::Group* pDecoGroup = new osg::Group();
	g_pRoot->addChild(pDecoGroup);
	osg::ref_ptr<osg::Geode> terrain = new osg::Geode;
	terrain->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(-1800,1500,-20),6000,5500,10)));
	osg::ref_ptr<osg::Texture2D> grassText = new osg::Texture2D(osgDB::readImageFile(g_sDataPath + "grassTex.jpg"));
	terrain->getOrCreateStateSet()-> setTextureAttributeAndModes(0, grassText.get());
	pDecoGroup->addChild(terrain);


	osg::Group* pFogGroup = new osg::Group();
	g_pRoot->addChild(pFogGroup);

	osg::Fog* fog = new osg::Fog();
	fog->setMode(osg::Fog::LINEAR);
	fog->setColor(osg::Vec4(.33, .34, .34, .1));
	fog->setStart(1000);
	fog->setEnd(22000);

	osg::StateSet* stateSet = g_pRoot->getOrCreateStateSet();
	stateSet->setAttributeAndModes(fog, osg::StateAttribute::ON);
	stateSet->setMode(GL_FOG, osg::StateAttribute::ON);


	// osg setup stuff
	osg::GraphicsContext::Traits* pTraits = new osg::GraphicsContext::Traits();
	pTraits->x = 20;
	pTraits->y = 20;
	pTraits->width = 600;
	pTraits->height = 480;
	pTraits->windowDecoration = true;
	pTraits->doubleBuffer = true;
	pTraits->sharedContext = 0;


	osg::GraphicsContext* pGC = osg::GraphicsContext::createGraphicsContext(pTraits);
	osgGA::KeySwitchMatrixManipulator* pKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator();
	pKeyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator());
	pKeyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
	pKeyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());




	viewer.setCameraManipulator(pKeyswitchManipulator);
	osg::Camera* pCamera = viewer.getCamera();
	pCamera->setGraphicsContext(pGC);
	pCamera->setViewport(new osg::Viewport(0, 0, pTraits->width, pTraits->height));

	// add own event handler - this currently switches on an off the animation points
	viewer.addEventHandler(new raaInputController(g_pRoot, pRainGroup, pFogGroup));

	// add the state manipulator
	viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));

	// add the thread model handler
	viewer.addEventHandler(new osgViewer::ThreadingHandler);

	// add the window size toggle handler
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);

	// add the stats handler
	viewer.addEventHandler(new osgViewer::StatsHandler);

	// add the record camera path handler
	viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);

	// add the LOD Scale handler
	viewer.addEventHandler(new osgViewer::LODScaleHandler);

	// add the screen capture handler
	viewer.addEventHandler(new osgViewer::ScreenCaptureHandler);


	//osgUtil::Optimizer optimizer;
	//optimizer.optimize(g_pRoot);

	// set the scene to render
	viewer.setSceneData(g_pRoot);

	viewer.realize();

	
	

	return viewer.run();
}



