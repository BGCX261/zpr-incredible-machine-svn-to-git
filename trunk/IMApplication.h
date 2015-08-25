#pragma once

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>

#include "GameWorld.h"
#include "GameLevel.h"

//=====================================================================

/*!
 * \brief
 * G³ówna klasa aplikacji
 * 
 * Kontroler. Od wywo³ania jego metody run rozpoczynany jest program.
 * Implementuje wzorzec singleton
 */
class IMApplication
{
//Operacje
public:
	static IMApplication& getInstance()
	{
		static IMApplication instance;
		return instance;
	}

	static int run(const std::vector<CL_String> &args)
	{
		return getInstance().do_run(args);
	}

	///tworzy pusty poziom dla edytora
	void initLevel();

	///otwiera poziom z pliku, do grania lub edycji
	void loadLevel();

	///zapis poziomu do pliku
	void saveLevel();

	///poziom wygrany
	void levelFinished();

//Atrybuty
public:
	GameWorld gameWorld() const { return world_; };
	GameLevel gameLevel() const { return level_; };

	CL_ResourceManager* resources() { return &resources_; };

	static CL_Rect toolsBox() 
	{ 
		return getInstance().toolsBox_;
	};
	
	static CL_Rect boardBox()
	{
		return getInstance().boardBox_; 
	};
	
	static CL_Rect toolBarBox()
	{
		return getInstance().toolBarBox_; 
	};

//Konstrukcja
private:
	IMApplication();
	IMApplication(const IMApplication &);
	IMApplication& operator=(const IMApplication&);

//Implementacja
private:
	int do_run(const std::vector<CL_String> &args);
	void initWorld(CL_DisplayWindow &window);

//Sk³adowe
private:
	GameWorld world_;
	GameLevel level_;
	
	CL_ResourceManager resources_;

	CL_Rect toolsBox_;
	CL_Rect boardBox_;
	CL_Rect toolBarBox_;

	CL_Window *window_;
};

//=====================================================================

class AlreadyRunningException : public std::exception
{
public:
	AlreadyRunningException() { };

	virtual const char* what() const throw()
	{
		return "Aplikacja zosta³a wczeœniej uruchomiona!";
	}
};