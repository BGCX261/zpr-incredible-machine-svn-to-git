#include "LevelTools.h"
#include "ElementFactory.h"
#include "IMApplication.h"

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

//=====================================================================

CLevelTools::CLevelTools(bool editingMode) : editingMode_(editingMode)
{	
	background_ = CL_Image(IMApplication::getInstance().gameWorld()->gc(), 
		"Resources/Image/tools_background.png");

	background_.set_alignment(origin_center);

	int lastY = IMApplication::toolsBox().top;

	for(int i = 0; i < MaxTypes; ++i)
	{
		AbstractElement elem = ElementFactory::createElement(ElementType(i));
		
		if(editingMode_)
		{
			CL_Point pos;
			pos.x = IMApplication::toolsBox().get_center().x;
			pos.y = lastY + 20 + elem->height() / 2;
			elem->setPosition(pos);

			lastY = pos.y + elem->height() / 2;

			ToolButton add(new CToolButton("button_plus"));
			add->setPosition(CL_Point(IMApplication::toolsBox().right - 15, pos.y - 10));

			ToolButton del(new CToolButton("button_minus"));
			del->setPosition(CL_Point(IMApplication::toolsBox().right - 15, pos.y + 10)); 

			elements_.insert(ElementMap::value_type(ElementType(i), ElementInfo(elem, InfinityNum, add, del)));

			
		
		} else
		{
			elements_.insert(ElementMap::value_type(ElementType(i), ElementInfo(elem, 0, ToolButton(), ToolButton())));
		}
	}
}

//=====================================================================

CLevelTools::~CLevelTools(void)
{
}

//=====================================================================

void CLevelTools::addElement(ElementType type)
{
	int count = elements_[type].get<1>();

	if(editingMode_ || count == InfinityNum)
		return;

	setElementNumber(type, count + 1);
}

//=====================================================================

void CLevelTools::removeElement(ElementType type)
{
	int count = elements_[type].get<1>();
	
	if(count == 0 || count == InfinityNum || editingMode_)
		return;

	setElementNumber(type, count - 1);
}

//=====================================================================

void CLevelTools::setElementNumber(ElementType type, int num)
{
	if(elements_[type].get<1>() == 0)
	{
		if(num == 0)
			return;

		CL_Point pos;
		pos.x = IMApplication::toolsBox().get_center().x;
		pos.y = IMApplication::toolsBox().top;

		for(int i = type - 1; i >= 0; --i)
		{
			if(elements_[ElementType(i)].get<1>() != 0)
			{
				pos.y = int(elements_[ElementType(i)].get<0>()->position().y) + elements_[ElementType(i)].get<0>()->height() / 2;
				break;
			}
		}

		pos.y += 20 + elements_[type].get<0>()->height() / 2;

		elements_[type].get<0>()->setPosition(pos);		

		for(int i = type + 1; i < MaxTypes; ++i)
		{
			AbstractElement elem = elements_[ElementType(i)].get<0>();
			
			elem->setPosition(CL_Pointf(elem->position().x, 
				elem->position().y + 20 + elements_[type].get<0>()->height()));
		}


	} else
	{
		if(num != 0)
		{
			elements_[type].get<1>() = num;
			return;
		}

		for(int i = type + 1; i < MaxTypes; ++i)
		{
			AbstractElement elem = elements_[ElementType(i)].get<0>();
			
			elem->setPosition(CL_Pointf(elem->position().x, elem->position().y - 20 - elements_[type].get<0>()->height()));
		}
	}

	elements_[type].get<1>() = num;
}

//=====================================================================

AbstractElement CLevelTools::elementAtPos(const CL_Point &pos)
{
	ElementMap::iterator it;

	for(it = elements_.begin(); it != elements_.end(); ++it)
	{
		if(it->second.get<1>() != 0)
		{
			if(it->second.get<0>()->hitTest(pos))
			{
				AbstractElement elem =  ElementFactory::createElement(it->first);
				elem->setPosition(it->second.get<0>()->position());

				return elem;
			}
		}
	}

	return AbstractElement();
}

//=====================================================================

void CLevelTools::draw()
{ 
	static CL_Font font(IMApplication::getInstance().gameWorld()->gc(), "Calibri Bold", 22);

	background_.draw(IMApplication::getInstance().gameWorld()->gc(), 
		IMApplication::getInstance().toolsBox().get_center().x, IMApplication::getInstance().toolsBox().get_center().y);

	ElementMap::iterator it;

	for(it = elements_.begin(); it != elements_.end(); ++it)
	{
		if(it->second.get<1>() != 0 || editingMode_)
		{
			it->second.get<0>()->draw();

			if(editingMode_)
			{
				it->second.get<2>()->draw();
				it->second.get<3>()->draw();
			}

			if(it->second.get<1>() == InfinityNum)
				continue;

			CL_String text(lexical_cast<string>(it->second.get<1>()));
			int text_width = font.get_text_size(IMApplication::getInstance().gameWorld()->gc(), text).width;

			CL_Point pos = CL_Point(int(it->second.get<0>()->position().x), int(it->second.get<0>()->position().y));
			pos.x -= it->second.get<0>()->width() / 2 + 10 + text_width;
			pos.y += it->second.get<0>()->height() / 2;

			font.draw_text(IMApplication::getInstance().gameWorld()->gc(), pos.x, pos.y, text, CL_Colorf::black);
		}
	}
}

//=====================================================================
	
void CLevelTools::mouseDown(const CL_Point &pos)
{
	if(!editingMode_)
		return;

	ElementMap::iterator it;

	for(it = elements_.begin(); it != elements_.end(); ++it)
	{
		if(it->second.get<2>()->mouseDown(pos))
		{
			++(it->second.get<1>());
		}

		if(it->second.get<3>()->mouseDown(pos))
		{
			if(it->second.get<1>() == InfinityNum)
				continue;

			--(it->second.get<1>());
		}
	}
}

//=====================================================================
	
void CLevelTools::mouseMove(const CL_Point &pos)
{
	if(!editingMode_)
		return;

	ElementMap::iterator it;

	for(it = elements_.begin(); it != elements_.end(); ++it)
	{
		it->second.get<2>()->mouseMove(pos);
		it->second.get<3>()->mouseMove(pos);
	}
}

//=====================================================================
	
void CLevelTools::mouseUp(const CL_Point &pos)
{
	if(!editingMode_)
		return;

	ElementMap::iterator it;

	for(it = elements_.begin(); it != elements_.end(); ++it)
	{
		it->second.get<2>()->mouseUp(pos);
		it->second.get<3>()->mouseUp(pos);
	}
}

//=====================================================================
	
std::ostream & operator<< (std::ostream &out, const LevelTools &elem)      
{		
	for(int i = 0; i < MaxTypes; ++i)
	{
		out << elem->elements_[ElementType(i)].get<1>() << std::endl;
	}

	return out;
}

//=====================================================================

std::istream & operator>> (std::istream &in, LevelTools &elem)     
{		
	for(int i = 0; i < MaxTypes; ++i)
	{
		int count;
		in >> count;
		if(elem->editingMode_)
		{
			elem->elements_[ElementType(i)].get<1>() = count;
		} else
		{
			elem->setElementNumber(ElementType(i), count);
		}
	}

	return in;
}

//=====================================================================
