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
 * Zawiera planszê i przybornik.
 * Dane tej klasy s¹ zapisywane/odczytywanie przy serializacji
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
     * Odrysowywuje planszê i przybornik wraz z elementami w nich siê znajduj¹cymi
     */
	void draw();

	/*!
     * \brief
     * Aktualizacja wszystkich elementów na planszy
     * 
     * \return true jesli którykolwiek z elementów zwróci przy aktualizacji true.
     */
	bool update();

	/*!
	 * \brief
	 * Rozpoczêcie symulacji
	 * 
	 * Wo³ane przy ka¿dym rozpoczêciu symulacji
	 */
	void startSimulation() { board_->startSimulation(); };	

	/*!
	 * \brief
	 * Zakoñczenie symulacji
	 * 
	 * Wo³ane przy ka¿dym zakoñczeniu symulacji
	 */
	void stopSimulation() { board_->stopSimulation(); };

	bool isSimulating() const { return board_->isSimulating(); };

//Atrybuty
public:
	LevelBoard board() { return board_; };
	LevelTools tools() { return tools_; };

//Sk³adowe
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

