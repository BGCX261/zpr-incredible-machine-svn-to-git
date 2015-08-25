#pragma once

#include "LevelBoard.h"
#include "LevelTools.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CGameLevel;
typedef boost::shared_ptr<CGameLevel> GameLevel;

//=====================================================================

/*!
 * \brief
 * Aktualnie rozgrywany poziom
 * 
 * Model i widok aktualnie rozgrywanego poziomu.
 * Zawiera plansz� i przybornik.
 * Dane tej klasy s� zapisywane/odczytywanie przy serializacji
 */
class CGameLevel
{
public:
	CGameLevel(bool editingMode = false);
	~CGameLevel(void);

//Operacje
public:

	/*!
     * \brief
     * Odrysowanie poziomu
     * 
     * Odrysowywuje plansz� i przybornik wraz z elementami w nich si� znajduj�cymi
     */
	void draw();

	/*!
     * \brief
     * Aktualizacja wszystkich element�w na planszy
     * 
     * \return true jesli kt�rykolwiek z element�w zwr�ci przy aktualizacji true.
     */
	bool update();

	/*!
	 * \brief
	 * Rozpocz�cie symulacji
	 * 
	 * Wo�ane przy ka�dym rozpocz�ciu symulacji
	 */
	void startSimulation() { board_->startSimulation(); };	

	/*!
	 * \brief
	 * Zako�czenie symulacji
	 * 
	 * Wo�ane przy ka�dym zako�czeniu symulacji
	 */
	void stopSimulation() { board_->stopSimulation(); };

	bool isSimulating() const { return board_->isSimulating(); };

//Atrybuty
public:
	LevelBoard board() { return board_; };
	LevelTools tools() { return tools_; };

//Sk�adowe
private:
	LevelBoard board_;
	LevelTools tools_;

//serializacja
private:
	friend std::ostream & operator<< (std::ostream &out, const GameLevel &elem)      
	{
		out << elem->board_ << elem->tools_;
		return out;
	};

	friend std::istream & operator>> (std::istream &in, GameLevel &elem)      
	{
		in >> elem->board_ >> elem->tools_;
		return in;
	};
};

//=====================================================================

