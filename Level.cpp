#pragma once
#include "arkanoid_includes.h"

extern Game CurrentGame;
extern HWND hWnd;
extern Ball CurrentBall;
extern Platform CurrentPlatform;

Level::~Level() {
    for (int i = 0; i < this->Size_Strings; i++) {
        for (int j = 0; j < this->Size_Columns; j++){
            free(Map[i]);
        }
    }
    free(Map);
}

void Level::End(bool status) {
	if (status == true) {
			if (CurrentGame.CurrentLevelNumber == (CurrentGame.Levels.size() - 1)){
				MessageBox(hWnd, _T("Вы прошли все доступные уровни! Поехали сначала..."), 
				_T("Конец"), MB_OK | MB_ICONQUESTION
				);
				CurrentGame.CurrentLevelNumber = 0;
			} else {
				CurrentGame.CurrentLevelNumber++;			
			}
			CurrentGame.loadCurrentLevel();
			CurrentBall.setStandard();
			CurrentPlatform.setStandard();
			CurrentGame.setStandard();
			CurrentGame.saveStatus = 1;
			saveConfig();
	} else {
		int i = MessageBox(hWnd, _T("Сохранить игру"), 
		_T("Сохранение"), MB_YESNO | MB_ICONQUESTION
		);
		if (i == IDYES) {
			CurrentGame.loadCurrentLevel();
			CurrentPlatform.setStandard();
			CurrentBall.setStandard();
			CurrentGame.setStandard();
		} else {
			CurrentGame.End();
		}
	}
}


void Level::reMap(bool init)
{
	if (!init){ 
		for(int i = 0; i < this->Size_Strings; i++)
			free(this->Map[i]);
		free(Map);
	}

	Map = (char**) malloc(this->Size_Strings * sizeof(char*));
	for (int i = 0; i < this->Size_Strings; i++)
		Map[i] = (char*) malloc(this->Size_Columns * sizeof(char));
}

void Level::setNullLevel()// устанавливает нулевой уровень
{
	for (int i = 0; i < this->Size_Strings; i++) {
		for (int j = 0; j < this->Size_Columns; j++) {
			if (i == 0) {
				this->Map[i][j] = 'c';
			}else{
				this->Map[i][j] = this->back;
			}
			std::string str;
			str.resize(1);
			str[0] = Map[i][j];
			MessageBox(NULL, (LPCWSTR) str.c_str(), 
			_T("Нулевой уровень"), MB_OK | MB_ICONQUESTION
			);
		}
	}

	CurrentBall.setStandard();
	CurrentGame.setStandard();
	CurrentPlatform.setStandard();
}

Level::Level() 
{
	this->setStandard();
	this->reMap(1);
}