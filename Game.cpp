#pragma once
#include "arkanoid_includes.h"

extern Ball CurrentBall;
extern HWND hWnd;
extern Platform CurrentPlatform;

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


void Game::increasePoints(char c) {
	this->points += 100;
	//����������� ����� � ����������� �� ������������ �����!
}
void Game::destroyBlock(int y, int x) {
	CurrentLevel.Map[y][x] = CurrentLevel.back;
}

void Game::render(HDC hdc, static int sx, static int sy) { //����������
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
				for(int k = 0; k < CurrentPlatform.length; k++)
					Rectangle(hdc, j * cube_size.X, i * cube_size.Y, (j + 1) * cube_size.X, (i + 1) * cube_size.Y);
				j += (CurrentPlatform.length - 1); // j
				continue;
			}
			else if (CurrentBall.position.X == j && CurrentBall.position.Y == i) {
					Rectangle(hdc, j * cube_size.X, i * cube_size.Y, (j + 1) * cube_size.X, (i + 1) * cube_size.Y);				
				continue;
			}else {
					Rectangle(hdc, j * cube_size.X, i * cube_size.Y, (j + 1) * cube_size.X, (i + 1) * cube_size.Y);	
			}
		}
	}
	//printInfo();
}
bool Game::createLevel(std::string LName) { // ��������/�������� �������
	Level newlevel;
	newlevel.name = LName;
	newlevel.number = CurrentGame.Levels.size();
	FILE *level_file;
	if ((level_file = fopen(newlevel.name.c_str(), "r")) == NULL) {
		MessageBox(hWnd, (LPCWSTR) newlevel.name.c_str(), 
		_T("���� �� �����������"), MB_YESNO | MB_ICONQUESTION
		);
	}
	fscanf(level_file, "%i%i", &newlevel.Size_Columns, &newlevel.Size_Strings);
	fseek(level_file, 2, SEEK_CUR);
	fscanf(level_file, "%c", &newlevel.back);
	fseek(level_file, 2, SEEK_CUR);
	fscanf(level_file, "%i%i%i", 
		&newlevel.minSpeedTime, &newlevel.maxSpeedTime, &newlevel.stepNorm
	);
	for (int i = 0; i < newlevel.Size_Strings; i++) {
		for (int j = 0; j < newlevel.Size_Columns; j++) {
			fscanf(level_file, "%c", &newlevel.Map[i][j]);
		}
		fseek(level_file, 2, SEEK_CUR);
	}
	fclose(level_file);
	CurrentGame.Levels.push_back(newlevel);
	return true;
}

bool Game::loadCurrentLevel() { // ��������/�������� �������
	CurrentLevel.name = CurrentGame.Levels[CurrentGame.CurrentLevelNumber].name;
	CurrentLevel.number = CurrentGame.CurrentLevelNumber;
	CurrentLevel.back = CurrentGame.Levels[CurrentGame.CurrentLevelNumber].back;
	CurrentLevel.maxSpeedTime = CurrentGame.Levels[CurrentGame.CurrentLevelNumber].maxSpeedTime;
	CurrentLevel.minSpeedTime = CurrentGame.Levels[CurrentGame.CurrentLevelNumber].minSpeedTime;
	CurrentLevel.Size_Columns = CurrentGame.Levels[CurrentGame.CurrentLevelNumber].Size_Columns;
	CurrentLevel.Size_Strings = CurrentGame.Levels[CurrentGame.CurrentLevelNumber].Size_Strings;
	CurrentLevel.reMap(0);
	for (int i = 0; i < CurrentLevel.Size_Strings; i++) {
		for (int j = 0; j < CurrentLevel.Size_Columns; j++) {
			CurrentLevel.Map[i][j] = CurrentGame.Levels[CurrentGame.CurrentLevelNumber].Map[i][j];
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
			CurrentGame.createLevel(ws2mb(datas.cFileName));
		}
	} else 
		return false;
	FindClose(hff);
	return true;
}


void Game::End() { // ��������� ������� � Level.End
	int i = MessageBox(hWnd, _T("��������� ����"), 
		_T("����������"), MB_YESNO | MB_ICONQUESTION
		);
	i = (i == IDYES)? 1 : 0;
	if (i == 1) {
		CurrentGame.saveStatus = 1;
	} else {
		CurrentGame.saveStatus = 0;
	}
	saveConfig();
	exit(0);
}

void Game::printInfo() {
	
}