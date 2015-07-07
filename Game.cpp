#pragma once
#include "arkanoid_includes.h"

extern Ball CurrentBall;
extern HWND hWnd;
extern Platform CurrentPlatform;
extern HDC hdc;

Game::Game() {
	this->setStandard();
	Level *lnew = new Level();// ������� �������
	lnew->setNullLevel();//������ ��� �������� �������� ������
	CurrentGame.Levels.push_back(lnew);
	lnew = NULL; // ������� ������� ����������.
	RedBlackBrush = CreateSolidBrush(RGB(128, 0, 0));
	RedLightBrush = CreateSolidBrush(RGB(255, 0, 0));
	GreenBlackBrush = CreateSolidBrush(RGB(0, 128, 0));
	GreenLightBrush = CreateSolidBrush(RGB(0, 255, 0));
	BlueBlackBrush = CreateSolidBrush(RGB(0, 0, 128));
	BlueLightBrush = CreateSolidBrush(RGB(0, 0, 255));
	YellowBlackBrush = CreateSolidBrush(RGB(128, 128, 0));
	YellowLightBrush = CreateSolidBrush(RGB(255, 255, 0));
	GreyBlackBrush = CreateSolidBrush(RGB(128, 128, 128));
	GreyLightBrush = CreateSolidBrush(RGB(255, 255, 255));
	White = CreateSolidBrush(RGB(255, 255, 0));
	Black = CreateSolidBrush(RGB(255, 255, 0));

}

Game::~Game (){
	// ��� ����������� ���� �� ����������� ������ �� ��� �������
	for (int i = 0; i < this->Levels.size(); i++) {
		delete Levels[i];
		Levels[i] = NULL;
	}
	DeleteObject(RedBlackBrush);
	DeleteObject(RedLightBrush);
	DeleteObject(GreenBlackBrush);
	DeleteObject(GreenLightBrush);
	DeleteObject(BlueBlackBrush);
	DeleteObject(BlueLightBrush);
	DeleteObject(YellowBlackBrush);
	DeleteObject(YellowLightBrush);
	DeleteObject(GreyBlackBrush);
	DeleteObject(GreyLightBrush);
	DeleteObject(White);
	DeleteObject(Black);

}

void Game::Play() {
	CurrentBall.timer++; // ������� �������� ��� ���������� �������� ����
	if (CurrentBall.timer >= CurrentBall.speed) {
		CurrentBall.collision();
		CurrentBall.collision();
		CurrentBall.collision();
		if(CurrentBall.collision()){
			CurrentBall.step(); // ���� ���������� ��� ������ - ��� ����
		}
		CurrentBall.timer = 0;
		CurrentBall.stepNum++;
	}
	if (CurrentBall.stepNum >= CurrentLevel.stepNorm) { //���� ������ ����� ���-�� �����, �� ����������
		CurrentBall.speedUp(2);
		CurrentBall.stepNum = 0;
	}
	InvalidateRect(hWnd, NULL, TRUE);
	if (CurrentLevel.allBlocksDestroyed()){
		CurrentLevel.End(true);
	}
}



void Game::increasePoints(wchar_t c) {
	this->points += 100;
	//����������� ����� � ����������� �� ������������ �����!
}
void Game::destroyBlock(int y, int x) {
	CurrentLevel.Map[y][x].element = CurrentLevel.back;
}

void Game::render(static int sx, static int sy) { //����������
	COORD cube_size;
	cube_size.X = sx / CurrentLevel.Size_Columns;
	cube_size.Y = sy / CurrentLevel.Size_Strings;
	MoveToEx(hdc, 0, 0, NULL);
	for (int i=0; i<CurrentLevel.Size_Strings; i++)
	{
		for (int j=0; j<CurrentLevel.Size_Columns; j++)
		{
			if (CurrentPlatform.position.X == j && CurrentPlatform.position.Y == i)
			{
				for(int k = 0; k < CurrentPlatform.length; k++){
					SetRect(&CurrentPlatform.block.rect, (j + k) * cube_size.X, i * cube_size.Y, (j + k + 1) * cube_size.X, (i + 1) * cube_size.Y);
					setElementColor(CurrentPlatform.block);
				}
				j += (CurrentPlatform.length - 1); // j
				continue;
			}
			else if (CurrentBall.position.X == j && CurrentBall.position.Y == i) {
				SetRect(&CurrentBall.block.rect, j * cube_size.X, i * cube_size.Y, (j + 1) * cube_size.X, (i + 1) * cube_size.Y);				
				setElementColor(CurrentBall.block);
				continue;
			}else if (CurrentLevel.Map[i][j].element != CurrentLevel.back){
				SetRect(&CurrentLevel.Map[i][j].rect, j * cube_size.X, i * cube_size.Y, (j + 1) * cube_size.X, (i + 1) * cube_size.Y);								
				setElementColor(CurrentLevel.Map[i][j]);
			}
			else {
				SetRect(&CurrentLevel.Map[i][j].rect, j * cube_size.X, i * cube_size.Y, (j + 1) * cube_size.X, (i + 1) * cube_size.Y);	
				setElementColor(CurrentLevel.Map[i][j]);
			}
		}
	}
	//printInfo();
}

bool Game::createLevel(LPCWSTR LName) { // ��������/�������� �������
	Level *newlevel = new Level(); //�������� ������ ��� ����� �������
	newlevel->name = LName; //��������� ������
	newlevel->number = CurrentGame.Levels.size();
	FILE *level_file;
	if ((level_file = _wfopen(newlevel->name, L"r")) == NULL) {
		MessageBox(hWnd, L"���� �� �����������", 
		L"���� �� �����������", MB_YESNO | MB_ICONQUESTION
		);
	}
	fwscanf(level_file, L"%i%i", &newlevel->Size_Columns, &newlevel->Size_Strings);
	fseek(level_file, 2, SEEK_CUR);
	fwscanf(level_file, L"%c", &newlevel->back);
	fseek(level_file, 2, SEEK_CUR);
	fwscanf(level_file, L"%i%i%i", 
		&newlevel->minSpeedTime, &newlevel->maxSpeedTime, &newlevel->stepNorm
	);
	for (int i = 0; i < newlevel->Size_Strings; i++) {
		for (int j = 0; j < newlevel->Size_Columns; j++) {
			fwscanf(level_file, L"%c", &newlevel->Map[i][j].element);
		}
		fseek(level_file, 2, SEEK_CUR);
	}
	fclose(level_file);
	CurrentGame.Levels.push_back(newlevel);
	newlevel = NULL; //��������, ����� ������ �� ����������
	return true;
}

bool Game::loadCurrentLevelByNumber() { // ��������/�������� �������
	//CurrentGame.CurrentLevelNumber = 0;
	CurrentLevel.name = CurrentGame.Levels[CurrentGame.CurrentLevelNumber]->name;
	CurrentLevel.number = CurrentGame.CurrentLevelNumber;
	CurrentLevel.back = CurrentGame.Levels[CurrentGame.CurrentLevelNumber]->back;
	CurrentLevel.maxSpeedTime = CurrentGame.Levels[CurrentGame.CurrentLevelNumber]->maxSpeedTime;
	CurrentLevel.minSpeedTime = CurrentGame.Levels[CurrentGame.CurrentLevelNumber]->minSpeedTime;
	CurrentLevel.Size_Columns = CurrentGame.Levels[CurrentGame.CurrentLevelNumber]->Size_Columns;
	CurrentLevel.Size_Strings = CurrentGame.Levels[CurrentGame.CurrentLevelNumber]->Size_Strings;
	CurrentLevel.reMap();
	for (int i = 0; i < CurrentLevel.Size_Strings; i++) {
		for (int j = 0; j < CurrentLevel.Size_Columns; j++) {
			CurrentLevel.Map[i][j].element = CurrentGame.Levels[CurrentGame.CurrentLevelNumber]->Map[i][j].element;
		}
	}
	return true;
}

bool Game::loadLevelsFromFile()
{
	int nff;
	HANDLE hff;
	WIN32_FIND_DATA datas;

	hff = FindFirstFile(L"LEVELS\\*.*", &datas);
	if (hff != INVALID_HANDLE_VALUE) 
	{
		for (;;)
		{
			nff = FindNextFile(hff, &datas);
			if (!nff)
				break;
			CurrentGame.createLevel(datas.cFileName);
		}
	} else 
		return false;
	FindClose(hff);
	return true;
}


void Game::End() {
	int i = MessageBox(hWnd, L"��������� ����", 
		L"����������", MB_YESNO | MB_ICONQUESTION
		);
	if (i == IDYES) {
		CurrentGame.saveStatus = 1;
	} else {
		CurrentGame.saveStatus = 0;
	}
	saveConfig();
	exit(0);
}

void Game::printInfo() {
	
}
