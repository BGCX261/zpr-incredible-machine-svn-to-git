#include "ElementFactory.h"

#include "AntigravityElement.h"
#include "BallElement.h"
#include "BucketElement.h"
#include "ConveyorElement.h"
#include "PipeElement.h"
#include "QuaterPipeElement.h"
#include "RampElement.h"
#include "SpringBoardElement.h"

//=====================================================================

CElementFactory::CElementFactory(void)
{
	registerElement(Antigravity, &CAntigravityElement::create);
	registerElement(Ball,        &CBallElement::create       );
	registerElement(Bucket,      &CBucketElement::create     );
	registerElement(Conveyor,    &CConveyorElement::create   );
	registerElement(Pipe,        &CPipeElement::create       );
	registerElement(QuaterPipe,  &CQuaterPipeElement::create );
	registerElement(Ramp,        &CRampElement::create       );
	registerElement(SpringBoard, &CSpringBoardElement::create);
}

//=====================================================================

CElementFactory::~CElementFactory(void)
{
}

//=====================================================================

AbstractElement CElementFactory::do_createElement(const ElementType& type)
{
	Map::const_iterator it = associations_.find(type);

	if(it != associations_.end())
	{
		return AbstractElement(it->second());
	
	} else
	{
		return AbstractElement();
	}
}

//=====================================================================

bool CElementFactory::registerElement(const ElementType& type, ElementCreator creator)
{
	return associations_.insert(Map::value_type(type, creator)).second;
}

//=====================================================================
