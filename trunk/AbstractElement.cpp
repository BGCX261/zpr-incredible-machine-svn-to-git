#include "AbstractElement.h"
#include "ElementFactory.h"

std::ostream & operator<< (std::ostream &out, const AbstractElement &elem)      
{
	out << elem->type_ << std::endl;
	out << elem->position_.x << std::endl; 
	out << elem->position_.y << std::endl; 
	out << elem->angle_.to_degrees() << std::endl;
	
	return out;
};

std::istream & operator>> (std::istream &in, AbstractElement &elem)      
{
	int type;
	in >> type;
	elem = ElementFactory::createElement(ElementType(type));

	CL_Pointf pos;
	in >> pos.x;
	in >> pos.y;

	elem->setPosition(pos);

	float angle;
	in >> angle;
	elem->setRotation(CL_Angle::from_degrees(angle));
	
	return in;
};