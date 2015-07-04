#pragma once
#include "arkanoid_includes.h"

class Level {
public:
	int Size_Strings;// ������ �� Y
	int Size_Columns;//������ �� X
	int number; // ����� ������
    std::string name;
	char back; // background
	char **Map; // ����� ������
	int minSpeedTime; //��������� �������� ���� �� ������
	int maxSpeedTime; //������������ �������� ���� �� ������
	int stepNorm; // ���������� ����� ���� ��� ��������� ��������
	Level(){};
	Level(std::string LName);
	~Level();
	void setStandard() {
		this->Size_Strings = 10;
		this->Size_Columns = 20;
		this->number = 0; // ������������� ������ �������
		//system("pause");
		this->back = 32;
		this->minSpeedTime = 30;
		this->maxSpeedTime = 7;
		this->stepNorm = 5;
	}
	void setNullLevel();
	void reMap(bool init); // ������ ���������� ����� � ���������� ��������.
	void End(bool status); // ����������� ��������� ������
	bool allBlocksDestroyed(); // ����������� ����������� ������
};
