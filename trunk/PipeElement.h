#pragma once
#include "AbstractElement.h"
#include "PipePhysics.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CPipeElement;
typedef boost::shared_ptr<CPipeElement> PipeElement;

//=====================================================================

/*!
 * \brief
 * Rurka
 * 
 * P�aska rurka - elementy mog� swobodnie przeje�d�a� przez ni�.
 */
class CPipeElement : public CAbstractElement
{
public:
	CPipeElement();
	~CPipeElement(void);

	virtual void startSimulation(const PhysicsWorld &world);
	virtual void stopSimulation(const PhysicsWorld &world);

	virtual void draw();

	virtual bool isRotatable() const { return true; };
	virtual void setRotation(const CL_Angle &angle);

	static CAbstractElement* create()
	{
		return new CPipeElement;
	};

private:
	PipePhysics physics_;
	bool simulation_;

	CL_Sprite sprite_;
};
