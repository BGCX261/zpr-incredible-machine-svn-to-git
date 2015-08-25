#pragma once

#include "AbstractElement.h"
#include "BallPhysics.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CBallElement;
typedef boost::shared_ptr<CBallElement> BallElement;

//=====================================================================

/*!
 * \brief
 * Element - pi³ka
 * 
 * Dynamiczny element - pi³ka
 */
class CBallElement : public CAbstractElement
{
public:
	CBallElement();
	~CBallElement(void);

	virtual void startSimulation(const PhysicsWorld &world);
	virtual void stopSimulation(const PhysicsWorld &world);

	virtual void draw();

	virtual bool isDynamic() const { return true; };

	static CAbstractElement* create()
	{
		return new CBallElement;
	};

private:
	BallPhysics physics_;
	bool simulation_;

	CL_Sprite sprite_;
};
