#pragma once
#include "AbstractElement.h"
#include "QuaterPipePhysics.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CQuaterPipeElement;
typedef boost::shared_ptr<CQuaterPipeElement> QuaterPipeElement;

//=====================================================================

/*!
 * \brief
 * Æwieræ rurka
 * 
 * Zakrzywiona rurka
 */
class CQuaterPipeElement : public CAbstractElement
{
public:
	CQuaterPipeElement();
	~CQuaterPipeElement(void);

	virtual void startSimulation(const PhysicsWorld &world);
	virtual void stopSimulation(const PhysicsWorld &world);

	virtual void draw();

	virtual bool isRotatable() const { return true; };
	virtual void setRotation(const CL_Angle &angle);

	static CAbstractElement* create()
	{
		return new CQuaterPipeElement;
	};

private:
	QuaterPipePhysics physics_;
	bool simulation_;

	CL_Sprite sprite_;
};
