#pragma once
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <clocale>
#include <cstdio>
#include <conio.h>
#include <string>
#include <vector>
#include "Game.h"
#include "Level.h"
#include "Ball.h"
#include "Platform.h"
#include "Menu.h"

bool createConfig();
bool saveConfig();
bool readConfig();
std::string ws2mb( LPCWSTR src);
void setElementColor(char elem);