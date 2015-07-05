#pragma once
#include "Level.h"

class Game {
public:
	int lifes; //�����
	long points; // ���� ������
	int speed; // ������� �������� ����
	int maxSpeed; // ������������ �������� ����
	int minSpeed; // ��������� �������� ����
	char stopSymbol; // ������, �� ������� �� ������� ���� �����������!
	char pauseSymbol; // ������ �����!
	int saveStatus; // ������ ����������: 0 - ����� ����, 1 - ��������
	int FPS; //���������� ������
	std::vector <Level> Levels;
	int CurrentLevelNumber;
	std::string CurrentLevelName;
	Game() {
		this->setStandard();
	}

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
	bool createLevel(std::string LName); //��������� ������� � ����������� �� �����
	void increasePoints(char c); // ����������� ���� � ����������� �� ��������
	void speedUp(int spd); // �������� ��������
	void setLifes(); //�������� ���������� �������
	void render(HDC hdc, int sx, int sy); //������ ���
	void destroyBlock(int y, int x); // ��������� ����������� ������
	void printInfo();
	void Play(); // ������ ����
	void End(); //����� ������!
};
