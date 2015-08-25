#pragma once

#include "AbstractElement.h"

//=====================================================================

class CElementFactory;
typedef CElementFactory ElementFactory;

//=====================================================================

/*!
 * \brief
 * Fabryka elementów
 * 
 * Klasa implementuj¹ca wzorzec fabryki skalowalnej.
 * na podstawie zarejestrowanego identyfikatowa i funkcji tworz¹cej
 * produkowany jest dynamicznie nowy element
 */
class CElementFactory {
	
	typedef CAbstractElement* (*ElementCreator)();

public:
	~CElementFactory(void);

//Operacje
public:
	/*!
	 * \brief
	 * Metoda produkcji elementu
	 * 
	 * \param type
	 * Typ elementu do wyprodukowania
	 * 
	 * \returns
	 * Nowy element
	 * 
	 * Statyczna metoda produkuj¹ca nowy element na podstawie podanego typu
	 * Typ musi byæ zarejestrowany wczeœniej
	 */
	static AbstractElement createElement(const ElementType& type)
	{
		static CElementFactory factory;
		return factory.do_createElement(type);		
	}

//Konstrukcja
private:
	CElementFactory(void);
	CElementFactory(const CElementFactory &) { };
	CElementFactory& operator=(const CElementFactory&);

//Implementacja
private:
	AbstractElement do_createElement(const ElementType& type);
	bool registerElement(const ElementType& type, ElementCreator creator);

//Sk³adowe
private:
	typedef std::map<ElementType, ElementCreator> Map; 
	Map associations_;				  
};

//=====================================================================
