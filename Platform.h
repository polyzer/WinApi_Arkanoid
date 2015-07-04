#pragma once
#include "arkanoid_includes.h"

extern Game CurrentGame;

struct Platform {
	char symbol; // символы используемые в качестве платформы
	char color; //цвет платформы
	char length; //длина платформы
	COORD position; // координаты левого конца
	Platform() {
		this->setStandard(); //
	}

	void setStandard() { // установка начальных параметров платформы
		this->symbol = 110; //
		this->color = 10; //
		this->length = 3; //
		this->position.X = (CurrentLevel.Size_Columns/2 - 1); // позиция о X
		this->position.Y = (CurrentLevel.Size_Strings - 2); // позиция по Y
	}

	void setPosition(COORD pos) {
		this->position.X = pos.X;
		this->position.Y = pos.Y;
	}
	void setColor(int col) {
		this->color = col;
	}
	bool moveControl(int control);//Глобальная функция проверки перемещения
	bool outOfSize(int control);//Проверка выхода за границы экрана
	bool blockCollision(int control);//Проверка столкновения с блоком
	bool ballCollision(int control);//Проверка столкновения с мячом
	void step(int course); //перемещение
};

