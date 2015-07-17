#pragma once
#include "arkanoid_includes.h"

extern Ball CurrentBall;
extern HWND hWnd;
extern Platform CurrentPlatform;
extern HDC hdc;
extern bool showMode;
extern int GamePlayTimer;

Game::Game() {
	this->setStandard();
	this->CurrentLevelNumber = 0; //������������� �������� �������� ������ �� 0
	this->CurrentLevelName = L"Default"; // ��� ������������ ������
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
	PlatformBrush = CreateSolidBrush(RGB(199, 123, 16));
	BallBrush = CreateSolidBrush(RGB(159, 129, 112));
	BlackBrush = CreateSolidBrush(RGB(0, 0, 0));

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
	DeleteObject(PlatformBrush);
	DeleteObject(BallBrush);
	DeleteObject(BlackBrush);

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
		CurrentGame.Shooting();
		CurrentGame.BlackBlockMoving();
	}
	
	if (CurrentBall.stepNum >= CurrentLevel.stepNorm) { //���� ������ ����� ���-�� �����, �� ����������
		CurrentBall.speedUp(1);
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
		//����������!!!
		//��������� �����
		//LevelName
		//GameLifes
		//minSpeed 30 .. 6
		//size_X size_Y
		//********************** elements
		//**********************
	Level *newlevel = new Level(); //�������� ������ ��� ����� �������
	newlevel->number = this->Levels.size();
	FILE *file_Fp;
	if ((file_Fp = _wfopen(LName, L"r")) != NULL)
	{
		wchar_t sym;
		newlevel->name.clear();
		fwscanf(file_Fp, L"%c", &sym);
		while (sym != L'\n') 
		{
			newlevel->name.push_back(sym);
			fwscanf(file_Fp, L"%c", &sym);
		}
		fwscanf(file_Fp, L"%i", &newlevel->gameLifes);
		fwscanf(file_Fp, L"%i", &newlevel->minSpeedTime);
		fwscanf(file_Fp, L"%i", &newlevel->Size_Columns);
		fwscanf(file_Fp, L"%i", &newlevel->Size_Strings);
		fseek(file_Fp, 3, SEEK_CUR);

		for (int i = 0; i < newlevel->Size_Strings; i++) 
		{
			for (int j = 0; j < newlevel->Size_Columns; j++) 
			{
				fwscanf(file_Fp, L"%c", &(newlevel->Map[i][j].element));
			}
			fseek(file_Fp, 2, SEEK_CUR);
		}
	} else {
		exit(0);
	}
	fclose(file_Fp);
	this->Levels.push_back(newlevel);
	newlevel = NULL; //��������, ����� ������ �� ����������
	return true;
}

bool Game::loadCurrentLevelByNumber() { // ��������/�������� �������
	CurrentLevel.name = this->Levels[this->CurrentLevelNumber]->name;
	this->CurrentLevelName = CurrentLevel.name;
	CurrentBall.genCourse(); // ���������� ���� ����
	int b = 0, p = 0;
	int k = 0;
	CurrentLevel.number = CurrentGame.CurrentLevelNumber;
	CurrentLevel.back = CurrentGame.Levels[this->CurrentLevelNumber]->back;
	CurrentLevel.maxSpeedTime = CurrentGame.Levels[this->CurrentLevelNumber]->maxSpeedTime;
	CurrentLevel.minSpeedTime = CurrentGame.Levels[this->CurrentLevelNumber]->minSpeedTime;
	CurrentBall.speed = CurrentLevel.minSpeedTime;
	CurrentLevel.gameLifes = CurrentGame.Levels[this->CurrentLevelNumber]->gameLifes;
	CurrentGame.lifes = CurrentLevel.gameLifes;
	CurrentLevel.Size_Columns = CurrentGame.Levels[this->CurrentLevelNumber]->Size_Columns;
	CurrentLevel.Size_Strings = CurrentGame.Levels[this->CurrentLevelNumber]->Size_Strings;
	CurrentLevel.reMap();
	for (int i = 0; i < CurrentLevel.Size_Strings; i++) {
		for (int j = 0; j < CurrentLevel.Size_Columns; j++) {
			CurrentLevel.Map[i][j].element = this->Levels[this->CurrentLevelNumber]->Map[i][j].element;
			if (CurrentGame.Levels[this->CurrentLevelNumber]->Map[i][j].element == L'P')	//���� ����������� ������ P, ��		
			{	
				CurrentPlatform.position.X = j; //������������� ��������� ���������
				CurrentPlatform.position.Y = i;
				for (k = j; k < CurrentLevel.Size_Columns; k++) {
					if(CurrentGame.Levels[CurrentGame.CurrentLevelNumber]->Map[i][k].element == L'P') {
						CurrentPlatform.length = (k - j + 1); // � ������������� ����� ���������
						CurrentLevel.Map[i][k].element = L' ';
					} else 
						break;
				}
				j = k;
				p++;
			}
			if (this->Levels[this->CurrentLevelNumber]->Map[i][j].element == L'B')	//���� ����������� ������ P, ��		
			{	
				CurrentBall.position.X = j; //������������� ��������� ���������
				CurrentBall.position.Y = i;
				CurrentLevel.Map[i][j].element = L' ';
				j++;
				b++;
			}
		}
	}
	if (!b && !p) {
		CurrentBall.setStandardPosition();
		CurrentPlatform.setStandardPosition();
	}
	if (!this->CurrentLevelName.compare(this->lastLevelName)){
		readConfig();
	}
	return true;
}

bool Game::loadLevelsFromFile()
{
	int nff;
	HANDLE hff;
	std::wstring str = L"LEVELS\\";
	WIN32_FIND_DATA datas;
	hff = FindFirstFile(L"LEVELS\\*.*", &datas);
	nff = FindNextFile(hff, &datas);
	if (hff != INVALID_HANDLE_VALUE) 
	{
		for (;;)
		{
			nff = FindNextFile(hff, &datas);
			if (!nff)
				break;
			this->createLevel((str.append(datas.cFileName)).c_str());
			str = L"LEVELS\\";
		}
	} else 
		return false;
	FindClose(hff);
	return true;
}


void Game::End() {
	KillTimer(hWnd, GamePlayTimer);
	int i = MessageBox(hWnd, L"��������� ����", 
		L"����������", MB_YESNO | MB_ICONQUESTION
		);
	if (i == IDYES) {
		this->saveStatus = 1;
	} else {
		this->saveStatus = 0;
	}

	saveConfig();
	CurrentGame.setStandard();
	CurrentPlatform.setStandard();
	CurrentPlatform.setStandardPosition();
	CurrentBall.setStandard();
	readConfig();
	SetTimer(hWnd, GamePlayTimer, CurrentGame.FPS, NULL);
	showMode = 0;
}

void Game::Menu() {
	InvalidateRect(hWnd, NULL, TRUE);
}
void Game::printMenu(int sx, int sy) {
	TEXTMETRICW tm;
	HFONT newfont, oldfont;
	tm.tmInternalLeading = 0;
	tm.tmDescent = 0;
	tm.tmExternalLeading = 0;
	int curTextPosX = (int)(sx / 5), curTextPosY = (int)(sy / 5);
	SetBkColor(hdc, RGB(200,200,200));
	SetTextColor(hdc, RGB(0,0,0));
	newfont = CreateFontW(30, 20, 0, 0, 500, 0, 0, 0, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");	
	oldfont = (HFONT) SelectObject(hdc, newfont);
	GetTextMetricsW(hdc, &tm);	
	//���������� ���� ��� ����������� ������� ��� ������;
	curTextPosY = curTextPosY - CurrentGame.CurrentLevelNumber * ( tm.tmHeight + tm.tmExternalLeading);
	for (int i = 0; i < CurrentGame.Levels.size(); i++) {
		if(this->CurrentLevelNumber == this->Levels[i]->number)
			SetTextColor(hdc, RGB(100, 220, 220));
		else
			SetTextColor(hdc, RGB(0, 0, 0));
		TextOutW(hdc, curTextPosX, curTextPosY, this->Levels[i]->name.c_str(), this->Levels[i]->name.length());
		curTextPosY += tm.tmExternalLeading + tm.tmHeight;
	}
	SelectObject(hdc, oldfont);
	DeleteObject(newfont);	
}
bool Game::CurrentLeveNumberControl(int num){
	if (num >= 0 && num < CurrentGame.Levels.size())		
		return true;
	else
		return false;
}

void Game::Shooting(){
	int chance = rand() % 100;
	if (chance >30 && chance < 33){
		int x = rand() % CurrentLevel.Size_Columns;
		int y = rand() % CurrentLevel.Size_Strings;
		if (CurrentLevel.Map[y][x].element == CurrentLevel.back) 
		{
			CurrentLevel.Map[y][x].element = L'b';
		}
	}
}

void Game::BlackBlockMoving(){
	for (int i = 0; i < CurrentLevel.Size_Strings; i++)
	{
		for (int j = 0; j < CurrentLevel.Size_Columns; j++)
		{
			int X = j, Y = i;
			if (CurrentLevel.Map[Y][X].element == L'b'){
			COORD course;
			course.X = 1 + rand() % 3 - 2;
			course.Y = 1 + rand() % 3 - 2;

			// ��������� ������ �� �����!
			if ((X <= 0) && (course.X < 0)) {
				CurrentLevel.Map[Y][X].element = L' ';			
				break;
			}
			if ((Y <= 0) && (course.Y < 0)) {
				CurrentLevel.Map[Y][X].element = L' ';			
				break;
			}
			if ((X >= (CurrentLevel.Size_Columns - 1)) && (course.X > 0)) {
				CurrentLevel.Map[Y][X].element = L' ';			
				break;
			}
			if (Y == (CurrentLevel.Size_Strings - 1)) {
				CurrentLevel.Map[Y][X].element = L' ';			
				break;
			}
			CurrentLevel.Map[Y][X].element = L'G';
				if (course.X > 0) {
					X++;
				}else {
					X--;
				}
				if (course.Y > 0) {
					Y++;
				}else {
					Y--;
				}
			if (Y <= 0){
				CurrentLevel.Map[Y][X].element = L' ';			
				break;
			}
			if (CurrentLevel.Map[Y][X].element == CurrentLevel.back)
				CurrentLevel.Map[Y][X].element = L'b';
			}
		}
	}
}