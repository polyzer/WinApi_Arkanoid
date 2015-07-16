#pragma once

extern Game CurrentGame;
extern Level CurrentLevel;

struct Platform {
	Block block; // ������� ������������ � �������� ���������
	wchar_t color; //���� ���������
	wchar_t length; //����� ���������
	COORD position; // ���������� ������ �����
	Platform() {
		this->setStandard(); //
		this->length = 3; //
		this->position.X = (CurrentLevel.Size_Columns/2 - 1); // ������� � X
		this->position.Y = (CurrentLevel.Size_Strings - 2); // ������� �� Y
	}
	void setStandard() { // ��������� ��������� ���������� ���������
		this->block.element = L'P'; //
		this->color = 10; //
	}

	void setStandardPosition() {
		this->position.X = 0; // ������� � X
		this->position.Y = (CurrentLevel.Size_Strings - 1); // ������� �� Y
	}
	bool moveControl(int control);//���������� ������� �������� �����������
	bool outOfSize(int control);//�������� ������ �� ������� ������
	bool blockCollision(int control);//�������� ������������ � ������
	bool ballCollision(int control);//�������� ������������ � �����
	bool withCollision(int x, int y);//�������� ������������ � ����� ��������
	void step(int course); //�����������
};

