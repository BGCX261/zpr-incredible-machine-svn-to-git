#pragma once
#include "AbstractElement.h"
#include "SpringBoardPhysics.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CSpringBoardElement;
typedef boost::shared_ptr<CSpringBoardElement> SpringBoardElement;

//=====================================================================

/*!
 * \brief
 * Trampolina
 * 
 * Trampolina - odbija elementy od siebie, nadaj¹c im przyspieszenie 
 * zgodnie ze swoim kontem obrotu
 */
class CSpringBoardElement : public CAbstractElement
{
public:
	CSpringBoardElement();
	~CSpringBoardElement(void);

	virtual void startSimulation(const PhysicsWorld &world);
	virtual void stopSimulation(const PhysicsWorld &world);

	virtual void draw();
	virtual bool update();

	virtual bool isRotatable() const { return true; };
	virtual void setRotation(const CL_Angle &angle);

	static CAbstractElement* create()
	{
		return new CSpringBoardElement;
	};

private:
	SpringBoardPhysics physics_;
	bool simulation_;

	CL_Sprite sprite_;
};
