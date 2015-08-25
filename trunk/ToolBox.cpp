#include "ToolBox.h"
#include "IMApplication.h"

//=====================================================================
	
CToolBox::CToolBox(void)
{
	background_ = CL_Image(IMApplication::getInstance().gameWorld()->gc(), 
		"Resources/Image/toolbox_background.png");

	background_.set_alignment(origin_center);

	CL_Point tmp;

	startButton_ = ToolButton(new CToolButton("button_start"));
	tmp = IMApplication::toolBarBox().get_center();
	tmp.y += IMApplication::toolBarBox().get_height() / 5;
	startButton_->setPosition(tmp);

	stopButton_ = ToolButton(new CToolButton("button_stop"));
	stopButton_->setPosition(tmp);

	simulationButton_ = startButton_;

	loadButton_ = ToolButton(new CToolButton("button_load"));
	tmp = IMApplication::toolBarBox().get_center();
	tmp.x -= IMApplication::toolBarBox().get_width() / 4;
	tmp.y -= IMApplication::toolBarBox().get_height() / 5;
	loadButton_->setPosition(tmp);

	saveButton_ = ToolButton(new CToolButton("button_save"));
	tmp = IMApplication::toolBarBox().get_center();
	tmp.x += IMApplication::toolBarBox().get_width() / 4;
	tmp.y -= IMApplication::toolBarBox().get_height() / 5;
	saveButton_->setPosition(tmp);
}

//=====================================================================
	
CToolBox::~CToolBox(void)
{
}

//=====================================================================
	
void CToolBox::mouseDown(const CL_Point &pos)
{
	if(simulationButton_->mouseDown(pos))
	{
		if(IMApplication::getInstance().gameLevel()->isSimulating())
		{
			IMApplication::getInstance().gameWorld()->stopSimulation();

		} else
		{
			IMApplication::getInstance().gameWorld()->startSimulation();
		}
	}

	if(loadButton_->mouseDown(pos))
	{
		IMApplication::getInstance().loadLevel();
	}

	if(saveButton_->mouseDown(pos))
	{
		IMApplication::getInstance().saveLevel();
	}
}

//=====================================================================
	
void CToolBox::mouseMove(const CL_Point &pos)
{
	simulationButton_->mouseMove(pos);
	loadButton_->mouseMove(pos);
	saveButton_->mouseMove(pos);
}

//=====================================================================
	
void CToolBox::mouseUp(const CL_Point &pos)
{
	simulationButton_->mouseUp(pos);
	loadButton_->mouseUp(pos);
	saveButton_->mouseUp(pos);
}

//=====================================================================
	
void CToolBox::draw()
{
	background_.draw(IMApplication::getInstance().gameWorld()->gc(), 
		IMApplication::getInstance().toolBarBox().get_center().x, IMApplication::getInstance().toolBarBox().get_center().y);

	simulationButton_->draw();
	loadButton_->draw();
	saveButton_->draw();
}

//=====================================================================
	
void CToolBox::toggleSimulation(bool value)
{
	loadButton_->setEnabled(!value);
	saveButton_->setEnabled(!value);

	if(value)
	{
		startButton_->mouseUp(CL_Point());
		simulationButton_ = stopButton_;
	
	} else
	{
		stopButton_->mouseUp(CL_Point());
		simulationButton_ = startButton_;
	}
}