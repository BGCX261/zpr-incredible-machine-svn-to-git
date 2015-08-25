#include "LevelBoard.h"
#include "IMApplication.h"

#include <boost/bind.hpp>

using namespace std;
using namespace boost;

//=====================================================================
	
CLevelBoard::CLevelBoard(bool editingMode) : simulating_(false), editingMode_(editingMode)
{
	background_ = CL_Image(IMApplication::getInstance().gameWorld()->gc(), 
		"Resources/Image/board_background.png");

	background_.set_alignment(origin_center);
}

//=====================================================================
	
CLevelBoard::~CLevelBoard(void)
{
}

//=====================================================================
	
void CLevelBoard::addElement(const AbstractElement &element)
{
	//¿eby pi³ki rysowa³y siê za koszykiem, rurkami...
	if(element->isDynamic())
	{
		elementList_.push_front(element);
	
	} else
	{
		elementList_.push_back(element);
	}
}

//=====================================================================
	
void CLevelBoard::removeElement(const AbstractElement &element)
{
	elementList_.remove(element);
}

//=====================================================================
	
AbstractElement CLevelBoard::elementAtPos(const CL_Point &pos)
{
	list<AbstractElement>::reverse_iterator it;
	for(it = elementList_.rbegin(); it != elementList_.rend(); ++it)
	{
		if((*it)->hitTest(pos))
		{
			return *it;
		}
	}

	return AbstractElement();
}

//=====================================================================
	
void CLevelBoard::draw()
{
	background_.draw(IMApplication::getInstance().gameWorld()->gc(), 
		IMApplication::getInstance().boardBox().get_center().x, IMApplication::getInstance().boardBox().get_center().y);

	for_each(elementList_.begin(), elementList_.end(), bind(&CAbstractElement::draw, _1));	
}

//=====================================================================
	
bool CLevelBoard::update()
{
	if(simulating_)
	{
		simulationWorld_->step();
	}

	bool result = false;

	list<AbstractElement>::iterator it;
	for(it = elementList_.begin(); it != elementList_.end(); ++it)
	{
		result |= (*it)->update();
	}

	return result;
}

//=====================================================================
	
void CLevelBoard::startSimulation()
{
	simulationWorld_ = PhysicsWorld(new CPhysicsWorld);
	for_each(elementList_.begin(), elementList_.end(), bind(&CAbstractElement::startSimulation, _1, simulationWorld_));

	simulating_ = true; 
}

//=====================================================================
	
void CLevelBoard::stopSimulation()
{
	for_each(elementList_.begin(), elementList_.end(), bind(&CAbstractElement::stopSimulation, _1, simulationWorld_));
	simulationWorld_ = PhysicsWorld();

	simulating_ = false; 
}

//=====================================================================
	
std::ostream & operator<< (std::ostream &out, const LevelBoard &elem)      
{
	out << elem->elementList_.size() << std::endl;

	list<AbstractElement>::iterator it;
	for(it = elem->elementList_.begin(); it != elem->elementList_.end(); ++it)
	{
		out << *it;
	}

	return out;
}

//=====================================================================
	
std::istream & operator>> (std::istream &in, LevelBoard &elem)
{
	int size;
	in >> size;

	for(int i = 0; i < size; ++i)
	{
		AbstractElement element;
		in >> element;

		element->setMovable(elem->editingMode_);

		elem->addElement(element);
	}

	return in;
}

//=====================================================================
	