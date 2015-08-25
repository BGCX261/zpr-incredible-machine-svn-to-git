#pragma once

#include "AbstractElement.h"
#include "PhysicsWorld.h"

#include <list>
#include <boost/shared_ptr.hpp>

//=====================================================================

class CLevelBoard;
typedef boost::shared_ptr<CLevelBoard> LevelBoard;

//=====================================================================

/*!
 * Plansza w aktualnym poziomie gry.
 * Dostarcza interfejsu do dodawania i usuwania z niej elementów, 
 * jak równie¿ rysowania i aktualizacji ich.
 */
class CLevelBoard
{
public:
	CLevelBoard(bool editingMode = false);
	~CLevelBoard(void);

//Operacje
public:
	void addElement(const AbstractElement &element);
	void removeElement(const AbstractElement &element);

	AbstractElement elementAtPos(const CL_Point &pos);

	void draw();
	bool update();

	void startSimulation();
	void stopSimulation();

	bool isSimulating() const { return simulating_; };

//Sk³adowe
private:	
	std::list<AbstractElement> elementList_;
	PhysicsWorld simulationWorld_;

	bool simulating_;
	bool editingMode_;

	CL_Image background_;

//serializacja
private:
	friend std::ostream & operator<< (std::ostream &out, const LevelBoard &elem);
	friend std::istream & operator>> (std::istream &in, LevelBoard &elem);
};

//=====================================================================

