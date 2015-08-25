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
     * Obs³uga wciœciêcia przycisku myszy
     * 
     * \param pos
     * Punkt w który klikniêto
     */
	void mouseDown(const CL_Point &pos);

	/*!
     * Obs³uga ruchu kursora
     * 
     * \param pos
     * Punkt w którym znajduje siê kursor myszy
     */
	void mouseMove(const CL_Point &pos);

	/*!
     * Obs³uga puszczenia przycisku myszy
     * 
     * \param pos
     * Punkt w którym puszczono przycisk
     */
	void mouseUp  (const CL_Point &pos);

	/*!
     * Rysowanie obszaru z przyciskami
     */
	void draw();

	/*!
     * Obs³uga w³¹czania/wy³¹czania symulacji
     * 
     * true jeœli w³¹czono symulacjê
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
