#pragma once

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gui.h>

#include <list>
#include <boost/shared_ptr.hpp>

#include "PhysicsWorld.h"
#include "ToolBox.h"

//=====================================================================

class CGameWorld;
typedef boost::shared_ptr<CGameWorld> GameWorld;

class CAbstractElement;
typedef boost::shared_ptr<CAbstractElement> AbstractElement;

//=====================================================================

/*!
 * \brief
 * Widok gry
 * 
 * Zarz¹dza g³ównym oknem aplikacji, rysuje elementy i zarz¹dza komunikacj¹ z u¿ytkownikiem
 */
class CGameWorld
{
public:
	CGameWorld(CL_DisplayWindow &display_window);
	virtual ~CGameWorld(void);

//Atrybuty
public:	
	CL_GraphicContext& gc() const { return window_.get_gc(); }

//Operacje
public:

	/*!
     * \brief
     * Uruchomienie g³ównej pêtli programu
     * 
     * Metod¹ t¹ w³¹czamy g³ówne okno programu
     */
	void run();

    /*!
     * Rozpoczêcie symulacji
     */
	void startSimulation();

    /*!
     * Zakoñczenie symulacji
     */
	void stopSimulation();

	void on_render(CL_GraphicContext &gc, const CL_Rect &clip_rect);

//wewnêtrzne metody
private:
	void draw();
	void update();

	void onKeyDown  (const CL_InputEvent &key, const CL_InputState &state);
	void onMouseDown(const CL_InputEvent &key, const CL_InputState &state);
	void onMouseUp  (const CL_InputEvent &key, const CL_InputState &state);
	void onMouseMove(const CL_InputEvent &key, const CL_InputState &state);
	void onWindowClose();

//sk³adowe
private:
	CL_DisplayWindow &window_;

	CL_Slot slotMouseDown_;
	CL_Slot slotMouseUp_;
	CL_Slot slotMouseMove_;
	CL_Slot slotKeyDown_;
	CL_Slot slotQuit_;
	
	AbstractElement dragElement_;

	bool dragOnBoard_;
	bool dragFromTools_;
	bool rotating_;	

	bool quit_;

	CL_Vec2f dragDelta_;
	CL_Angle rotationDelta_;
	CL_Angle startRotation_;

	ToolBox toolBox_;
};
