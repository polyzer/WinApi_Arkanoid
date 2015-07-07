#pragma once

class Level {
public:
	int Size_Strings;// ������ �� Y
	int Size_Columns;//������ �� X
	int number; // ����� ������
    LPCWSTR name;
	bool init;
	wchar_t back; // background
	wchar_t **Map; // ����� ������
	int minSpeedTime; //��������� �������� ���� �� ������
	int maxSpeedTime; //������������ �������� ���� �� ������
	int stepNorm; // ���������� ����� ���� ��� ��������� ��������
	Level();
	~Level();
	void setStandard() {
		this->Size_Strings = 10;
		this->Size_Columns = 20;
		this->number = 0; // ������������� ������ �������
		//system("pause");
		this->back = L' ';
		this->minSpeedTime = 30;
		this->maxSpeedTime = 7;
		this->stepNorm = 5;
		this->name = L"Auto";
		this->init = 1;
	}
	void setNullLevel();
	void reMap(); // ������ ���������� ����� � ���������� ��������.
	void End(bool status); // ����������� ��������� ������
	bool allBlocksDestroyed(); // ����������� ����������� ������
};
