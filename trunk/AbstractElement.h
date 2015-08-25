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
 * Enumeracja okre�laj�ca typ elementu dla fabryki element�w
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

	MaxTypes //sta�a okre�laj�ca liczb� typ�w element�w
};

//=====================================================================

/*!
 * \brief
 * Abstrakcyjny element
 * 
 * Abstrakcyjna, bazowa klasa dla wsyzstkich element�w
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
	 * Rozpocz�cie symulacji (dla pojedy�czego elementu)
	 * 
	 * \param world
	 * �wiat w kt�rym ma znale�� si� element przy starcie symulacji
	 * 
	 * Rozpoczynaj�c symulacj� nale�y wywo�a� t� metod� dla ka�dego elementu
	 */
	virtual void startSimulation(const PhysicsWorld &world) = 0;

	/*!
	 * \brief
	 * Zako�czenie symulacji (dla pojedy�czego elementu)
	 * 
	 * \param world
	 * �wiat w kt�rym jest element
	 * 
	 * Ko�cz�c symulacj� nale�y wywo�a� t� metod� dla ka�dego elementu
	 */
	virtual void stopSimulation(const PhysicsWorld &world)  = 0;

	/*!
	 * \brief
	 * Rysowanie elementu
	 * 
	 * Metod� rysuj�ca element, kt�r� nale�y zaimplementowa� w ka�dym elemencie
	 */
	virtual void draw() = 0;

	/*!
	 * \brief
	 * Aktualizacja elementu
	 * 
	 * \returns
	 * true je�li symulacja dobieg�a ko�ca (pi�ka wpad�a do koszyka)
	 * 
	 * Aktualizacja elementu
	 */
	virtual bool update() { return false; };

	/*!
	 * \brief
	 * Wykrywanie kolizji widoku elementu
	 * 
	 * \returns
	 * trua je�li wykryto kolizj�
	 * 
	 * Wykrywanie kolizji np z punktem kursora myszki (potrzebne przy przesuwaniu 
	 * element�w myszk� po ekranie
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
	 * Pozycja we wsp�rz�dnych ekranu (piksele)
	 * 
	 * Ustawienie pozycji elementu na ekranie przed symulacj�
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
	 * K�t obrotu (w stopniach, zgodnie z uk�adem wsp�rz�dnych)
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
	 * Pozycja elementu we wsp�rz�dnych ekranu (piksele)
	 * 
	 * Pozycja elementu poza symulacj�
	 */
	CL_Pointf position() const { return position_; };

	/*!
	 * \brief
	 * Rotacja elementu
	 * 
	 * \returns
	 * K�t (w stopniach) o jaki jest obr�cony element na planszy
	 * 
	 * Rotacja elementu z przed symulacji
	 */
	CL_Angle  rotation() const { return angle_; };

	/*!
	 * \brief
	 * Czy element jest rotowalny
	 * 
	 * \returns
	 * tru je�li mo�na obr�ci� element
	 * 
	 * Okre�la, czy element mo�na obraca� na planszy za pomoc� myszki np.
	 */
	virtual bool isRotatable() const { return false; };

	/*!
	 * \brief
	 * Czy element jest dynamiczny
	 * 
	 * \returns
	 * true je�li element mo�e zmienia� swoje po�o�enie podczas symulacji
	 * 
	 * Okre�la, czy element mo�e zmienia� swoje po�o�enie na planszy podczas symulacji
	 */
	virtual bool isDynamic() const { return false; };

	/*!
	 * \returns
	 * Szeroko�c elementu w pikselach
	 * 
	 * Szeroko�c elementu w pikselach
	 */
	virtual int width() const { return collisionBody_.get_width(); };

	/*!
	 * \returns
	 * Wysoko�� elementu w pikselach
	 * 
	 * Wysoko�� elementu w pikselach
	 */
	virtual int height() const { return collisionBody_.get_height(); };

	/*!
	 * \brief
	 * Okre�lenie czy element mo�na przesywa� po planszy
	 * 
	 * \param value
	 * Flaga czy mo�na przesuwa� element
	 * 
	 * Okre�la czy mo�na przesuwa� myszk� element po planszy.
	 * Elementy wczytane z z pliku w trybie gry nie mo�na przesuwa� po planszy
	 */
	void setMovable(bool value) { movable_ = value; };

	/*!
	 * \brief
	 * Okre�lenie czy element mo�na przesywa� po planszy
	 * 
	 * \return
	 * true je�li mo�na przesuwa� element
	 * 
	 * Okre�la czy mo�na przesuwa� myszk� element po planszy.
	 * Elementy wczytane z z pliku w trybie gry nie mo�na przesuwa� po planszy
	 */
	bool canMove() const { return movable_; };

//Sk�adowe
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
