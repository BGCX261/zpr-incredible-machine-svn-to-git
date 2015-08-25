#pragma once
#include "AbstractElement.h"
#include "ConveyorPhysics.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CConveyorElement;
typedef boost::shared_ptr<CConveyorElement> ConveyorElement;

//=====================================================================

/*!
 * \brief
 * Ruchoma taœma
 * 
 * Element przesuwaj¹cy po sobie inne elementy
 */
class CConveyorElement : public CAbstractElement
{
public:
	CConveyorElement();
	~CConveyorElement(void);

	virtual void startSimulation(const PhysicsWorld &world);
	virtual void stopSimulation(const PhysicsWorld &world);

	virtual void draw();
	virtual bool update();

	static CAbstractElement* create()
	{
		return new CConveyorElement;
	};

private:
	ConveyorPhysics physics_;
	bool simulation_;

	CL_Sprite sprite_;
};
