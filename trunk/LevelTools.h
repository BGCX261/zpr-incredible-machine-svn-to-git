#pragma once

#include "AbstractElement.h"
#include "ToolButton.h"

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

//=====================================================================

class CLevelTools;
typedef boost::shared_ptr<CLevelTools> LevelTools;

//=====================================================================

/*!
 * \brief
 * Przybornik
 * 
 * Przybornik w danym poziomie.
 * Dostarcza interfejsu do dodatania i odejmowania iloœci elementów danego typu
 */
class CLevelTools
{
public:
	CLevelTools(bool editingMode = false);
	~CLevelTools(void);

	///okreœlenie liczby elementów jako nieskoñczona
	enum {
		InfinityNum = -1
	};

//Operacje
public:
	void addElement(ElementType type);
	void removeElement(ElementType type);

	void setElementNumber(ElementType type, int num);

	AbstractElement elementAtPos(const CL_Point &pos);

	void draw();

	void mouseDown(const CL_Point &pos);
	void mouseMove(const CL_Point &pos);
	void mouseUp  (const CL_Point &pos);

//Sk³adowe
private:
	typedef boost::tuple<AbstractElement, int, ToolButton, ToolButton> ElementInfo;
	typedef std::map<ElementType, ElementInfo> ElementMap;
	ElementMap elements_;

	bool editingMode_;

	CL_Image background_;

//serializacja
private:
	friend std::ostream & operator<< (std::ostream &out, const LevelTools &elem);
	friend std::istream & operator>> (std::istream &in, LevelTools &elem);
};

//=====================================================================

