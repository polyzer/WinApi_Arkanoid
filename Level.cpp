#pragma once
#include "arkanoid_includes.h"

extern Game CurrentGame;
extern HWND hWnd;
extern Ball CurrentBall;
extern Platform CurrentPlatform;
extern int worktimer;

Level::Level() 
{
	this->setStandard();
	this->reMap();
}

Level::~Level() {
    for (int i = 0; i < this->Size_Strings; i++) {
         delete [] Map[i];
    }
    delete [] Map;
}

void Level::End(bool status) {
	KillTimer(hWnd, worktimer);
	if (status == true) {
		if (CurrentGame.CurrentLevelNumber == (CurrentGame.Levels.size() - 1)){
			MessageBox(hWnd, L"�� ������ ��� ��������� ������! ������� �������...", 
				L"�����", MB_OK | MB_ICONQUESTION
			);
			CurrentGame.CurrentLevelNumber = 0;
		} else {
			CurrentGame.CurrentLevelNumber++;			
		}
		CurrentGame.loadCurrentLevelByNumber();
		CurrentGame.setStandard();
		CurrentPlatform.setStandard();
		CurrentBall.setStandard();
		CurrentGame.saveStatus = 1;
		SetTimer(hWnd, worktimer, CurrentGame.FPS, NULL);
		saveConfig();
	} else {
		int i = MessageBox(hWnd, L"������ ������", 
		L"��������", MB_YESNO | MB_ICONQUESTION
		);
		if (i == IDYES) {
			CurrentGame.loadCurrentLevelByNumber();
			CurrentGame.setStandard();
			CurrentPlatform.setStandard();
			CurrentBall.setStandard();
			SetTimer(hWnd, worktimer, CurrentGame.FPS, NULL);
		} else {
			CurrentGame.End();
		}
	}
}


void Level::reMap()
{
	if (!this->init){ 
		for(int i = 0; i < this->Size_Strings; i++)
			delete [] Map[i];
		delete [] Map;
	} else 
		this->init = false;// ������� �������� ��������������, ����� ������� ������ � ���� ���

	Map = new Block *[this->Size_Strings];
	for (int i = 0; i < this->Size_Strings; i++)
		Map[i] = new Block [this->Size_Columns];
}

void Level::setNullLevel()// ������������� ������� �������
{
	for (int i = 0; i < this->Size_Strings; i++) {
		for (int j = 0; j < this->Size_Columns; j++) {
			if (i == 0) {
				this->Map[i][j].element = L'c';
			}else{
				this->Map[i][j].element = this->back;
			}
		}
	}

	CurrentBall.setStandard();
	CurrentGame.setStandard();
	CurrentPlatform.setStandard();
}
