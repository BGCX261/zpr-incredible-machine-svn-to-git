#pragma once

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include <ClanLib/gui.h>

/*!
 * \brief
 * Okno z tekstow¹ informacj¹
 * 
 * Okno dialogowe z tekstow¹ informacj¹ dla u¿ytkownika
 */
class CIMMsgBox : public CL_Window
{
public:	
	CIMMsgBox(CL_GUIComponent *owner, const CL_String &text);
	~CIMMsgBox();

//Atrybuty
public:
	static CL_GUITopLevelDescription get_description();

//Implementacja
private:
	void on_render(CL_GraphicContext &gc, const CL_Rect &clip_rect);
	bool on_inputPressed(const CL_InputEvent &input_event);
	bool on_inputReleased(const CL_InputEvent &input_event);
	bool on_inputPointerMoved(const CL_InputEvent &input_event);
	void on_okClicked();
	void on_cancelClicked();
	bool on_close();

//Sk³adowe
private:
	CL_PushButton *buttonOk_;
	CL_PushButton *buttonCancel_;

	CL_Label *label_;

	CL_GUIThemePart part_background;
};
