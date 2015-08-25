#include "IMMsgBox.h"

//=====================================================================

CIMMsgBox::CIMMsgBox(CL_GUIComponent *manager, const CL_String &text)
	: CL_Window(manager, get_description()), buttonOk_(0L), buttonCancel_(0L)
{
	CL_DisplayWindow dispwindow = get_display_window();

	set_class_name("msg_box");

	func_render().set(this, &CIMMsgBox::on_render);
	func_input_pressed().set(this, &CIMMsgBox::on_inputPressed);
	func_input_released().set(this, &CIMMsgBox::on_inputReleased);
	func_input_pointer_moved().set(this, &CIMMsgBox::on_inputPointerMoved);
	func_close().set(this, &CIMMsgBox::on_close);

	part_background = CL_GUIThemePart(this);

	buttonCancel_ = new CL_PushButton(this);
	buttonCancel_->func_clicked().set(this, &CIMMsgBox::on_cancelClicked);
	buttonCancel_->set_text("Anuluj");
	buttonCancel_->set_cancel(true);
	buttonCancel_->set_geometry(CL_Rect(get_client_area().right - 85, get_client_area().bottom - 32, 
		CL_Size(75, 22)));

	buttonOk_ = new CL_PushButton(this);
	buttonOk_->func_clicked().set(this, &CIMMsgBox::on_okClicked);
	buttonOk_->set_text("Ok");
	buttonOk_->set_default(true);
	buttonOk_->set_geometry(CL_Rect(buttonCancel_->get_geometry().left - 85, buttonCancel_->get_geometry().top, 
		CL_Size(75, 22)));

	label_ = new CL_Label(this);
	label_->set_text(text);
	label_->set_alignment(CL_Label::align_center);
	label_->set_geometry(CL_Rect(0, get_client_area().get_center().y - 16 - 12, 
		CL_Size(get_client_area().get_width(), 24)));
}

//=====================================================================

CIMMsgBox::~CIMMsgBox()
{
}

//=====================================================================

CL_GUITopLevelDescription CIMMsgBox::get_description()
{
	CL_GUITopLevelDescription desc;
	desc.set_title("Incredible Machines");
	desc.set_allow_resize(false);
	desc.set_visible(false);
	desc.set_size(CL_Size(250, 100), true);
	desc.show_maximize_button(false);
	return desc;
}

//=====================================================================

void CIMMsgBox::on_render(CL_GraphicContext &gc, const CL_Rect &clip_rect)
{
	CL_Rect background = get_size();
	part_background.render_box(gc, background, clip_rect);
}

//=====================================================================

bool CIMMsgBox::on_inputPressed(const CL_InputEvent &input_event)
{
	if (input_event.id == CL_MOUSE_LEFT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=====================================================================

bool CIMMsgBox::on_inputReleased(const CL_InputEvent &input_event)
{
	if (input_event.id == CL_MOUSE_LEFT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=====================================================================

bool CIMMsgBox::on_inputPointerMoved(const CL_InputEvent &input_event)
{
	return true;
}

//=====================================================================

void CIMMsgBox::on_okClicked()
{
	exit_with_code(1);
}

//=====================================================================

void CIMMsgBox::on_cancelClicked()
{
	exit_with_code(0);
}

//=====================================================================

bool CIMMsgBox::on_close()
{
	exit_with_code(0);
	return true;
}

//=====================================================================
