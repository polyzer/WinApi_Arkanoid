#pragma once
#include "arkanoid_includes.h"

class Level {
public:
	int Size_Strings;// размер по Y
	int Size_Columns;//размер по X
	int number; // номер уровня
    std::string name;
	char back; // background
	char **Map; // карта уровня
	int minSpeedTime; //начальная скорость шара на уровне
	int maxSpeedTime; //максимальная скорость шара на уровне
	int stepNorm; // количество шагов шара для изменения скорости
	Level(){};
	Level(std::string LName);
	~Level();
	void setStandard() {
		this->Size_Strings = 10;
		this->Size_Columns = 20;
		this->number = 0; // устанавливаем первый уровень
		//system("pause");
		this->back = 32;
		this->minSpeedTime = 30;
		this->maxSpeedTime = 7;
		this->stepNorm = 5;
	}
	void setNullLevel();
	void reMap(bool init); // задаем количество строк и количество столбцов.
	void End(bool status); // отслеживает окончание уровня
	bool allBlocksDestroyed(); // отслеживает уничтожение блоков
};
