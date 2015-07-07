#pragma once

struct Ball {
	COORD position; // ������� ����
	COORD course; // ����������� ����
	Block block; //����
	int color; //���� ����
	int speed; // ������� ��������
	int timer; //���������� ����������
	int stepNum; //������� �����

	Ball() {
		this->setStandard();
	}

	void setStandard();

	void setPosition(COORD pos) {
		this->position.X = pos.X;
		this->position.Y = pos.Y;
	}
	void step(); // ��� ����
	void setCourse(int side); //1 - ������, 0 - �����
	bool collision(); //������������ � ����� �� ������� ����
	bool screenOut();
	bool platformCollision();
	void speedControl(); //�������� ��������
	void speedUp(int spd);
};
