#pragma once

#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/gl.h>
#include <ClanLib/application.h>
#include <ClanLib/gui.h>

/*!
 * \brief
 * Dalog wskazywania pliku
 * 
 * Okno dialogowe do wskazania pliku do odczytu/zapisu planszy
 */
class CIMFileDialog : public CL_Window
{
public:	
	/*!
	 * Typ dialogu
	 */
	enum DialogType 
	{
		SaveDialog,
		LoadDialog
	};

	CIMFileDialog(CL_GUIComponent *owner, DialogType type);
	~CIMFileDialog();

//Atrybuty
public:
	/*!
	 * Nazwa wskazanego pliku
	 * 
	 * \returns
	 * Nazwa wskazywanego pliku
	 */
	CL_String getFileName() const { return fileName_; };

	static CL_GUITopLevelDescription get_description();

//Implementacja
private:
	void on_render(CL_GraphicContext &gc, const CL_Rect &clip_rect);
	//void on_resized();
	bool on_inputPressed(const CL_InputEvent &input_event);
	bool on_inputReleased(const CL_InputEvent &input_event);
	bool on_inputPointerMoved(const CL_InputEvent &input_event);
	void on_okClicked();
	void on_editClicked();
	void on_cancelClicked();
	bool on_close();
	void on_fileListSelectionChanged(CL_ListViewSelection selection, CL_ListView *listview);
	void initFileList();

//Sk³adowe
private:
	DialogType type_;
	CL_String fileName_;

	CL_PushButton *buttonOk_;
	CL_PushButton *buttonEdit_;
	CL_PushButton *buttonCancel_;

	CL_ListView *fileList_;
	CL_LineEdit *fileNameEdit_;

	CL_GUIThemePart part_background;
};
