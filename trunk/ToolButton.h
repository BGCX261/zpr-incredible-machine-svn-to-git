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
     * Obs³uga wciœciêcia przycisku myszy
	 *
	 * \return true jeœli klikniêto w przycisk
     * 
     * \param pos
     * Punkt w który klikniêto
     */
	bool mouseDown(const CL_Point &pos);

	/*!
     * Obs³uga ruchu kursora
     * 
     * \param pos
     * Punkt w którym znajduje siê kursor myszy
     */
	void mouseMove(const CL_Point &pos);

	/*!
     * Obs³uga puszczenia przycisku myszy
     * 
     * \param pos
     * Punkt w którym puszczono przycisk
     */
	void mouseUp  (const CL_Point &pos);

	/*!
     * Okreœlenie pozycji przycisku
     * 
     * \param pos
     * Nowa pozycja przycisku
     */
	void setPosition(const CL_Point &pos);

	/*!
     * Okreœlenie dostêpnoœci przycisku
     * 
     * \param value
     * Dostepnoœæ przycisku
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
