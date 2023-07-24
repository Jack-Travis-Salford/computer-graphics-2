
#include "raaCollisionTarget.h"
#include "raaTrafficSystem.h"

raaCollisionTargets raaTrafficSystem::sm_lColliders;
raaCollisionTargets raaTrafficSystem::sm_LightColliders;

void raaTrafficSystem::start()
{
	sm_lColliders.clear();
	sm_LightColliders.clear();
}

void raaTrafficSystem::end()
{
	sm_lColliders.clear();
	sm_LightColliders.clear();
}

void raaTrafficSystem::addTarget(raaCollisionTarget* pTarget)
{
	if (pTarget && std::find(sm_lColliders.begin(), sm_lColliders.end(), pTarget) == sm_lColliders.end()) sm_lColliders.push_back(pTarget);
}

void raaTrafficSystem::addTrafficTarget(raaCollisionTarget* pTarget)
{
	if (pTarget && std::find(sm_LightColliders.begin(), sm_LightColliders.end(), pTarget) == sm_LightColliders.end()) sm_LightColliders.push_back(pTarget);
}

void raaTrafficSystem::removeTarget(raaCollisionTarget* pTarget)
{
	if (pTarget && std::find(sm_lColliders.begin(), sm_lColliders.end(), pTarget) != sm_lColliders.end()) sm_lColliders.remove(pTarget);
}

void raaTrafficSystem::removeTrafficTarget(raaCollisionTarget* pTarget)
{
	if (pTarget && std::find(sm_LightColliders.begin(), sm_LightColliders.end(), pTarget) != sm_LightColliders.end()) sm_LightColliders.remove(pTarget);
}

const raaCollisionTargets& raaTrafficSystem::colliders()
{
	return sm_lColliders;
}
const raaCollisionTargets& raaTrafficSystem::trafficColliders()
{
	return sm_LightColliders;
}
