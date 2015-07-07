#pragma once
#include "Level.h"

class Game {
public:
	int lifes; //�����
	long points; // ���� ������
	int speed; // ������� �������� ����
	int maxSpeed; // ������������ �������� ����
	int minSpeed; // ��������� �������� ����
	wchar_t stopSymbol; // ������, �� ������� �� ������� ���� �����������!
	wchar_t pauseSymbol; // ������ �����!
	int saveStatus; // ������ ����������: 0 - ����� ����, 1 - ��������
	int FPS; //���������� ������
	std::vector <Level*> Levels; // ��������� �� ������
	HBRUSH RedBlackBrush;
	HBRUSH RedLightBrush;
	HBRUSH GreenBlackBrush;
	HBRUSH GreenLightBrush;
	HBRUSH BlueBlackBrush;
	HBRUSH BlueLightBrush;
	HBRUSH YellowBlackBrush;
	HBRUSH YellowLightBrush;
	HBRUSH GreyBlackBrush;
	HBRUSH GreyLightBrush;
	HBRUSH White;
	HBRUSH Black;

	int CurrentLevelNumber;
	LPCWSTR CurrentLevelName;
	Game();
	~Game();
	void setStandard() { // ������������� ��������� ��������
		this->FPS = 30;
		minSpeed = 1000;
		maxSpeed = 50;
		stopSymbol = 113; //������ ������������ ����
		pauseSymbol = 32; // 
		lifes = 3; //���������� ������
		points = 0; //��������� ����
		speed = minSpeed; //��������� ��������
		saveStatus = 0; //0 - new, 1 - load
		this->CurrentLevelNumber = 0; //������������� �������� �������� ������ �� 0
		this->CurrentLevelName = L"Default"; // ��� ������������ ������
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
	
	bool loadLevelsFromFile();
	bool loadCurrentLevelByNumber();
	bool createLevel(LPCWSTR LName); //��������� ������� � ����������� �� �����
	void increasePoints(wchar_t c); // ����������� ���� � ����������� �� ��������
	void speedUp(int spd); // �������� ��������
	void setLifes(); //�������� ���������� �������
	void render(int sx, int sy); //������ ���
	void destroyBlock(int y, int x); // ��������� ����������� ������
	void printInfo();
	void Play(); // ������ ����
	void End(); //����� ������!
};
