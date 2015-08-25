#include "GameLevel.h"

//=====================================================================

CGameLevel::CGameLevel(bool editingMode)
{
	board_ = LevelBoard(new CLevelBoard(editingMode));
	tools_ = LevelTools(new CLevelTools(editingMode));
}

//=====================================================================

CGameLevel::~CGameLevel(void)
{
}

//=====================================================================

void CGameLevel::draw()
{
	board_->draw();
	tools_->draw();
}

//=====================================================================

bool CGameLevel::update()
{
	return board_->update();
}

//=====================================================================

