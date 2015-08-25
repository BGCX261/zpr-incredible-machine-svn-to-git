#include "AbstractPhysics.h"

//=====================================================================

CAbstractPhysics::CAbstractPhysics(void) : body_(0L)
{
}

//=====================================================================

CAbstractPhysics::~CAbstractPhysics(void)
{
}

//=====================================================================

float CAbstractPhysics::positionX() const
{
	return body_->GetPosition().x * 100.0f;
}

//=====================================================================

float CAbstractPhysics::positionY() const
{
	return -body_->GetPosition().y * 100.0f;
}

//=====================================================================

float CAbstractPhysics::rotation() const
{
	return float(-180 * body_->GetAngle() / b2_pi);
}