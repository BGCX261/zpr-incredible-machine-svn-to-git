/*!
 * AbstractFactory.h
 * 
 * Copyright (c) 2010 by Kamil Skoneczny & Joanna Nawalany
 */
#pragma once

#include "GameWorld.h"

#include <ClanLib/display.h>
#include <iostream>
#include <map>

//=====================================================================


/*!
 * \brief
 * Typ elementu
 * 
 * Enumeracja okreœlaj¹ca typ elementu dla fabryki elementów
 */
enum ElementType
{
	Ball = 0,
	Antigravity,
	QuaterPipe,
	Pipe,
	SpringBoard,
	Bucket,
	Ramp,
	Conveyor,

	MaxTypes //sta³a okreœlaj¹ca liczbê typów elementów
};

//=====================================================================

/*!
 * \brief
 * Abstrakcyjny element
 * 
 * Abstrakcyjna, bazowa klasa dla wsyzstkich elementów
 */
class CAbstractElement
{
public:
	CAbstractElement(ElementType type) : type_(type), movable_(true) { };
	virtual ~CAbstractElement(void) { };

//Operacje
public:
	/*!
	 * \brief
	 * Rozpoczêcie symulacji (dla pojedyñczego elementu)
	 * 
	 * \param world
	 * Œwiat w którym ma znaleŸæ siê element przy starcie symulacji
	 * 
	 * Rozpoczynaj¹c symulacjê nale¿y wywo³aæ tê metodê dla ka¿dego elementu
	 */
	virtual void startSimulation(const PhysicsWorld &world) = 0;

	/*!
	 * \brief
	 * Zakoñczenie symulacji (dla pojedyñczego elementu)
	 * 
	 * \param world
	 * Œwiat w którym jest element
	 * 
	 * Koñcz¹c symulacjê nale¿y wywo³aæ tê metodê dla ka¿dego elementu
	 */
	virtual void stopSimulation(const PhysicsWorld &world)  = 0;

	/*!
	 * \brief
	 * Rysowanie elementu
	 * 
	 * Metod¹ rysuj¹ca element, któr¹ nale¿y zaimplementowaæ w ka¿dym elemencie
	 */
	virtual void draw() = 0;

	/*!
	 * \brief
	 * Aktualizacja elementu
	 * 
	 * \returns
	 * true jeœli symulacja dobieg³a koñca (pi³ka wpad³a do koszyka)
	 * 
	 * Aktualizacja elementu
	 */
	virtual bool update() { return false; };

	/*!
	 * \brief
	 * Wykrywanie kolizji widoku elementu
	 * 
	 * \returns
	 * trua jeœli wykryto kolizjê
	 * 
	 * Wykrywanie kolizji np z punktem kursora myszki (potrzebne przy przesuwaniu 
	 * elementów myszk¹ po ekranie
	 */
	bool hitTest(const CL_CollisionOutline &outline) { return collisionBody_.collide(outline); };
	bool hitTest(const CL_Pointf &point) { return collisionBody_.point_inside(point); };
	bool hitTest(const CL_Point &point) { return hitTest(CL_Pointf(float(point.x), float(point.y))); };
	
//Atrybuty
public:
	ElementType type() const { return type_; };

	/*!
	 * \brief
	 * Ustawienie pozycji
	 * 
	 * \param pos
	 * Pozycja we wspó³rzêdnych ekranu (piksele)
	 * 
	 * Ustawienie pozycji elementu na ekranie przed symulacj¹
	 */
	void setPosition(const CL_Point &pos) { setPosition(CL_Pointf(float(pos.x), float(pos.y))); }; 
	void setPosition(const CL_Pointf &pos) 
	{ 
		position_ = pos; 
		collisionBody_.set_translation(pos.x, pos.y);
	};

	/*!
	 * \brief
	 * Ustawienie rotacji
	 * 
	 * \param angle
	 * K¹t obrotu (w stopniach, zgodnie z uk³adem wspó³rzêdnych)
	 * 
	 * Ustawienie rotacji elementu na planszy
	 */
	virtual void setRotation(const CL_Angle &angle) 
	{ 
		angle_ = angle; 
		collisionBody_.set_angle(angle);
	};

	/*!
	 * \brief
	 * Pozycja elementu
	 * 
	 * \returns
	 * Pozycja elementu we wspó³rzêdnych ekranu (piksele)
	 * 
	 * Pozycja elementu poza symulacj¹
	 */
	CL_Pointf position() const { return position_; };

	/*!
	 * \brief
	 * Rotacja elementu
	 * 
	 * \returns
	 * K¹t (w stopniach) o jaki jest obrócony element na planszy
	 * 
	 * Rotacja elementu z przed symulacji
	 */
	CL_Angle  rotation() const { return angle_; };

	/*!
	 * \brief
	 * Czy element jest rotowalny
	 * 
	 * \returns
	 * tru jeœli mo¿na obróciæ element
	 * 
	 * Okreœla, czy element mo¿na obracaæ na planszy za pomoc¹ myszki np.
	 */
	virtual bool isRotatable() const { return false; };

	/*!
	 * \brief
	 * Czy element jest dynamiczny
	 * 
	 * \returns
	 * true jeœli element mo¿e zmieniaæ swoje po³o¿enie podczas symulacji
	 * 
	 * Okreœla, czy element mo¿e zmieniaæ swoje po³o¿enie na planszy podczas symulacji
	 */
	virtual bool isDynamic() const { return false; };

	/*!
	 * \returns
	 * Szerokoœc elementu w pikselach
	 * 
	 * Szerokoœc elementu w pikselach
	 */
	virtual int width() const { return collisionBody_.get_width(); };

	/*!
	 * \returns
	 * Wysokoœæ elementu w pikselach
	 * 
	 * Wysokoœæ elementu w pikselach
	 */
	virtual int height() const { return collisionBody_.get_height(); };

	/*!
	 * \brief
	 * Okreœlenie czy element mo¿na przesywaæ po planszy
	 * 
	 * \param value
	 * Flaga czy mo¿na przesuwaæ element
	 * 
	 * Okreœla czy mo¿na przesuwaæ myszk¹ element po planszy.
	 * Elementy wczytane z z pliku w trybie gry nie mo¿na przesuwaæ po planszy
	 */
	void setMovable(bool value) { movable_ = value; };

	/*!
	 * \brief
	 * Okreœlenie czy element mo¿na przesywaæ po planszy
	 * 
	 * \return
	 * true jeœli mo¿na przesuwaæ element
	 * 
	 * Okreœla czy mo¿na przesuwaæ myszk¹ element po planszy.
	 * Elementy wczytane z z pliku w trybie gry nie mo¿na przesuwaæ po planszy
	 */
	bool canMove() const { return movable_; };

//Sk³adowe
protected:
	ElementType type_;
	bool movable_;

	CL_Pointf position_;
	CL_Angle  angle_;

	CL_CollisionOutline collisionBody_;

//serializacja
private:
	friend std::ostream & operator<< (std::ostream &out, const AbstractElement &elem);
	friend std::istream & operator>> (std::istream &in, AbstractElement &elem);
}; 

//=====================================================================
