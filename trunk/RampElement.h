#pragma once
#include "AbstractElement.h"
#include "RampPhysics.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CRampElement;
typedef boost::shared_ptr<CRampElement> RampElement;

//=====================================================================

/*!
 * Œcianka
 */
class CRampElement : public CAbstractElement
{
public:
	CRampElement();
	~CRampElement(void);

	virtual void startSimulation(const PhysicsWorld &world);
	virtual void stopSimulation(const PhysicsWorld &world);

	virtual void draw();

	virtual bool isRotatable() const { return true; };
	virtual void setRotation(const CL_Angle &angle);

	static CAbstractElement* create()
	{
		return new CRampElement;
	};

private:
	RampPhysics physics_;
	bool simulation_;

	CL_Sprite sprite_;
};
