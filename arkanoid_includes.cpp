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

HWND hWnd; // ���������� �������� ���� ���������
MSG msg; // ��������� ��� �������� ���������
WNDCLASS wc; // ����� ����
Platform CurrentPlatform;// ������ ���������
Game CurrentGame; // ������ ������� ����
Ball CurrentBall; //������ ����
Level CurrentLevel; // ������� �������
//������� ������� �������������� CurrentGame ����������. ������� �� ������������

char config_file_name_ca[] = "config.cnf"; //���� ������������
//DWORD FILE_PATH_BUF_DW = 255;
//char FILE_PATH_ca [255];

void setElementColor(char elem){
}

bool createConfig() //�������� ����� ������������
{
	FILE *config_Fp;
	if ((config_Fp = fopen(config_file_name_ca, "w")) != NULL)
	{
	  MessageBox(hWnd, _T("���������������� ���� ������"), 
		_T("���������������� ����"), MB_OK | MB_ICONQUESTION
	  );
		return true;
	} else {
		MessageBox(hWnd, _T("�� ������� ������� ���������������� ����!!!!"), 
			_T("���������������� ����"), MB_OK | MB_ICONQUESTION
		);
		return false;
	}


}

bool saveConfig() // ���������� ������������ ��� ������
{
	FILE *file_Fp;
	if ((file_Fp = fopen(config_file_name_ca, "w")) != NULL)
	{
		fprintf(file_Fp, "%i \n", CurrentGame.lifes);
		fprintf(file_Fp, "%i \n", CurrentGame.points);
		fprintf(file_Fp, "%i \n", CurrentBall.speed);
		fprintf(file_Fp, "%i \n", CurrentBall.timer);
		fprintf(file_Fp, "%i \n", CurrentBall.stepNum);
		fprintf(file_Fp, "%i %i \n", CurrentBall.position.X, CurrentBall.position.Y);
		fprintf(file_Fp, "%i %i \n", CurrentBall.course.X, CurrentBall.course.Y);
		fprintf(file_Fp, "%i %i \n", CurrentPlatform.position.X, CurrentPlatform.position.Y);
		fprintf(file_Fp, "%s \n", CurrentGame.CurrentLevelName);
		fprintf(file_Fp, "%i \n", CurrentGame.saveStatus);
		for (int i = 0; i < CurrentLevel.Size_Strings; i++)
		{
			for (int j = 0; j < CurrentLevel.Size_Columns; j++)
			{
				fprintf(file_Fp, "%c", CurrentLevel.Map[i][j]);
			}
			fprintf(file_Fp, "\n");
		}
		fclose(file_Fp);
		system("cls");
		printf("������ ���������!");
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
	if ((file_Fp = fopen(config_file_name_ca, "r")) != NULL)
	{
		//����������!!!
		fscanf(file_Fp, "%i", &CurrentGame.lifes);
		fscanf(file_Fp, "%i", &CurrentGame.points);
		fscanf(file_Fp, "%i", &CurrentBall.speed);
		fscanf(file_Fp, "%i", &CurrentBall.timer);
		fscanf(file_Fp, "%i", &CurrentBall.stepNum);
		fscanf(file_Fp, "%i %i", &CurrentBall.position.X, &CurrentBall.position.Y);
		fscanf(file_Fp, "%i %i", &CurrentBall.course.X, &CurrentBall.course.Y);
		fscanf(file_Fp, "%i %i", &CurrentPlatform.position.X, &CurrentPlatform.position.Y);
		fseek(file_Fp, 2, SEEK_CUR);
		fscanf(file_Fp, "%s", &CurrentGame.CurrentLevelNumber);
		fscanf(file_Fp, "%i", &CurrentGame.saveStatus);
		fseek(file_Fp, 3, SEEK_CUR);
		if (CurrentGame.saveStatus == 1) {
			for (int i = 0; i < CurrentLevel.Size_Strings; i++) {
				for (int j = 0; j < CurrentLevel.Size_Columns; j++) {
					fscanf(file_Fp, "%c", &CurrentLevel.Map[i][j]);
				}
				fseek(file_Fp, 2, SEEK_CUR);
			}
			printf("��������� ������� ����!\n");
			system("pause");
			system("cls");
		} else if (CurrentGame.saveStatus == 0) {
			CurrentGame.loadCurrentLevel(); // ����� ����
		}
		fclose(file_Fp);
		return true;
	} else {
		if (createConfig()) {
			if ((file_Fp = fopen(config_file_name_ca, "r")) != NULL)
			{
				// ����������!!!
				fscanf(file_Fp, "%i", &CurrentGame.lifes);
				fscanf(file_Fp, "%i", &CurrentGame.points);
				fscanf(file_Fp, "%i", &CurrentBall.speed);
				fscanf(file_Fp, "%i", &CurrentBall.timer);
				fscanf(file_Fp, "%i", &CurrentBall.stepNum);
				fscanf(file_Fp, "%i %i", &CurrentBall.position.X, &CurrentBall.position.Y);
				fscanf(file_Fp, "%i %i", &CurrentBall.course.X, &CurrentBall.course.Y);
				fscanf(file_Fp, "%i %i", &CurrentPlatform.position.X, &CurrentPlatform.position.Y);
				fseek(file_Fp, 2, SEEK_CUR);
				fscanf(file_Fp, "%s", &CurrentGame.CurrentLevelName);
				fscanf(file_Fp, "%i", &CurrentGame.saveStatus);
				if (CurrentGame.saveStatus == 1) {
					for (int i = 0; i < CurrentLevel.Size_Strings; i++) {
						for (int j = 0; j < CurrentLevel.Size_Columns; j++) {
							fscanf(file_Fp, "%c", &CurrentLevel.Map[i][j]);
						}
						fseek(file_Fp, 2, SEEK_CUR);
					}
				} else if (CurrentGame.saveStatus == 0) {
					CurrentGame.CurrentLevelNumber = 0;
					CurrentGame.loadCurrentLevel();

			   	    MessageBox(hWnd, _T("����� ����!"), 
					_T("����"), MB_OK | MB_ICONQUESTION
					);	
				}
				fclose(file_Fp);
				return true;
			} else {
		  	    MessageBox(hWnd, _T("���������������� ���� ����������, �� �� ���� ���������� ������� ������!"), 
				_T("���������������� ����"), MB_OK | MB_ICONQUESTION
				);	
				fclose(file_Fp);
				return false;
			}
		} else {
	 	    MessageBox(hWnd, _T("�� ������� �������� � ��������� ������!"), 
			_T("������"), MB_OK | MB_ICONQUESTION
			);	
			return false;
		}
	}
}
