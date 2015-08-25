#pragma once

#include "ToolButton.h"

#include <boost/shared_ptr.hpp>

//=====================================================================

class CToolBox;
typedef boost::shared_ptr<CToolBox> ToolBox;

//=====================================================================

/*!
 * \brief
 * Obszar z przyciskami
 *
 *
 * Obszar z przyciskami do zapisu/odczytu poziomu i uruchomienia symulacji .
 */
class CToolBox
{
public:
	CToolBox(void);
	~CToolBox(void);

	/*!
     * Obs�uga wci�ci�cia przycisku myszy
     * 
     * \param pos
     * Punkt w kt�ry klikni�to
     */
	void mouseDown(const CL_Point &pos);

	/*!
     * Obs�uga ruchu kursora
     * 
     * \param pos
     * Punkt w kt�rym znajduje si� kursor myszy
     */
	void mouseMove(const CL_Point &pos);

	/*!
     * Obs�uga puszczenia przycisku myszy
     * 
     * \param pos
     * Punkt w kt�rym puszczono przycisk
     */
	void mouseUp  (const CL_Point &pos);

	/*!
     * Rysowanie obszaru z przyciskami
     */
	void draw();

	/*!
     * Obs�uga w��czania/wy��czania symulacji
     * 
     * true je�li w��czono symulacj�
     */
	void toggleSimulation(bool value);

private:
	ToolButton simulationButton_;
	ToolButton startButton_;
	ToolButton stopButton_;

	ToolButton saveButton_;
	ToolButton loadButton_;

	CL_Image background_;
};
