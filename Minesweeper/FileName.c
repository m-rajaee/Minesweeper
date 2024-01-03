#include <stdio.h>
#include<time.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#pragma warning (disable:4996)
//---------------------------------------------
// Variables
//---------------------------------------------
int martabe1 = 0, martabe2 = 0;
char beforeP1[8][8] = { 0 };
char beforeP2[16][16] = { 0 };
int check3_1[8];
int check3_2[16];
int timerecord;
int a, b;
int parcham1;
int parcham_karbar1;
int parcham2;
int parcham_karbar2;
char board1[8][8] = { 0 };
char board2[16][16] = { 0 };
char t1[8][8] = { 0 };
char t2[16][16] = { 0 };
char name[50] = { 0 };
char end = ' ';
//---------------------------------------------
//  8 x 8 Functions
//---------------------------------------------
void checkwin1();
void lclick1(int i, int j);
void rclick1(int i, int j);
void reset1();
void printboard1();
void playermove1();
int checkfreespace1();
void open1_1(int i, int j);
void open1_2(int i, int j);
void open1_3(int i, int j);
void open1_4(int i, int j);
//---------------------------------------------
// 16 x 16 Functions
//---------------------------------------------
int checkfreespace2();
void reset2();
void lclick2(int i, int j);
void checkwin2();
void rclick2(int i, int j);
void printboard2();
void playermove2();
void open2_1(int i, int j);
void open2_2(int i, int j);
void open2_3(int i, int j);
void open2_4(int i, int j);
//---------------------------------------------
//   main
//---------------------------------------------
int main() {
	_setmode(_fileno(stdout), _O_U8TEXT);
	srand(time(NULL));
	int total = 0, win = 0, lose = 0;
	wprintf(L"\033[1;96m\t\t\t\tWelcome To The Minesweeper!\033[33m\n\n\n\t\t\tEnter Your Name: \033[0m");
	wprintf(L"\033[1;32m");
	wscanf(L"%[^\n]%*c", name);
	wprintf(L"\033[1;0m");
	while (1) {
		system("cls || clear");
		wprintf(L"\033[1;34m\n\t\tProfile:\n\t\t\t\t     Name : %s\n\t\t\t\t     Total Rounds: %d\n\t\t\t\t     Wins : %d\n\t\t\t\t     Loses : %d\n\n\033[0m", name, total, win, lose);
		wprintf(L"\033[33m\n\n\t\t\t\t     1 . Play\n\n\t\t\t\t     2 . Change Name\n\n\t\t\t\t     3 . Guide \n\n\t\t\t\t     4 . Exit\033[0m");
		int first = getch();
		while (first != '1' && first != '2' && first != '3' && first != '4')
			first = getch();
		if (first == '2') {
			system("cls || clear");
			wprintf(L"\033[33m\n\n\n\t\tEnter The New Name: \033[0m");
			wprintf(L"\033[1;32m");
			wscanf(L"%[^\n]%*c", name);
			wprintf(L"\033[1;0m");
			continue;
		}
		else if (first == '4') {
			system("cls || clear");
			wprintf(L"\033[33m\n\n\t\t\t\t     GoodBye!\n\n\n\n\033[0m");
			exit(0);
			break;
		}
		else if (first == '3') {
			system("cls || clear");
			wprintf(L"\033[33m\n\n\n\t\t\t\tUse \033[96mW-A-S-D\033[33m Keys For Moving\n\n\t\t\t\t\Place Or Remove a Flag : \033[96mSPACE\033[33m\n\n\t\t\t\tChose : \033[96mENTER\033[33m\n\n\t\t\t\tGive up : \033[96mZ\033[33m");
			wprintf(L"\n\n\n\t\t\t\tPress Enter To Return To The Menu");
			int Enter = getch();
			while (Enter != 13)
				Enter = getch();
			if (Enter == 13)
				continue;
		}
		system("cls || clear");
		wprintf(L"\033[33m\n\n\n\n\t\t\t\tSelect Mode :\n\n\t\t\t\t      1 . 8 x 8\n\n\t\t\t\t      2 . 16 x 16\n\033[0m");
		int mode = getch();
		while (mode != '1' && mode != '2')
			mode = getch();
		if (mode == '1') {
			parcham_karbar1 = 10;
			parcham1 = 10;
			reset1();
			end = ' ';
			//timer
			a = clock();
			while (1) {
				if (end == 'z')
					break;
				//timer
				system("cls || clear");
				b = clock();
				if (end == ' ')
					a += (clock() - b);
				///////////
				if (end == ' ' && checkfreespace1() == 1) {
					system("cls || clear");
					wprintf(L"\033[35m\t\t\t\t\t   \u2660%d\033[0m", parcham_karbar1);
					playermove1();

				}
				checkwin1();
				if (end == 'w') {
					if (martabe1 == 0) {
						timerecord = b - a;
						wprintf(L"\033[32m\t\t\t\t     You Won! in \033[96m %d : %d\n\n\n\033[0m", ((b - a) / 1000) / 60, ((b - a) / 1000) % 60);
					}
					else if ((b - a) > timerecord) {
						wprintf(L"\033[32m\t\t\t\t     You Won!\n& Broke Your Time Record (\033[96m%d : %d\033[0m) With \033[96m %d : %d !\n\n\033[0m", (timerecord / 1000) / 60, (timerecord / 1000) % 60, ((b - a) / 1000) / 60, ((b - a) / 1000) % 60);
						timerecord = b - a;
					}
					martabe1 = 1;;
					win++;
					total++;
					break;
				}
				else if (end == 'l') {
					wprintf(L"\a");
					lose++;
					total++;
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (t1[i][j] == '+')
								board1[i][j] = '+';
						}
					}
					system("cls || clear");
					wprintf(L"\033[96m\t\t\t\t\t  %d : %d", ((b - a) / 1000) / 60, ((b - a) / 1000) % 60);
					printboard1();
					wprintf(L"\033[31m\t\t\t\t       You've lost!\n\n\033[0m");
					break;
				}
			}
		}
		else if (mode == '2') {
			parcham_karbar2 = 40;
			parcham2 = 40;
			reset2();
			end = ' ';
			//timer
			a = clock();
			//////
			while (1) {
				if (end == 'z')
					break;
				//timer
				system("cls || clear");
				b = clock();
				if (end == ' ')
					a += (clock() - b);
				///////////
				if (end == ' ' && checkfreespace2() == 1) {
					system("cls || clear");
					wprintf(L"\033[35m\t\t\t\t\t   \u2660%d\033[0m", parcham_karbar2);
					playermove2();
				}
				checkwin2();
				if (end == 'w') {
					if (martabe2 == 0) {
						timerecord = b - a;
						wprintf(L"\033[32m\t\t\t\t     You Won! in \033[96m %d : %d \n\n\n\033[0m", ((b - a) / 1000) / 60, ((b - a) / 1000) % 60);
					}
					else if ((b - a) > timerecord) {
						wprintf(L"\033[32m\t\t\t\t     You Won!\n& Broke Your Time Record (\033[96m%d : %d\033[0m) With \033[96m %d : %d !\n\n\033[0m", (timerecord / 1000) / 60, (timerecord / 1000) % 60, ((b - a) / 1000) / 60, ((b - a) / 1000) % 60);
						timerecord = b - a;
					}
					win++;
					total++;
					break;
				}
				else if (end == 'l') {
					wprintf(L"\a");
					lose++;
					total++;
					for (int i = 0; i < 16; i++) {
						for (int j = 0; j < 16; j++) {
							if (t2[i][j] == '+')
								board2[i][j] = '+';
						}
					}
					system("cls || clear");
					wprintf(L"\033[96m\t\t\t\t\t  %d : %d", ((b - a) / 1000) / 60, ((b - a) / 1000) % 60);
					printboard2();
					wprintf(L"\033[31m\t\t\t\t       You've lost!\n\n\033[0m");
					break;
				}
			}
		}
		wprintf(L"\033[33mDo You Want to Play Again? (Y/N)\033[0m");
		int l = getch();
		while (l != 'Y' && l != 'N' && l != 'y' && l != 'n')
			l = getch();
		if (l == 'y' || l == 'Y')
			continue;
		else if (l == 'n' || l == 'N') {
			wprintf(L"\033[33m\n\nGoodBye!\n\033[0m");
			Sleep(1000);
			break;
		}
	}
}
//---------------------------------------------
// 	8 x 8 Functions
//---------------------------------------------

void open1_1(int i, int j) {
	if (i < 0 || i>7 || j < 0 || j>7)
		return;
	if (t1[i][j] == '+')
		return;
	board1[i][j] = t1[i][j];
	if (board1[i][j + 1] != '-' && board1[i][j + 1] != '0')
		return;
	open1_1(i, j + 1);
}
void open1_2(int i, int j) {
	if (i < 0 || i>7 || j < 0 || j>7)
		return;
	if (t1[i][j] == '+')
		return;
	board1[i][j] = t1[i][j];
	if (board1[i + 1][j] != '-' && board1[i + 1][j] != '0')
		return;
	open1_2(i + 1, j);
}
void open1_3(int i, int j) {
	if (i < 0 || i>7 || j < 0 || j>7)
		return;
	if (t1[i][j] == '+')
		return;
	board1[i][j] = t1[i][j];
	if (board1[i][j - 1] != '-' && board1[i][j - 1] != '0')
		return;
	open1_3(i, j - 1);
}
void open1_4(int i, int j) {
	if (i < 0 || i>7 || j < 0 || j>7)
		return;
	if (t1[i][j] == '+')
		return;
	board1[i][j] = t1[i][j];
	if (board1[i - 1][j] != '-' && board1[i - 1][j] != '0')
		return;
	open1_4(i - 1, j);
}
int checkfreespace1() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board1[i][j] == '-')
				return 1;
		}
	}
	return 0;
}
void checkwin1() {
	if (parcham1 == 0 && checkfreespace1() == 0)
		end = 'w';
}
void reset1() {
	for (int j = 0; j < 8; j++) {
		check3_1[j] = 0;
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board1[i][j] = '-';
			t1[i][j] = '-';
		}
	}
	int c = 0;
	while (c < 10) {
		int i = rand() % 8;
		int j = rand() % 8;
		if (t1[i][j] == '-' && check3_1[j] < 3) {
			t1[i][j] = '+';
			check3_1[j]++;
			c++;
		}
	}
	c = 0;
	while (c < 14) {
		int i = rand() % 8;
		int j = rand() % 8;
		if (t1[i][j] == '-') {
			t1[i][j] = '0';
			c++;
		}
	}
	c = 0;
	while (c < 40) {
		int bomb = 0;
		int i = rand() % 8;
		int j = rand() % 8;
		if (t1[i][j] == '-') {
			if (i == 0 && j == 0) {
				if (t1[0][1] == '+')
					bomb++;
				if (t1[1][0] == '+')
					bomb++;
				if (t1[1][1] == '+')
					bomb++;
			}
			else if (i == 0 && j == 7) {
				if (t1[0][6] == '+')
					bomb++;
				if (t1[1][6] == '+')
					bomb++;
				if (t1[1][7] == '+')
					bomb++;
			}
			else if (i == 7 && j == 0) {
				if (t1[7][1] == '+')
					bomb++;
				if (t1[6][1] == '+')
					bomb++;
				if (t1[6][0] == '+')
					bomb++;
			}
			else if (i == 7 && j == 7) {
				if (t1[6][6] == '+')
					bomb++;
				if (t1[7][6] == '+')
					bomb++;
				if (t1[6][7] == '+')
					bomb++;
			}
			else if (i == 0) {
				if (t1[0][j + 1] == '+')
					bomb++;
				if (t1[0][j - 1] == '+')
					bomb++;
				if (t1[1][j] == '+')
					bomb++;
				if (t1[1][j + 1] == '+')
					bomb++;
				if (t1[1][j - 1] == '+')
					bomb++;
			}
			else if (i == 7) {
				if (t1[7][j + 1] == '+')
					bomb++;
				if (t1[7][j - 1] == '+')
					bomb++;
				if (t1[6][j] == '+')
					bomb++;
				if (t1[6][j - 1] == '+')
					bomb++;
				if (t1[6][j + 1] == '+')
					bomb++;
			}
			else if (j == 0) {
				if (t1[i][1] == '+')
					bomb++;
				if (t1[i - 1][0] == '+')
					bomb++;
				if (t1[i - 1][1] == '+')
					bomb++;
				if (t1[i + 1][1] == '+')
					bomb++;
				if (t1[i + 1][0] == '+')
					bomb++;
			}
			else if (j == 7) {
				if (t1[i + 1][7] == '+')
					bomb++;
				if (t1[i - 1][7] == '+')
					bomb++;
				if (t1[i][6] == '+')
					bomb++;
				if (t1[i + 1][6] == '+')
					bomb++;
				if (t1[i - 1][6] == '+')
					bomb++;
			}
			else {
				if (t1[i + 1][j - 1] == '+')
					bomb++;
				if (t1[i + 1][j] == '+')
					bomb++;
				if (t1[i + 1][j + 1] == '+')
					bomb++;
				if (t1[i][j - 1] == '+')
					bomb++;
				if (t1[i][j + 1] == '+')
					bomb++;
				if (t1[i - 1][j - 1] == '+')
					bomb++;
				if (t1[i - 1][j] == '+')
					bomb++;
				if (t1[i - 1][j + 1] == '+')
					bomb++;
			}
			bomb += '0';
			t1[i][j] = (char)bomb;
			c++;
		}
	}
}
void lclick1(int i, int j) {
	if (t1[i][j] == '+')
		end = 'l';
	else if (t1[i][j] == '0') {
		if (board1[i][j] != '0') {
			open1_1(i, j);
			open1_2(i, j);
			open1_3(i, j);
			open1_4(i, j);
		}
	}
	else
		board1[i][j] = t1[i][j];
}
void rclick1(int i, int j) {
	if (board1[i][j] == 'P') {
		board1[i][j] = beforeP1[i][j];
		parcham_karbar1++;
	}
	else if (board1[i][j] == '*' || board1[i][j] == '-') {
		if (parcham_karbar1 <= 0) {
			wprintf(L"\a");
		}
		else {
			beforeP1[i][j] = board1[i][j];
			board1[i][j] = 'P';
			parcham_karbar1--;
			if (t1[i][j] == '+')
				parcham1--;
		}
	}
}
void printboard1() {
	wprintf(L"\033[1;90m");
	wprintf(L"\n\n");
	for (int i = 0; i < 8; i++) {
		wprintf(L"\t\t\t\t     ");
		for (int j = 0; j < 8; j++) {
			if (board1[i][j] == '-')
				wprintf(L"\u25A0 ");
			else if (board1[i][j] == '*')
				wprintf(L"\033[1;34m\u25A0 \033[1;90m");
			else if (board1[i][j] == '+')
				wprintf(L"\033[1;31m\u01A0 \033[1;90m");
			else if (board1[i][j] == '0')
				wprintf(L"\033[1;90m0 \033[1;90m");
			else if (board1[i][j] == 'P')
				wprintf(L"\033[1;35m\u2660 \033[1;90m");
			else if (board1[i][j] == '1')
				wprintf(L"\033[1;94m1 \033[1;90m");
			else if (board1[i][j] == '2')
				wprintf(L"\033[1;32m2 \033[1;90m");
			else if (board1[i][j] == '3')
				wprintf(L"\033[1;33m3 \033[1;90m");
			else if (board1[i][j] == '4')
				wprintf(L"\033[1;31m4 \033[1;90m");
			else if (board1[i][j] == '5')
				wprintf(L"\033[1;34m5 \033[1;90m");
			else if (board1[i][j] == '6')
				wprintf(L"\033[1;34m6 \033[1;90m");
			else if (board1[i][j] == '7')
				wprintf(L"\033[1;34m7 \033[1;90m");
			else if (board1[i][j] == '8')
				wprintf(L"\033[1;34m8 \033[1;90m");
		}
		wprintf(L"\n");
	}
	wprintf(L"\n\n");
	wprintf(L"\033[1;0m");
}
void playermove1() {
	static int i = 0, j = 0;
	int n;
	if (board1[i][j] == '-') {
		board1[i][j] = '*';
		printboard1();
		board1[i][j] = '-';
	}
	else
		printboard1();

	n = getch();
	if (n == 13)
		lclick1(i, j);
	else if (n == 32)
		rclick1(i, j);
	else if (n == 'z' || n == 'Z')
		end = 'z';
	else {
		switch (n) {
		case 'd':
		case 'D':
			if (j != 7)
				j++;
			break;
		case 'A':
		case 'a':
			if (j != 0)
				j--;
			break;
		case 's':
		case 'S':
			if (i != 7)
				i++;
			break;
		case 'w':
		case 'W':
			if (i != 0)
				i--;
			break;
		}
	}
}
//---------------------------------------------
// 16 x 16 Functions
//---------------------------------------------
void open2_1(int i, int j) {
	if (i < 0 || i>15 || j < 0 || j>15)
		return;
	if (t2[i][j] == '+')
		return;
	board2[i][j] = t2[i][j];
	if (board2[i][j + 1] != '-' && board2[i][j + 1] != '0')
		return;
	open2_1(i, j + 1);
}
void open2_2(int i, int j) {
	if (i < 0 || i>15 || j < 0 || j>15)
		return;
	if (t2[i][j] == '+')
		return;
	board2[i][j] = t2[i][j];
	if (board2[i + 1][j] != '-' && board2[i + 1][j] != '0')
		return;
	open2_2(i + 1, j);
}
void open2_3(int i, int j) {
	if (i < 0 || i>15 || j < 0 || j>15)
		return;
	if (t2[i][j] == '+')
		return;
	board2[i][j] = t2[i][j];
	if (board2[i][j - 1] != '-' && board2[i][j - 1] != '0')
		return;
	open2_3(i, j - 1);
}
void open2_4(int i, int j) {
	if (i < 0 || i>15 || j < 0 || j>15)
		return;
	if (t2[i][j] == '+')
		return;
	board2[i][j] = t2[i][j];
	if (board2[i - 1][j] != '-' && board2[i - 1][j] != '0')
		return;
	open2_4(i - 1, j);
}
int checkfreespace2() {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			if (board2[i][j] == '-')
				return 1;
		}
	}
	return 0;
}
void checkwin2() {
	if (parcham2 == 0 && checkfreespace1() == 0)
		end = 'w';
}
void reset2() {
	for (int j = 0; j < 16; j++) {
		check3_2[j] = 0;
	}
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			board2[i][j] = '-';
			t2[i][j] = '-';
		}
	}
	int c = 0;
	while (c < 40) {
		int i = rand() % 16;
		int j = rand() % 16;
		if (t2[i][j] == '-' && check3_2[j] < 3) {
			t2[i][j] = '+';
			check3_2[j]++;
			c++;
		}
	}
	c = 0;
	while (c < 120) {
		int i = rand() % 16;
		int j = rand() % 16;
		if (t2[i][j] == '-') {
			t2[i][j] = '0';
			c++;
		}
	}
	c = 0;
	while (c < 96) {
		int bomb = 0;
		int i = rand() % 16;
		int j = rand() % 16;
		if (t2[i][j] == '-') {
			if (i == 0 && j == 0) {
				if (t2[0][1] == '+')
					bomb++;
				if (t2[1][0] == '+')
					bomb++;
				if (t2[1][1] == '+')
					bomb++;
			}
			else if (i == 0 && j == 15) {
				if (t2[0][14] == '+')
					bomb++;
				if (t2[1][14] == '+')
					bomb++;
				if (t2[1][15] == '+')
					bomb++;
			}
			else if (i == 15 && j == 0) {
				if (t2[15][1] == '+')
					bomb++;
				if (t2[14][1] == '+')
					bomb++;
				if (t2[14][0] == '+')
					bomb++;
			}
			else if (i == 15 && j == 15) {
				if (t2[14][14] == '+')
					bomb++;
				if (t2[15][14] == '+')
					bomb++;
				if (t2[14][15] == '+')
					bomb++;
			}
			else if (i == 0) {
				if (t2[0][j + 1] == '+')
					bomb++;
				if (t2[0][j - 1] == '+')
					bomb++;
				if (t2[1][j] == '+')
					bomb++;
				if (t2[1][j + 1] == '+')
					bomb++;
				if (t2[1][j - 1] == '+')
					bomb++;
			}
			else if (i == 15) {
				if (t2[15][j + 1] == '+')
					bomb++;
				if (t2[15][j - 1] == '+')
					bomb++;
				if (t2[14][j] == '+')
					bomb++;
				if (t2[14][j - 1] == '+')
					bomb++;
				if (t2[14][j + 1] == '+')
					bomb++;
			}
			else if (j == 0) {
				if (t2[i][1] == '+')
					bomb++;
				if (t2[i - 1][0] == '+')
					bomb++;
				if (t2[i - 1][1] == '+')
					bomb++;
				if (t2[i + 1][1] == '+')
					bomb++;
				if (t2[i + 1][0] == '+')
					bomb++;
			}
			else if (j == 15) {
				if (t2[i + 1][15] == '+')
					bomb++;
				if (t2[i - 1][15] == '+')
					bomb++;
				if (t2[i][14] == '+')
					bomb++;
				if (t2[i + 1][14] == '+')
					bomb++;
				if (t2[i - 1][14] == '+')
					bomb++;
			}
			else {
				if (t2[i + 1][j - 1] == '+')
					bomb++;
				if (t2[i + 1][j] == '+')
					bomb++;
				if (t2[i + 1][j + 1] == '+')
					bomb++;
				if (t2[i][j - 1] == '+')
					bomb++;
				if (t2[i][j + 1] == '+')
					bomb++;
				if (t2[i - 1][j - 1] == '+')
					bomb++;
				if (t2[i - 1][j] == '+')
					bomb++;
				if (t2[i - 1][j + 1] == '+')
					bomb++;
			}
			bomb += '0';
			t2[i][j] = (char)bomb;
			c++;
		}
	}
}
void lclick2(int i, int j) {
	if (t2[i][j] == '+')
		end = 'l';
	else if (t2[i][j] == '0') {
		if (board2[i][j] != '0') {
			open2_1(i, j);
			open2_2(i, j);
			open2_3(i, j);
			open2_4(i, j);
		}
	}
	else
		board2[i][j] = t2[i][j];
}
void rclick2(int i, int j) {
	if (board2[i][j] == 'P') {
		board2[i][j] = beforeP2[i][j];
		parcham_karbar2++;
	}
	else if (board2[i][j] == '*' || board2[i][j] == '-') {
		if (parcham_karbar2 <= 0) {
			wprintf(L"\a");
		}
		else {
			beforeP2[i][j] = board2[i][j];
			board2[i][j] = 'P';
			parcham_karbar2--;
			if (t2[i][j] == '+')
				parcham2--;
		}
	}
}
void printboard2() {
	wprintf(L"\033[1;90m");
	wprintf(L"\n\n");
	for (int i = 0; i < 16; i++) {
		wprintf(L"\t\t\t     ");
		for (int j = 0; j < 16; j++) {
			if (board2[i][j] == '-')
				wprintf(L"\u25A0 ");
			else if (board2[i][j] == '*')
				wprintf(L"\033[1;34m\u25A0 \033[1;90m");
			else if (board2[i][j] == '+')
				wprintf(L"\033[1;31m\u01A0 \033[1;90m");
			else if (board2[i][j] == '0')
				wprintf(L"\033[1;90m0 \033[1;90m");
			else if (board2[i][j] == 'P')
				wprintf(L"\033[1;35m\u2660 \033[1;90m");
			else if (board2[i][j] == '1')
				wprintf(L"\033[1;94m1 \033[1;90m");
			else if (board2[i][j] == '2')
				wprintf(L"\033[1;32m2 \033[1;90m");
			else if (board2[i][j] == '3')
				wprintf(L"\033[1;33m3 \033[1;90m");
			else if (board2[i][j] == '4')
				wprintf(L"\033[1;31m4 \033[1;90m");
			else if (board2[i][j] == '5')
				wprintf(L"\033[1;34m5 \033[1;90m");
			else if (board2[i][j] == '6')
				wprintf(L"\033[1;34m6 \033[1;90m");
			else if (board2[i][j] == '7')
				wprintf(L"\033[1;34m7 \033[1;90m");
			else if (board2[i][j] == '8')
				wprintf(L"\033[1;34m8 \033[1;90m");
		}
		wprintf(L"\n");
	}
	wprintf(L"\n\n");
	wprintf(L"\033[1;0m");
}
void playermove2() {
	static int i = 0, j = 0;
	int n;
	if (board2[i][j] == '-') {
		board2[i][j] = '*';
		printboard2();
		board2[i][j] = '-';
	}
	else
		printboard2();
	n = getch();
	if (n == 13)
		lclick2(i, j);
	else if (n == 32)
		rclick2(i, j);
	else if (n == 'z' || n == 'Z')
		end = 'z';
	else {
		switch (n) {
		case 'd':
		case 'D':
			if (j != 15)
				j++;
			break;
		case 'A':
		case 'a':
			if (j != 0)
				j--;
			break;
		case 's':
		case 'S':
			if (i != 15)
				i++;
			break;
		case 'w':
		case 'W':
			if (i != 0)
				i--;
			break;
		}
	}
}