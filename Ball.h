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
	void setPosition(int x, int y) {
		this->position.X = x;
		this->position.Y = y;
	}
	void setStandardPosition();
	void step(); // ��� ����
	void setCourse(int hor_course, int ver_course); //1 - ������, 0 - �����
	void genCourse();
	bool collision(); //������������ � ����� �� ������� ����
	bool screenOut();
	bool platformCollision();
	void speedControl(); //�������� ��������
	void speedUp(int spd);
};
