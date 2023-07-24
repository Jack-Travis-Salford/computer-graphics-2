#pragma once

#include "raaAnimationPointFinder.h"
#include <random>

typedef std::vector<raaAnimationPointFinder>raaAnimationPointFinders;

class PathGenerator {
public:
	PathGenerator(int startingTile, int lastTile,raaAnimationPointFinders apfs, osg::Node* pRoadGroup);
	raaAnimationPointFinders createPath();
	int startingTile;
	int lastTile;
	int totalTiles;
	raaAnimationPointFinders apfs;
	osg::Node* pRoadGroup;
	void tile26PathDecider(int comingFromTile);
	void tile35PathDecider(int comingFromTile);
	void tile3PathDecider(int comingFromTile);
	void tile10PathDecider(int comingFromTile);
	void tile17PathDecider(int comingFromTile);
	void tile39PathDecider(int comingFromTile);
private:
	void tile27Path();
	void tile34Path();
	void tile0Path();
	void tile2Path();
	void tile4Path();
	void tile9Path();
	void tile11Path();
	void tile16Path();
	void tile18Path();
	void tile25Path();
	void tile46Path();
	void tile45Path();
	void tile42Path();
	void tile44Path();
	void tile40Path();
	void tile41Path();
	void tile38Path();
	void tile36Path();
	void tile48Path();
	void tile47Path();
	std::mt19937 rng;


	

};