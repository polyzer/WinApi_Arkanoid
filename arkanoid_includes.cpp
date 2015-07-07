#pragma once
#include "arkanoid_includes.h"

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>,
std::allocator<TCHAR> > String;

std::string ws2mb( LPCWSTR src) {
	 UINT CodePage = CP_ACP; 
    int cch = WideCharToMultiByte( CodePage, 0, src, -1, 0, 0, 0, 0 );
    
    if( cch == 0 ) 
        return std::string();
 
    std::string data;
    data.resize( cch );
 
    cch = WideCharToMultiByte( CodePage, 0, src, -1, &data[0], (DWORD)data.size(), 0, 0 );
    return cch ? data : std::string();
}

HDC hdc;
HWND hWnd; // ���������� �������� ���� ���������
MSG msg; // ��������� ��� �������� ���������
WNDCLASS wc; // ����� ����
Game CurrentGame; // ������ ������� ����
Level CurrentLevel; // ������� �������
Platform CurrentPlatform;// ������ ���������
Ball CurrentBall; //������ ����
//������� ������� �������������� CurrentGame ����������. ������� �� ������������

wchar_t config_file_name_ca[] = L"config.cnf"; //���� ������������
//DWORD FILE_PATH_BUF_DW = 255;
//wchar_t FILE_PATH_ca [255];
HPEN hpen;


void setElementColor(wchar_t elem){
	switch(elem) 
	{
		case L' ':
			hpen = (HPEN) GetStockObject(NULL_PEN);	
		break;
		default:
			hpen = (HPEN) 	GetStockObject(BLACK_PEN);
		break;
	}
	SelectObject(hdc, hpen);
}

bool createConfig() //�������� ����� ������������
{
	FILE *config_Fp;
	if ((config_Fp = _wfopen(config_file_name_ca, L"w")) != NULL)
	{
	  MessageBox(hWnd, L"���������������� ���� ������", 
		L"���������������� ����", MB_OK | MB_ICONQUESTION
	  );
		return true;
	} else {
		MessageBox(hWnd, L"�� ������� ������� ���������������� ����!!!!", 
			L"���������������� ����", MB_OK | MB_ICONQUESTION
		);
		return false;
	}


}

bool saveConfig() // ���������� ������������ ��� ������
{
	FILE *file_Fp;
	if ((file_Fp = _wfopen(config_file_name_ca, L"w")) != NULL)
	{
		fwprintf(file_Fp, L"%i \n", CurrentGame.lifes);
		fwprintf(file_Fp, L"%i \n", CurrentGame.points);
		fwprintf(file_Fp, L"%i \n", CurrentBall.speed);
		fwprintf(file_Fp, L"%i \n", CurrentBall.timer);
		fwprintf(file_Fp, L"%i \n", CurrentBall.stepNum);
		fwprintf(file_Fp, L"%i %i \n", CurrentBall.position.X, CurrentBall.position.Y);
		fwprintf(file_Fp, L"%i %i \n", CurrentBall.course.X, CurrentBall.course.Y);
		fwprintf(file_Fp, L"%i %i \n", CurrentPlatform.position.X, CurrentPlatform.position.Y);
		fwprintf(file_Fp, L"%s\n", CurrentLevel.name);
		fwprintf(file_Fp, L"%i \n", CurrentGame.saveStatus);
		for (int i = 0; i < CurrentLevel.Size_Strings; i++)
		{
			for (int j = 0; j < CurrentLevel.Size_Columns; j++)
			{
				fwprintf(file_Fp, L"%c", CurrentLevel.Map[i][j]);
			}
			fwprintf(file_Fp, L"\n");
		}
		fclose(file_Fp);
		return true;
	} else {

		system("cls");
		printf("�� ������� �������� ���������������� ������!!!");
		fclose(file_Fp);
		return false;
	}
}

bool readConfig() // ������ � �������� ������������
{
	FILE *file_Fp;
	if ((file_Fp = _wfopen(config_file_name_ca, L"r")) != NULL)
	{
		//����������!!!
		fwscanf(file_Fp, L"%i", &CurrentGame.lifes);
		fwscanf(file_Fp, L"%i", &CurrentGame.points);
		fwscanf(file_Fp, L"%i", &CurrentBall.speed);
		fwscanf(file_Fp, L"%i", &CurrentBall.timer);
		fwscanf(file_Fp, L"%i", &CurrentBall.stepNum);
		fwscanf(file_Fp, L"%i %i", &CurrentBall.position.X, &CurrentBall.position.Y);
		fwscanf(file_Fp, L"%i %i", &CurrentBall.course.X, &CurrentBall.course.Y);
		fwscanf(file_Fp, L"%i %i", &CurrentPlatform.position.X, &CurrentPlatform.position.Y);
		fseek(file_Fp, 2, SEEK_CUR);
		fwscanf(file_Fp, L"%s", &CurrentGame.CurrentLevelNumber);
		fwscanf(file_Fp, L"%i", &CurrentGame.saveStatus);
		fseek(file_Fp, 3, SEEK_CUR);
		if (CurrentGame.saveStatus == 1) {
			for (int i = 0; i < CurrentLevel.Size_Strings; i++) {
				for (int j = 0; j < CurrentLevel.Size_Columns; j++) {
					fwscanf(file_Fp, L"%c", &CurrentLevel.Map[i][j]);
				}
				fseek(file_Fp, 2, SEEK_CUR);
			}

		} else if (CurrentGame.saveStatus == 0) {
			CurrentGame.loadCurrentLevel(); // ����� ����
		}
		fclose(file_Fp);
		return true;
	} else {
		if (createConfig()) {
			if ((file_Fp = _wfopen(config_file_name_ca, L"r")) != NULL)
			{
				// ����������!!!
				fwscanf(file_Fp, L"%i", &CurrentGame.lifes);
				fwscanf(file_Fp, L"%i", &CurrentGame.points);
				fwscanf(file_Fp, L"%i", &CurrentBall.speed);
				fwscanf(file_Fp, L"%i", &CurrentBall.timer);
				fwscanf(file_Fp, L"%i", &CurrentBall.stepNum);
				fwscanf(file_Fp, L"%i %i", &CurrentBall.position.X, &CurrentBall.position.Y);
				fwscanf(file_Fp, L"%i %i", &CurrentBall.course.X, &CurrentBall.course.Y);
				fwscanf(file_Fp, L"%i %i", &CurrentPlatform.position.X, &CurrentPlatform.position.Y);
				fseek(file_Fp, 2, SEEK_CUR);
				fwscanf(file_Fp, L"%s", &CurrentGame.CurrentLevelName);
				fwscanf(file_Fp, L"%i", &CurrentGame.saveStatus);
				if (CurrentGame.saveStatus == 1) {
					for (int i = 0; i < CurrentLevel.Size_Strings; i++) {
						for (int j = 0; j < CurrentLevel.Size_Columns; j++) {
							fwscanf(file_Fp, L"%c", &CurrentLevel.Map[i][j]);
						}
						fseek(file_Fp, 2, SEEK_CUR);
					}
				} else if (CurrentGame.saveStatus == 0) {
					CurrentGame.CurrentLevelNumber = 0;
					CurrentGame.loadCurrentLevel();
			   	    MessageBox(hWnd, L"����� ����!", 
					L"����", MB_OK | MB_ICONQUESTION
					);	
				}
				fclose(file_Fp);
				return true;
			} else {
		  	    MessageBox(hWnd, L"���������������� ���� ����������, �� �� ���� ���������� ������� ������!", 
				L"���������������� ����", MB_OK | MB_ICONQUESTION
				);	
				fclose(file_Fp);
				return false;
			}
		} else {
	 	    MessageBox(hWnd, L"�� ������� �������� � ��������� ������!", 
			L"������", MB_OK | MB_ICONQUESTION
			);	
			return false;
		}
	}
}
