#pragma once

extern Game CurrentGame;
extern Level CurrentLevel;

struct Platform {
	wchar_t symbol; // ������� ������������ � �������� ���������
	wchar_t color; //���� ���������
	wchar_t length; //����� ���������
	COORD position; // ���������� ������ �����
	Platform() {
		this->setStandard(); //
	}

	void setStandard() { // ��������� ��������� ���������� ���������
		this->symbol = 110; //
		this->color = 10; //
		this->length = 3; //
		this->position.X = (CurrentLevel.Size_Columns/2 - 1); // ������� � X
		this->position.Y = (CurrentLevel.Size_Strings - 2); // ������� �� Y
	}

	void setPosition(COORD pos) {
		this->position.X = pos.X;
		this->position.Y = pos.Y;
	}
	bool moveControl(int control);//���������� ������� �������� �����������
	bool outOfSize(int control);//�������� ������ �� ������� ������
	bool blockCollision(int control);//�������� ������������ � ������
	bool ballCollision(int control);//�������� ������������ � �����
	void step(int course); //�����������
};

