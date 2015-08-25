#pragma once
#include "AbstractElement.h"
#include "BucketPhysics.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CBucketElement;
typedef boost::shared_ptr<CBucketElement> BucketElement;

//=====================================================================

/*!
 * \brief
 * Element - wiaderko
 * 
 * Wiaderko do którego ma wpaœæ pi³ka aby zakoñczyæ rozgrywany poziom
 */
class CBucketElement : public CAbstractElement
{
public:
	CBucketElement();
	~CBucketElement(void);

	virtual void startSimulation(const PhysicsWorld &world);
	virtual void stopSimulation(const PhysicsWorld &world);

	virtual void draw();
	virtual bool update();

	virtual bool isRotatable() const { return true; };
	virtual void setRotation(const CL_Angle &angle);

	static CAbstractElement* create()
	{
		return new CBucketElement;
	};

private:
	BucketPhysics physics_;
	bool simulation_;

	CL_Sprite sprite_;
};
