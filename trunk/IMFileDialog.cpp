#include "IMFileDialog.h"
#include "IMMsgBox.h"

//=====================================================================

CIMFileDialog::CIMFileDialog(CL_GUIComponent *owner, DialogType type)
	: CL_Window(owner, get_description()), buttonOk_(0L), buttonCancel_(0L), buttonEdit_(0L), 
	  fileList_(0L), type_(type)
{
	CL_DisplayWindow dispwindow = get_display_window();

	set_class_name("file_dialog");

	func_render().set(this, &CIMFileDialog::on_render);
	func_input_pressed().set(this, &CIMFileDialog::on_inputPressed);
	func_input_released().set(this, &CIMFileDialog::on_inputReleased);
	func_input_pointer_moved().set(this, &CIMFileDialog::on_inputPointerMoved);
	func_close().set(this, &CIMFileDialog::on_close);

	part_background = CL_GUIThemePart(this);

	initFileList();

	fileNameEdit_ = new CL_LineEdit(this);
	fileNameEdit_->set_geometry(CL_Rect(fileList_->get_geometry().left, fileList_->get_geometry().bottom + 10, 
		CL_Size(360, 21)));
	fileNameEdit_->set_text("");
	
	if(type == LoadDialog)
	{
		fileNameEdit_->set_enabled(false);
	}

	buttonCancel_ = new CL_PushButton(this);

	buttonCancel_->func_clicked().set(this, &CIMFileDialog::on_cancelClicked);

	buttonCancel_->set_text("Anuluj");
	buttonCancel_->set_cancel(true);
	buttonCancel_->set_geometry(CL_Rect(fileNameEdit_->get_geometry().right - 75, fileNameEdit_->get_geometry().bottom + 10, 
		CL_Size(75, 22)));

	if(type == LoadDialog)
	{
		buttonEdit_ = new CL_PushButton(this);
		buttonEdit_->func_clicked().set(this, &CIMFileDialog::on_editClicked);
		buttonEdit_->set_text("Edytuj");
		buttonEdit_->set_geometry(CL_Rect(fileNameEdit_->get_geometry().left, fileNameEdit_->get_geometry().bottom + 10, 
			CL_Size(75, 22)));
	}

	buttonOk_ = new CL_PushButton(this);
	buttonOk_->func_clicked().set(this, &CIMFileDialog::on_okClicked);
	
	if(type == LoadDialog)
	{
		buttonOk_->set_text("Graj");
	
	} else
	{
		buttonOk_->set_text("Zapisz");
	}

	buttonOk_->set_default(true);
	buttonOk_->set_geometry(CL_Rect(buttonCancel_->get_geometry().left - 85, fileNameEdit_->get_geometry().bottom + 10, 
		CL_Size(75, 22)));

	//on_resized();
}

//=====================================================================

CIMFileDialog::~CIMFileDialog()
{
}

//=====================================================================

void CIMFileDialog::initFileList()
{

	fileList_ = new CL_ListView(this);
	fileList_->set_geometry(CL_Rect(10, 10, CL_Size(360, 180)));
	fileList_->set_display_mode(listview_mode_details);
	fileList_->func_selection_changed().set(this, &CIMFileDialog::on_fileListSelectionChanged, fileList_);
	
	CL_ListViewHeader *lv_header = fileList_->get_header();  
	lv_header->append(lv_header->create_column("fname_id", "Poziom"));
	CL_ListViewItem doc_item = fileList_->get_document_item(); 

	CL_DirectoryScanner scanner;
	if (scanner.scan(".", "*.iml"))
	{
		while (scanner.next())
		{
			if(scanner.is_directory())
				continue;

			CL_ListViewItem i1 = fileList_->create_item();
			{
				i1.set_column_text("fname_id", scanner.get_name().erase(scanner.get_name().length() - 4));
				doc_item.append_child(i1);
			}
		}
	}
}

//=====================================================================

void CIMFileDialog::on_fileListSelectionChanged(CL_ListViewSelection selection, CL_ListView *listview)
{
	fileNameEdit_->set_text(listview->get_selected_item().get_column("fname_id").get_text());
}

//=====================================================================

CL_GUITopLevelDescription CIMFileDialog::get_description()
{
	CL_GUITopLevelDescription desc;
	desc.set_title("Wska¿ plik");
	desc.set_allow_resize(false);
	desc.set_visible(false);
	desc.set_size(CL_Size(380, 263), true);
	desc.show_maximize_button(false);
	return desc;
}

//=====================================================================

void CIMFileDialog::on_render(CL_GraphicContext &gc, const CL_Rect &clip_rect)
{
	CL_Rect background = get_size();
	part_background.render_box(gc, background, clip_rect);
}

//=====================================================================

bool CIMFileDialog::on_inputPressed(const CL_InputEvent &input_event)
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

bool CIMFileDialog::on_inputReleased(const CL_InputEvent &input_event)
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

bool CIMFileDialog::on_inputPointerMoved(const CL_InputEvent &input_event)
{
	return true;
}

//=====================================================================

void CIMFileDialog::on_okClicked()
{
	if(fileNameEdit_->get_text().empty())
		return;

	fileName_ = fileNameEdit_->get_text() + CL_String(".iml");

	if(type_ == SaveDialog && CL_FileHelp::file_exists(fileName_))
	{
		CIMMsgBox msg(this, "Czy nadpisaæ plik?");
		msg.set_visible();

		if(msg.exec() == 0)
			return;
	}

	exit_with_code(1);
}

//=====================================================================

void CIMFileDialog::on_editClicked()
{
	if(fileNameEdit_->get_text().empty())
		return;

	fileName_ = fileNameEdit_->get_text() + CL_String(".iml");
	exit_with_code(2);
}

//=====================================================================

void CIMFileDialog::on_cancelClicked()
{
	exit_with_code(0);
}

//=====================================================================

bool CIMFileDialog::on_close()
{
	exit_with_code(0);
	return true;
}

//=====================================================================

