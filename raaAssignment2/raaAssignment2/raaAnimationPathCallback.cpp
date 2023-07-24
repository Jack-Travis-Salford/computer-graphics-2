#include <windows.h>
#include <osg/NodeVisitor>

#include "raaAnimationPathCallback.h"

raaAnimationPathCallback::raaAnimationPathCallback(osg::AnimationPath* ap, double dSpeed, double maxAcc) : osg::AnimationPathCallback(ap, 0.0, 1.0), maxSpeed(dSpeed), m_bFirst(true), m_dTimeStep(0.0), m_dActualTime(0.0), maxAcc(maxAcc)
{
	currentSpeed = 0.1f;
	isObstructionAhead = false;
	decAllowedDisplacement = 0;
	targetSpeed = maxSpeed;
}

raaAnimationPathCallback::~raaAnimationPathCallback()
{
}

double raaAnimationPathCallback::getAnimationTime() const
{
	return m_dActualTime;
}

void raaAnimationPathCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	if(m_bFirst)
	{
		m_dLastTime = nv->getFrameStamp()->getSimulationTime();
		m_bFirst = false;
	}
	else
	{
		double dTime = nv->getFrameStamp()->getSimulationTime();

		double lastFrameLength = (dTime - m_dLastTime);
		if (!isObstructionAhead)
		{
			double newSpeed = currentSpeed + (maxAcc * lastFrameLength);
			currentSpeed = (newSpeed > maxSpeed) ? maxSpeed : newSpeed;
		}
		else {
			double acceleration = ((targetSpeed * targetSpeed) - (currentSpeed * currentSpeed)) / (2 * decAllowedDisplacement );
			acceleration = (acceleration > maxAcc) ? maxAcc : acceleration;
			if (targetSpeed == 0 && (acceleration > -0.007 && acceleration < 0))
			{
				acceleration = -10;
			}
		
			double newSpeed = currentSpeed + (acceleration);
			newSpeed = (newSpeed > maxSpeed) ? maxSpeed : newSpeed;
			newSpeed = (newSpeed < 0) ? 0 : newSpeed;
			currentSpeed = newSpeed;
		}
		

		m_dTimeStep = (dTime - m_dLastTime) * currentSpeed;
		if (!_pause)
		{
			m_dActualTime += m_dTimeStep;
			update(*node);
		}
		m_dLastTime = dTime;
	}
	NodeCallback::traverse(node, nv);

}

double raaAnimationPathCallback::getCurrentSpeed()
{
	return currentSpeed;
}

void raaAnimationPathCallback::setCurrentSpeed(double dSpeed)
{
	if (dSpeed>maxSpeed)
	{
		dSpeed = maxSpeed;
	}
	currentSpeed = dSpeed;
	
}

double raaAnimationPathCallback::getLastTimeStep()
{
	return m_dTimeStep;
}

void raaAnimationPathCallback::setObstructionAhead(bool obstructionAhead)
{
	isObstructionAhead = obstructionAhead;
}

void raaAnimationPathCallback::setObstructionAheadDistance(double distance, double endSpeed)
{
	
	isObstructionAhead = true;
	decAllowedDisplacement = distance;
	targetSpeed = endSpeed;
	
}





