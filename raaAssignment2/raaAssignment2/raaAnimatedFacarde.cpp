#include <windows.h>
#include <osg/MatrixTransform>

#include "raaAnimatedFacarde.h"

raaAnimatedFacarde::raaAnimatedFacarde(osg::Node* pPart, osg::AnimationPath* ap, double dMaxSpeed, double maxAcc): raaFacarde(pPart), raaAnimationPathCallback(ap, dMaxSpeed, maxAcc)
{
	osg::MatrixTransform* pTop = new osg::MatrixTransform();

	pTop->addChild(m_pRoot);
	m_pRoot->unref();
	m_pRoot = pTop;
	m_pRoot->ref();

	m_pRoot->addUpdateCallback(this);

}

raaAnimatedFacarde::~raaAnimatedFacarde()
{
}
