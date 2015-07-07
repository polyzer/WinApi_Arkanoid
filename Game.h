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
	std::vector <Level*> Levels; // ��������� �� ������...
	int CurrentLevelNumber;
	LPCWSTR CurrentLevelName;
	Game();
	~Game();
	void setStandard() { // ������������� ��������� ��������
		this->FPS = 30;
		minSpeed = 1000;
		maxSpeed = 50;
		stopSymbol = 113; //������ ������������ ����
		pauseSymbol = 32;
		lifes = 3;
		points = 0;
		speed = minSpeed; //��������� ��������
		saveStatus = 0; //0 - new, 1 - load
	}
	
	bool loadLevelsFromFile();
	bool loadCurrentLevel();
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
