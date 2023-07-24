#include "PathGenerator.h"
#include "raaAnimationPointFinder.h"

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <random>
#include <chrono>
#include <osg/AnimationPath>
#include <osg/Matrix>
#include <osg/Material>
#include <osg/ShapeDrawable>
PathGenerator::PathGenerator(int startingTile, int lastTile, raaAnimationPointFinders apfs, osg::Node* pRoadGroup) : startingTile(startingTile), lastTile(lastTile), apfs(apfs), pRoadGroup(pRoadGroup)
{
	totalTiles = 0;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	rng.seed(seed);
}

raaAnimationPointFinders apfs; 
raaAnimationPointFinders PathGenerator::createPath()
{
	return apfs;
}

void PathGenerator::tile27Path()
{
	apfs.push_back(raaAnimationPointFinder("tile27", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile27", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile28", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile28", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile29", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile29", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile29", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile30", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile30", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile31", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile31", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile32", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile32", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile33", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile33", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile34", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile34", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile34", 2, pRoadGroup));
	totalTiles++;
	tile35PathDecider(34);
}
void PathGenerator::tile34Path() 
{
	apfs.push_back(raaAnimationPointFinder("tile34", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile34", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile34", 5, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile33", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile33", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile32", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile32", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile31", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile31", 3, pRoadGroup));
	totalTiles++;
	if (lastTile == 31 && startingTile == 30 && totalTiles >= 50)
	{
		return;
	}
	apfs.push_back(raaAnimationPointFinder("tile30", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile30", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile29", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile29", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile29", 5, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile28", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile28", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile27", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile27", 0, pRoadGroup));
	totalTiles++;
	tile26PathDecider(27);
}

void PathGenerator::tile0Path()
{
	apfs.push_back(raaAnimationPointFinder("tile0", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile0", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile1", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile1", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile1", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile2", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile2", 0, pRoadGroup));
	totalTiles++;
	tile3PathDecider(2);
}

void PathGenerator::tile2Path()
{
	apfs.push_back(raaAnimationPointFinder("tile2", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile2", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile1", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile1", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile1", 5, pRoadGroup));
	totalTiles++;
	if (lastTile == 1 && startingTile == 0 && totalTiles>=50)
	{
		return;
	}
	apfs.push_back(raaAnimationPointFinder("tile0", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile0", 3, pRoadGroup));
	totalTiles++;
	tile35PathDecider(0);
}

void PathGenerator::tile4Path()
{
	apfs.push_back(raaAnimationPointFinder("tile4", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile4", 0, pRoadGroup));
	totalTiles++;
	if (lastTile == 4 && startingTile == 5 && totalTiles >= 50)
	{
		return;
	}
	apfs.push_back(raaAnimationPointFinder("tile5", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile5", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile6", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile6", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile6", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile7", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile7", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile8", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile8", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile9", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile9", 0, pRoadGroup));
	totalTiles++;
	tile10PathDecider(9);
}

void PathGenerator::tile9Path()
{
	apfs.push_back(raaAnimationPointFinder("tile9", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile9", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile8", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile8", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile7", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile7", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile6", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile6", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile6", 5, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile5", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile5", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile4", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile4", 3, pRoadGroup));
	totalTiles++;
	tile3PathDecider(4);
}

void PathGenerator::tile11Path()
{
	apfs.push_back(raaAnimationPointFinder("tile11", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile11", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile12", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile12", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile12", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile13", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile13", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile14", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile14", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile15", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile15", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile15", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile16", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile16", 3, pRoadGroup));
	totalTiles++;
	tile17PathDecider(16);
}

void PathGenerator::tile16Path()
{
	apfs.push_back(raaAnimationPointFinder("tile16", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile16", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile15", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile15", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile15", 5, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile14", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile14", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile13", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile13", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile12", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile12", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile12", 5, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile11", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile11", 3, pRoadGroup));
	totalTiles++;
	tile10PathDecider(11);
}

void PathGenerator::tile18Path()
{
	apfs.push_back(raaAnimationPointFinder("tile18", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile18", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile19", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile19", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile20", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile20", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile20", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile21", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile21", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile22", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile22", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile23", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile23", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile23", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile24", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile24", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile25", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile25", 0, pRoadGroup));
	totalTiles++;
	tile26PathDecider(25);
}
void PathGenerator::tile25Path()
{
	apfs.push_back(raaAnimationPointFinder("tile25", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile25", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile24", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile24", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile23", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile23", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile23", 5, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile22", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile22", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile21", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile21", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile20", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile20", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile20", 5, pRoadGroup));
	totalTiles++;
	if (lastTile == 20 && startingTile == 19 && totalTiles >= 50)
	{
		return;
	}
	apfs.push_back(raaAnimationPointFinder("tile19", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile19", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile18", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile18", 3, pRoadGroup));
	totalTiles++;
	tile17PathDecider(18);

}
void PathGenerator::tile46Path()
{
	apfs.push_back(raaAnimationPointFinder("tile46", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile46", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile45", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile45", 0, pRoadGroup));
	totalTiles++;
	tile39PathDecider(45);
}
void PathGenerator::tile45Path()
{
	apfs.push_back(raaAnimationPointFinder("tile45", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile45", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile46", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile46", 3, pRoadGroup));
	totalTiles++;
	tile26PathDecider(46);
}
void PathGenerator::tile42Path()
{
	apfs.push_back(raaAnimationPointFinder("tile42", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile42", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile43", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile43", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile44", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile44", 0, pRoadGroup));
	totalTiles++;
	tile3PathDecider(44);
}
void PathGenerator::tile44Path()
{
	apfs.push_back(raaAnimationPointFinder("tile44", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile44", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile43", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile43", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile42", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile42", 3, pRoadGroup));
	totalTiles++;
	tile39PathDecider(42);
}

void PathGenerator::tile40Path()
{
	apfs.push_back(raaAnimationPointFinder("tile40", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile40", 0, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile41", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile41", 0, pRoadGroup));
	totalTiles++;
	tile10PathDecider(41);
}

void PathGenerator::tile41Path()
{
	apfs.push_back(raaAnimationPointFinder("tile41", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile41", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile40", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile40", 3, pRoadGroup));
	totalTiles++;
	tile39PathDecider(40);
}

void PathGenerator::tile38Path()
{
	apfs.push_back(raaAnimationPointFinder("tile38", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile38", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile38", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile37", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile37", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile37", 5, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile36", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile36", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile36", 2, pRoadGroup));
	totalTiles++;
	tile35PathDecider(36);
}

void PathGenerator::tile36Path()
{
	apfs.push_back(raaAnimationPointFinder("tile36", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile36", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile36", 5, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile37", 0, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile37", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile37", 2, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile38", 3, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile38", 4, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile38", 5, pRoadGroup));
	totalTiles++;
	tile39PathDecider(38);
}

void PathGenerator::tile48Path()
{
	apfs.push_back(raaAnimationPointFinder("tile48", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile48", 3, pRoadGroup));
	totalTiles++;
	apfs.push_back(raaAnimationPointFinder("tile47", 1, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile47", 3, pRoadGroup));
	totalTiles++;
	tile26PathDecider(47);
}

void PathGenerator::tile47Path()
{
	apfs.push_back(raaAnimationPointFinder("tile47", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile47", 0, pRoadGroup));
	totalTiles++;
	if (lastTile == 47 && startingTile == 48 && totalTiles >= 50)
	{
		return;
	}
	apfs.push_back(raaAnimationPointFinder("tile48", 2, pRoadGroup));
	apfs.push_back(raaAnimationPointFinder("tile48", 0, pRoadGroup));
	totalTiles++;
	tile17PathDecider(48);
}

void PathGenerator::tile26PathDecider(int comingFromTile)
{
	totalTiles++;
	int choice = rng.operator()() % 3;
	switch (comingFromTile)
	{
	case 27:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile26", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 9, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 7, pRoadGroup));
			tile25Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile26", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 15, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 10, pRoadGroup));
			tile46Path();
			break;
		case 2:
			apfs.push_back(raaAnimationPointFinder("tile26", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 2, pRoadGroup));
			tile47Path();
			break;
		default:
			printf("Error: tile 26, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 25:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile26", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 1, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 2, pRoadGroup));
			tile47Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile26", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 10, pRoadGroup));
			tile46Path();
			break;
		case 2:
			apfs.push_back(raaAnimationPointFinder("tile26", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 3, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 4, pRoadGroup));
			tile27Path();
			break;
		default:
			printf("Error: tile 26, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 47:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile26", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 14, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 10, pRoadGroup));
			tile46Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile26", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 4, pRoadGroup));
			tile27Path();
			break;
		case 2:
			apfs.push_back(raaAnimationPointFinder("tile26", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 6, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 7, pRoadGroup));
			tile25Path();
			break;
		default:
			printf("Error: tile 26, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 46:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile26", 11, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 12, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 4, pRoadGroup));
			tile27Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile26", 11, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 7, pRoadGroup));
			tile25Path();
			break;
		case 2:
			apfs.push_back(raaAnimationPointFinder("tile26", 11, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 13, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile26", 2, pRoadGroup));
			tile47Path();
			break;
		default:
			printf("Error: tile 26, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	default:
		printf("Error: Case not found for tile 26. Passed val:%i", comingFromTile);
		break;
	}
}

void PathGenerator::tile39PathDecider(int comingFromTile)
{
	totalTiles++;
	int choice = rng.operator()() % 3;


	switch (comingFromTile)
	{
	case 38:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile39", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 9, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 7, pRoadGroup));
			tile45Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile39", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 15, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 10, pRoadGroup));
			tile42Path();
			break;
		case 2:
			apfs.push_back(raaAnimationPointFinder("tile39", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 2, pRoadGroup));
			tile40Path();
			break;
		default:
			printf("Error: tile 39, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 45:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile39", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 1, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 2, pRoadGroup));
			tile40Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile39", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 10, pRoadGroup));
			tile42Path();
			break;
		case 2:
			apfs.push_back(raaAnimationPointFinder("tile39", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 3, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 4, pRoadGroup));
			tile38Path();
			break;
		default:
			printf("Error: tile 39, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 40:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile39", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 14, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 10, pRoadGroup));
			tile42Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile39", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 4, pRoadGroup));
			tile38Path();
			break;
		case 2:
			apfs.push_back(raaAnimationPointFinder("tile39", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 6, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 7, pRoadGroup));
			tile45Path();
			break;
		default:
			printf("Error: tile 39, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 42:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile39", 11, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 12, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 4, pRoadGroup));
			tile38Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile39", 11, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 7, pRoadGroup));
			tile45Path();
			break;
		case 2:
			apfs.push_back(raaAnimationPointFinder("tile39", 11, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 13, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile39", 2, pRoadGroup));
			tile40Path();
			break;
		default:
			printf("Error: tile 39, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	default:
		printf("Error: Case not found for tile 39. Passed val:%i", comingFromTile);
		break;
	}
}


void PathGenerator::tile35PathDecider(int comingFromTile)
{
	totalTiles++;
	int choice = rng.operator()() % 2;
	switch (comingFromTile)
	{
	case 34:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile35", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 1, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 2, pRoadGroup));
			tile36Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile35", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 3, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 4, pRoadGroup));
			tile0Path();
			break;
		default:
			printf("Error: tile 35, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 0:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile35", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 9, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 7, pRoadGroup));
			tile34Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile35", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 2, pRoadGroup));
			tile36Path();
			break;
		default:
			printf("Error: tile 35, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 36:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile35", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 6, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 7, pRoadGroup));
			tile34Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile35", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile35", 4, pRoadGroup));
			tile0Path();
			break;
		default:
			printf("Error: tile 35, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	default:
		printf("Error: Case not found for tile 35. Passed val:%i", comingFromTile);
		break;
	}
}

void PathGenerator::tile3PathDecider(int comingFromTile)
{
	totalTiles++;
	int choice = rng.operator()() % 2;
	switch (comingFromTile)
	{
	case 44:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile3", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 1, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 2, pRoadGroup));
			tile4Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile3", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 3, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 4, pRoadGroup));
			tile2Path();
			break;
		default:
			printf("Error: tile 3, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 2:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile3", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 9, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 7, pRoadGroup));
			tile44Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile3", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 2, pRoadGroup));
			tile4Path();
			break;
		default:
			printf("Error: tile 3, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 4:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile3", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 6, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 7, pRoadGroup));
			tile44Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile3", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile3", 4, pRoadGroup));
			tile2Path();
			break;
		default:
			printf("Error: tile 3, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	default:
		printf("Error: Case not found for tile 3. Passed val:%i", comingFromTile);
		break;
	}
}

void PathGenerator::tile10PathDecider(int comingFromTile)
{
	totalTiles++;
	int choice = rng.operator()() % 2;
	switch (comingFromTile)
	{
	case 9:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile10", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 1, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 2, pRoadGroup));
			tile41Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile10", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 3, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 4, pRoadGroup));
			tile11Path();
			break;
		default:
			printf("Error: tile 10, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 11:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile10", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 9, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 7, pRoadGroup));
			tile9Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile10", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 2, pRoadGroup));
			tile41Path();
			break;
		default:
			printf("Error: tile 10, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 41:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile10", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 6, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 7, pRoadGroup));
			tile9Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile10", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile10", 4, pRoadGroup));
			tile11Path();
			break;
		default:
			printf("Error: tile 10, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	default:
		printf("Error: Case not found for tile 10. Passed val:%i", comingFromTile);
		break;
	}


}

void PathGenerator::tile17PathDecider(int comingFromTile)
{
	totalTiles++;
	int choice = rng.operator()() % 2;
	switch (comingFromTile)
	{
	case 18:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile17", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 1, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 2, pRoadGroup));
			tile16Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile17", 0, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 3, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 4, pRoadGroup));
			tile48Path();
			break;
		default:
			printf("Error: tile 17, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 48:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile17", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 9, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 7, pRoadGroup));
			tile18Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile17", 8, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 2, pRoadGroup));
			tile16Path();
			break;
		default:
			printf("Error: tile 17, choice not handledPassed val:%i", comingFromTile);
			break;
		}
		break;
	case 16:
		switch (choice)
		{
		case 0:
			apfs.push_back(raaAnimationPointFinder("tile17", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 6, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 7, pRoadGroup));
			tile18Path();
			break;
		case 1:
			apfs.push_back(raaAnimationPointFinder("tile17", 5, pRoadGroup));
			apfs.push_back(raaAnimationPointFinder("tile17", 4, pRoadGroup));
			tile48Path();
			break;
		default:
			printf("Error: tile 17, choice not handled Passed val:%i", comingFromTile);
			break;
		}
		break;
	default:
		printf("Error: Case not found for tile 17. Passed val:%i", comingFromTile);
		break;
	}
}


