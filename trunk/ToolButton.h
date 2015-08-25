#pragma once

#include <ClanLib/display.h>

#include <boost/shared_ptr.hpp>

//=====================================================================

class CToolButton;
typedef boost::shared_ptr<CToolButton> ToolButton;

//=====================================================================

/*!
 * \brief
 * Przycisk z obrazkiem
 * 
 * Widok przyciski z obrazkiem
 */
class CToolButton
{
public:
	CToolButton(const std::string& name);
	virtual ~CToolButton(void);

public:

	/*!
     * Obs�uga wci�ci�cia przycisku myszy
	 *
	 * \return true je�li klikni�to w przycisk
     * 
     * \param pos
     * Punkt w kt�ry klikni�to
     */
	bool mouseDown(const CL_Point &pos);

	/*!
     * Obs�uga ruchu kursora
     * 
     * \param pos
     * Punkt w kt�rym znajduje si� kursor myszy
     */
	void mouseMove(const CL_Point &pos);

	/*!
     * Obs�uga puszczenia przycisku myszy
     * 
     * \param pos
     * Punkt w kt�rym puszczono przycisk
     */
	void mouseUp  (const CL_Point &pos);

	/*!
     * Okre�lenie pozycji przycisku
     * 
     * \param pos
     * Nowa pozycja przycisku
     */
	void setPosition(const CL_Point &pos);

	/*!
     * Okre�lenie dost�pno�ci przycisku
     * 
     * \param value
     * Dostepno�� przycisku
     */
	void setEnabled(bool value);
	
	/*!
     * Rysowanie przycisku
     */
	void draw();

private:
	std::string name_;
	CL_Point position_;

	CL_CollisionOutline outline_;
	CL_Sprite* currentView_;

	CL_Sprite* normalView_;
	CL_Sprite* hoverView_;
	CL_Sprite* clickedView_;
	CL_Sprite* disabledView_;

	bool mouseDown_;
	bool enabled_;
};
