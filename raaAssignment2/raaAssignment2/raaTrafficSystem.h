#pragma once

#include <list>

typedef std::list<class raaCollisionTarget*> raaCollisionTargets;
typedef std::list<class raaCollisionTarget*> raaLightTargets;

class raaTrafficSystem
{
public:
	static void start();
	static void end();
	static void addTarget(raaCollisionTarget* pTarget);
	static void addTrafficTarget(raaCollisionTarget* pTarget);
	static void removeTarget(raaCollisionTarget* pTarget);
	static void removeTrafficTarget(raaCollisionTarget* pTarget);
	static const raaCollisionTargets& colliders();
	static const raaCollisionTargets& trafficColliders();
protected:
	static raaCollisionTargets sm_lColliders;
	static raaLightTargets sm_LightColliders;
};

