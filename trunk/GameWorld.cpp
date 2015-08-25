#include "GameWorld.h"
#include "AbstractElement.h"
#include "ElementFactory.h"
#include "IMApplication.h"
#include <ClanLib/display.h>

#include <boost/bind.hpp>

using namespace std;
using namespace boost;

//=====================================================================

CGameWorld::CGameWorld(CL_DisplayWindow &display_window) 
	: window_(display_window)
{
	//zamykanie okna
	slotQuit_ = window_.sig_window_close().connect(this, &CGameWorld::onWindowClose);
	
	//³¹czenie zdarzeñ
	slotKeyDown_   = window_.get_ic().get_keyboard().sig_key_down().connect(this, &CGameWorld::onKeyDown);
	slotMouseDown_ = window_.get_ic().get_mouse().sig_key_down().connect(this, &CGameWorld::onMouseDown);
	slotMouseUp_   = window_.get_ic().get_mouse().sig_key_up().connect(this, &CGameWorld::onMouseUp);
	slotMouseMove_ = window_.get_ic().get_mouse().sig_pointer_move().connect(this, &CGameWorld::onMouseMove);
}

//=====================================================================

CGameWorld::~CGameWorld(void)
{
}

//=====================================================================

void CGameWorld::run()
{
	quit_ = dragOnBoard_ = dragFromTools_ = rotating_ = false;

	toolBox_ = ToolBox(new CToolBox);

	while(!quit_)
	{
		update();
		draw();

		window_.flip();

		CL_KeepAlive::process();
		CL_System::sleep(10);
	};
}

//=====================================================================
	
void CGameWorld::startSimulation()
{ 
	if(IMApplication::getInstance().gameLevel()->isSimulating())
		return;

	IMApplication::getInstance().gameLevel()->startSimulation();
	toolBox_->toggleSimulation(true);
}

//=====================================================================
	
void CGameWorld::stopSimulation()
{ 
	if(!IMApplication::getInstance().gameLevel()->isSimulating())
		return;

	IMApplication::getInstance().gameLevel()->stopSimulation();
	toolBox_->toggleSimulation(false);
}
  
//=====================================================================

void CGameWorld::draw()
{
	gc().clear(CL_Colorf("#3F2B20"));

	//CL_Draw::box(gc(), IMApplication::toolsBox(), CL_Colorf::black);
	//CL_Draw::box(gc(), IMApplication::boardBox(), CL_Colorf::black);
	//CL_Draw::box(gc(), IMApplication::toolBarBox(), CL_Colorf::black);
	
	if(dragOnBoard_)
	{
		toolBox_->draw();
	}

	IMApplication::getInstance().gameLevel()->draw();
	
	if(!dragOnBoard_)
	{
		toolBox_->draw();
	}

	if(dragFromTools_ || dragOnBoard_)
	{
		dragElement_->draw();
	}	
}

//=====================================================================

void CGameWorld::update() 
{	
	if(IMApplication::getInstance().gameLevel()->update())
	{
		IMApplication::getInstance().levelFinished();
	}
}

//=====================================================================

void CGameWorld::on_render(CL_GraphicContext &gc, const CL_Rect &clip_rect)
{
	draw();
}

//=====================================================================

void CGameWorld::onKeyDown(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_KEY_SPACE)
	{
		if(IMApplication::getInstance().gameLevel()->isSimulating())
		{
			stopSimulation();
		
		} else
		{
			startSimulation();
		}

	} else if(key.id == CL_KEY_ESCAPE)
	{
		onWindowClose();
	}
}

//=====================================================================

void CGameWorld::onMouseDown(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_MOUSE_LEFT && IMApplication::toolBarBox().contains(key.mouse_pos))
	{
		toolBox_->mouseDown(key.mouse_pos);
	}

	if(IMApplication::getInstance().gameLevel()->isSimulating())
	{
		return;
	}

	if(key.id == CL_MOUSE_LEFT)
	{
		//przenoszenie z przybornika
		if(IMApplication::toolsBox().contains(key.mouse_pos))
		{
			dragElement_ = IMApplication::getInstance().gameLevel()->tools()->elementAtPos(key.mouse_pos);

			if(dragElement_ == AbstractElement())
			{
				IMApplication::getInstance().gameLevel()->tools()->mouseDown(key.mouse_pos);
				return;
			}

			dragFromTools_ = true;

			dragDelta_ = CL_Vec2f(float(key.mouse_pos.x - dragElement_->position().x), 
								  float(key.mouse_pos.y - dragElement_->position().y));
		

		} else if(IMApplication::boardBox().contains(key.mouse_pos)) //przesuwanie po planszy
		{
			dragElement_ = IMApplication::getInstance().gameLevel()->board()->elementAtPos(key.mouse_pos);

			if(dragElement_ == AbstractElement() || !dragElement_->canMove())
			{
				return;
			}

			dragOnBoard_ = true;

			dragDelta_ = CL_Vec2f(float(key.mouse_pos.x - dragElement_->position().x), 
								  float(key.mouse_pos.y - dragElement_->position().y));
		}

	} else if(key.id == CL_MOUSE_RIGHT)
	{
		//obracanie
		if(IMApplication::boardBox().contains(key.mouse_pos))
		{
			dragElement_ = IMApplication::getInstance().gameLevel()->board()->elementAtPos(key.mouse_pos);

			if(dragElement_ == AbstractElement() || !dragElement_->isRotatable() || !dragElement_->canMove())
			{
				return;
			}
				
			rotating_ = true;

			startRotation_ = dragElement_->rotation();
		
			CL_Vec2f dragVec = CL_Vec2f(float(dragElement_->position().x - key.mouse_pos.x), 
									    float(dragElement_->position().y - key.mouse_pos.y));

			dragVec.normalize(); 
		
			float corr = 1.0f;
			if(dragVec.y < 0.0f)
				corr = -1.0f;

			rotationDelta_ = dragVec.angle(CL_Vec2f(1.0f)) * corr;
		}
	}
}

//=====================================================================

void CGameWorld::onMouseUp(const CL_InputEvent &key, const CL_InputState &state)
{
	if(key.id == CL_MOUSE_LEFT && IMApplication::toolBarBox().contains(key.mouse_pos))
	{
		toolBox_->mouseUp(key.mouse_pos);
	}
	
	if(dragOnBoard_)
	{
		dragOnBoard_ = false;
		rotating_ = false;
		dragFromTools_ = false;

		if(IMApplication::toolsBox().contains(key.mouse_pos))
		{
			IMApplication::getInstance().gameLevel()->tools()->addElement(dragElement_->type());
			IMApplication::getInstance().gameLevel()->board()->removeElement(dragElement_);
		}

		return;

	} else if(rotating_)
	{
		dragOnBoard_ = false;
		rotating_ = false;
		dragFromTools_ = false;
		return;

	} else if(dragFromTools_)
	{
		dragOnBoard_ = false;
		rotating_ = false;
		dragFromTools_ = false;

		if(IMApplication::boardBox().contains(key.mouse_pos))
		{
			IMApplication::getInstance().gameLevel()->board()->addElement(dragElement_);
			IMApplication::getInstance().gameLevel()->tools()->removeElement(dragElement_->type());
		}
	
		return;
	}
	
	if(key.id == CL_MOUSE_LEFT && IMApplication::toolsBox().contains(key.mouse_pos))
	{
		IMApplication::getInstance().gameLevel()->tools()->mouseUp(key.mouse_pos);
	}
}

//=====================================================================

void CGameWorld::onMouseMove(const CL_InputEvent &key, const CL_InputState &state)
{
	if(dragOnBoard_ || dragFromTools_)
	{
		if(IMApplication::boardBox().contains(key.mouse_pos) || 
			IMApplication::toolsBox().contains(key.mouse_pos) ||dragFromTools_)
		{
			dragElement_->setPosition(key.mouse_pos - dragDelta_);
			return;
		}
	
	} else if(rotating_)
	{
		CL_Vec2f dragVec = CL_Vec2f(float(dragElement_->position().x - key.mouse_pos.x), 
									float(dragElement_->position().y - key.mouse_pos.y));

		dragVec.normalize(); 
		
		float corr = 1.0f;
		if(dragVec.y < 0.0f)
			corr = -1.0f;

		CL_Angle angleDelta = dragVec.angle(CL_Vec2f(1.0f)) * corr - rotationDelta_;

		//Zabezpieczenie przed k¹tem NaN
		if(!(angleDelta == angleDelta))
		{
			angleDelta = CL_Angle::from_degrees(0.0f);
		}

		dragElement_->setRotation(startRotation_ + angleDelta);
		dragDelta_ = dragVec;

		return;	
	} 
	
	if(IMApplication::toolBarBox().contains(key.mouse_pos))
	{
		toolBox_->mouseMove(key.mouse_pos);
	
	} else if(IMApplication::toolsBox().contains(key.mouse_pos))
	{
		IMApplication::getInstance().gameLevel()->tools()->mouseMove(key.mouse_pos);
	} 
}

//=====================================================================
	
void CGameWorld::onWindowClose() 
{
	quit_ = true;
}

//=====================================================================
