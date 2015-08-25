#include "IMApplication.h"
#include "IMFileDialog.h"
#include "IMMsgBox.h"
#include "GameWorld.h"
#include "ElementFactory.h"

#include <ClanLib/gui.h>
#include <fstream>

using namespace std;

//=====================================================================
	
IMApplication::IMApplication()
{
}

//=====================================================================
	
int IMApplication::do_run(const std::vector<CL_String> &args)
{
	static bool running = false;

	if(running)
	{
		throw AlreadyRunningException();	
	}

	running = true;

	CL_SetupCore setup_core;
	CL_SetupDisplay setup_display;
	CL_SetupGL setup_gl;

	CL_ConsoleWindow console("Console", 80, 160);

	try
	{					
		CL_String resource_filename("Resources/GUIThemeBasic/resources.xml");
		CL_String theme_filename("Resources/GUIThemeBasic/theme.css");

		CL_ResourceManager resources(resource_filename);
		CL_GUIThemeDefault theme;
		theme.set_resources(resources);
		CL_GUIWindowManagerSystem wm;
		CL_GUIManager gui;
		gui.set_window_manager(wm);
	    gui.set_theme(theme);
		gui.set_css_document(theme_filename);

		CL_GUITopLevelDescription desc;
		desc.set_title("[ZPR] Incredible Machines");
		desc.set_size(CL_Size(1024, 768), true);	// Use this resolution (as caption is disabled)
		desc.set_visible();
		desc.show_maximize_button(false);

		window_ = new CL_Window(&gui, desc);
	
		CL_DisplayWindow dwindow = window_->get_display_window();
		
		resources_.load("Resources/resources.xml");

		toolBarBox_.set_top_left(CL_Point(desc.get_size().width - 270, 20));
		toolBarBox_.set_width(250);
		toolBarBox_.set_height(100);

		toolsBox_.top = toolBarBox_.bottom + 20;
		toolsBox_.left = toolBarBox_.left;
		toolsBox_.set_width(toolBarBox_.get_width());
		toolsBox_.set_height(desc.get_size().height - 40 - toolBarBox_.get_height() - 20);

		boardBox_.set_top_left(CL_Point(20, 20));
		boardBox_.set_width(toolsBox_.left - 40);
		boardBox_.set_height(desc.get_size().height - 40);
		
		initWorld(dwindow);
		initLevel();
		
		window_->func_render().set(world_.get(), &CGameWorld::on_render);
		
		world_->run();
	
	} catch(CL_Exception &exception)
	{
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();

		return -1;
	}

	return 0;
}

//=====================================================================
	
void IMApplication::initWorld(CL_DisplayWindow &window)
{
	world_ = GameWorld(new CGameWorld(window));
}	

//=====================================================================
	
void IMApplication::initLevel()
{
	level_ = GameLevel(new CGameLevel(true));
}

//=====================================================================
	
void IMApplication::loadLevel()
{
	CIMFileDialog dialog(window_, CIMFileDialog::LoadDialog);
	dialog.set_visible();
	int ret = dialog.exec();

	if(ret == 0)
	{
		return;
	}

	fstream file(dialog.getFileName().c_str(), fstream::in);

	GameLevel level(new CGameLevel(ret == 2));

	file >> level;

	file.close();

	level_ = level;
}

//=====================================================================
	
void IMApplication::saveLevel()
{	
	CIMFileDialog dialog(window_, CIMFileDialog::SaveDialog);	
	dialog.set_visible();
	int ret = dialog.exec();

	if(ret == 0)
	{
		return;
	}

	fstream file(dialog.getFileName().c_str(), fstream::out);

	file << level_;

	file.close();
}

//=====================================================================

void IMApplication::levelFinished()
{
	CIMMsgBox msg(window_, "Gratulacje!");
	msg.set_visible();
	msg.exec();

	world_->stopSimulation();
}