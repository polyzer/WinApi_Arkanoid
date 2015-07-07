#pragma once
#include "arkanoid_includes.h"

extern Platform CurrentPlatform;

bool Ball::screenOut(){
/*	if ((this->position.X <= 0) && (this->course.X < 0)) {
		return true;
	}*/
	if ((this->position.Y <= 0)) {
		return true;
	}
//	if (this->position.X >= (CurrentLevel.Size_Columns - 1)) {
//		return true;
//	}
	return false;
}

bool Ball::platformCollision() {
	//������������ � ����������!
	if ((this->position.X >= CurrentPlatform.position.X && //���� ����� ��������� ��� ���������� � ���� � ���
		 this->position.X < (CurrentPlatform.position.X + CurrentPlatform.length)) &&
		 (this->position.Y == (CurrentPlatform.position.Y - 1))
	 )
	{
		return true;
	}
	//������������ � ���������� �� ����������
	if(
		(this->position.X == (CurrentPlatform.position.X - 1)) &&
		(this->position.Y == (CurrentPlatform.position.Y - 1))
	) {
		return true;
	}
	if(
		(((this->position.X) == (CurrentPlatform.position.X + CurrentPlatform.length))) &&
		((this->position.Y) == (CurrentPlatform.position.Y - 1))
	) {
		return true;
	}
	return false;
	// ����� ��������� ������������ � ����������

}

bool Ball::collision() {
	if (this->platformCollision() && this->screenOut()) {
		return false;
	}
	// ��������� ������ �� �����!
	if ((this->position.X <= 0) && (this->course.X < 0)) {
		this->course.X = -(this->course.X);
	}
	if ((this->position.Y <= 0) && (this->course.Y < 0)) {
		this->course.Y = -(this->course.Y);
	}
	if ((this->position.X >= (CurrentLevel.Size_Columns - 1)) && (this->course.X > 0)) {
		this->course.X = -(this->course.X);
	}
	if (this->position.Y == (CurrentLevel.Size_Strings - 1)) {
		// ��������!!!!
		CurrentGame.lifes--;
		this->setStandard(); //��������� ���������� ��������� ����
		CurrentPlatform.setStandard(); //��������� ���������� ��������� ���������
		if (CurrentGame.lifes == 0) {
		//	 ��������� ����� ����!
			CurrentLevel.End(false);
		}
	}
	//����� ��������� ������ �� �����
	//������������ � ����������!
	if ((this->position.X >= CurrentPlatform.position.X && //���� ����� ��������� ��� ���������� � ���� � ���
		 this->position.X < (CurrentPlatform.position.X + CurrentPlatform.length)) &&
		 (this->position.Y == (CurrentPlatform.position.Y - 1)) &&
		  (this->course.Y > 0)
		 )
	{
		this->course.Y = -(this->course.Y);
	}
	if ((this->position.X >= CurrentPlatform.position.X &&
		 this->position.X < (CurrentPlatform.position.X + CurrentPlatform.length)) &&
		 (this->position.Y == (CurrentPlatform.position.Y + 1)) &&
		  (this->course.Y < 0)
		 )
	{
		this->course.Y = -(this->course.Y);
	}
	if ((this->position.X == (CurrentPlatform.position.X - 1)
		) && (this->position.Y == CurrentPlatform.position.Y)
		&& (this->course.X > 0)
	) {
		this->course.X = -(this->course.X);
	}
	if ((this->position.X == (CurrentPlatform.position.X + CurrentPlatform.length)
		) && this->position.Y == CurrentPlatform.position.Y
		&& (this->course.X < 0)
	) {
		this->course.X = -(this->course.X);
	}
	//������������ � ���������� �� ����������
	if(
		(this->position.X == (CurrentPlatform.position.X - 1)) &&
		(this->position.Y == (CurrentPlatform.position.Y - 1)) &&
		(this->course.X > 0 && this->course.Y > 0)
	) {
		this->course.X = -(this->course.X);
		this->course.Y = -(this->course.Y);
	}
	if(
		(((this->position.X) == (CurrentPlatform.position.X + CurrentPlatform.length))) &&
		((this->position.Y) == (CurrentPlatform.position.Y - 1)) &&
		(this->course.X < 0 && this->course.Y > 0)
	) {
		this->course.X = -(this->course.X);
		this->course.Y = -(this->course.Y);
	}
	if(
		(this->position.X == (CurrentPlatform.position.X + CurrentPlatform.length)) &&
		(this->position.Y == (CurrentPlatform.position.Y + 1)) &&
		(this->course.X < 0 && this->course.Y < 0)
	) {
		this->course.X = -(this->course.X);
		this->course.Y = -(this->course.Y);
	}
	if(
		(this->position.X == (CurrentPlatform.position.X - 1)) &&
		(this->position.Y == (CurrentPlatform.position.Y + 1)) &&
		(this->course.X > 0 && this->course.Y < 0)
	) {
		this->course.X = -(this->course.X);
		this->course.Y = -(this->course.Y);
	}
	// ����� ��������� ������������ � ����������
	//������������ � �������
	int i = 0; //������� ������������
	if (!(this->position.Y - 1 < 0)) // �������� �������� ���������, ����� �� ���� �� ������� ������� (-1).
		if ((CurrentLevel.Map[this->position.Y - 1][this->position.X] !=
			 CurrentLevel.back) &&
			 (this->course.Y < 0)) {
			CurrentGame.points += 100; // ���� �� ������������
			CurrentLevel.Map[this->position.Y - 1][this->position.X] = CurrentLevel.back;
			this->course.Y = -(this->course.Y);
			i++;
		}
	if ((CurrentLevel.Map[this->position.Y][this->position.X + 1] !=
         CurrentLevel.back) &&
         (this->course.X > 0)) {
		CurrentGame.points += 100; // ���� �� ������������
		CurrentLevel.Map[this->position.Y][this->position.X + 1] = CurrentLevel.back;
		this->course.X = -(this->course.X);
		i++;
	}
	if ((CurrentLevel.Map[this->position.Y + 1][this->position.X] !=
         CurrentLevel.back) &&
         (this->course.Y > 0)) {
		CurrentGame.points += 100; // ���� �� ������������
		CurrentLevel.Map[this->position.Y + 1][this->position.X] = CurrentLevel.back;
		this->course.Y = -(this->course.Y);
		i++;
	}
	if ((CurrentLevel.Map[this->position.Y][this->position.X - 1]) !=
         CurrentLevel.back &&
         (this->course.X < 0)) {
		CurrentGame.points += 100; // ���� �� ������������
		CurrentLevel.Map[this->position.Y][this->position.X - 1] = CurrentLevel.back;
		this->course.X = -(this->course.X);
		i++;
	}
	//������������ �� ���������
	if (i == 0) { //���� �� ��������� ������������ �� �����������/���������, �� ������������ ������������
		if (CurrentLevel.Map[this->position.Y + 1][this->position.X + 1] != CurrentLevel.back &&
			(this->course.X > 0) && (this->course.Y > 0) // ���� ���� ������ �� ����������� � ���� ��������� � ��� ���� ������ + ����
		) {
			CurrentGame.points += 100;// ���� �� ������������
			CurrentLevel.Map[this->position.Y + 1][this->position.X + 1] = CurrentLevel.back;
			i++;
		}
		if ((this->position.Y - 1) >= 0)
			if (CurrentLevel.Map[this->position.Y - 1][this->position.X + 1] != CurrentLevel.back &&
				(this->course.X > 0) && (this->course.Y < 0) // ���� ���� ������ �� ����������� � ���� ��������� � ��� ���� ������ + �����
			) {
				CurrentGame.points += 100;// ���� �� ������������
				CurrentLevel.Map[this->position.Y - 1][this->position.X + 1] = CurrentLevel.back;
				i++;
			}
		if ((this->position.Y - 1) >= 0)
			if (CurrentLevel.Map[this->position.Y - 1][this->position.X - 1] != CurrentLevel.back &&
				(this->course.X < 0) && (this->course.Y < 0) // ���� ���� ����� �� ����������� � ���� ��������� � ��� ���� ����� + ����
			) {
				CurrentGame.points += 100;// ���� �� ������������
				CurrentLevel.Map[this->position.Y - 1][this->position.X - 1] = CurrentLevel.back;
				i++;
			}
		if (CurrentLevel.Map[this->position.Y + 1][this->position.X - 1] != CurrentLevel.back &&
			(this->course.X < 0) && (this->course.Y > 0) // ���� ���� ����� �� ����������� � ���� ��������� � ��� ���� ����� + �����
		) {
			CurrentGame.points += 100; // ���� �� ������������
			CurrentLevel.Map[this->position.Y + 1][this->position.X - 1] = CurrentLevel.back;
			i++;
		}
		if (i != 0) {
			this->course.Y = -(this->course.Y);
			this->course.X = -(this->course.X);
		}
	}
	return true;
	//����� ��������� ������������ � �������

}

void Ball::step(){
	if (this->course.X > 0) {
		this->position.X++;
	}else {
		this->position.X--;
	}
	if (this->course.Y > 0) {
		this->position.Y++;
	}else {
		this->position.Y--;
	}

}

void Ball::setStandard() {//��������� ���������� ��������� ����
		this->course.X = 1; // 1 - ������, -1 - �����
		this->course.Y = -1;// 1 - ����, -1 - �����
		this->position.X = (CurrentLevel.Size_Columns/2);
		this->position.Y = (CurrentLevel.Size_Strings/2);
		this->symbol = 4;
		this->speed = CurrentLevel.minSpeedTime;
		this->timer = 0;
		this->stepNum = 0;
	}
////////////

void Ball::speedUp(int spd) {
	if (this->speed >= CurrentLevel.maxSpeedTime)
		this->speed -= spd;
}
bool Level::allBlocksDestroyed() {
	for(int i = 0; i < CurrentLevel.Size_Strings; i++) {
		for(int j = 0; j < CurrentLevel.Size_Columns; j++){
			if (this->Map[i][j] != this->back) {
				return false;
			}
		}
	}
	return true;
}
