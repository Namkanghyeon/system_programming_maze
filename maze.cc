#include "maze.h"
#include <process.h>

void TextColorChange(int);
void GotoXY(int, int);
void DrawMap(int, int);
void RunGame(int, int);
int Checker(int, int);

int endFlag; // �ⱸ�� �����ߴ��� üũ
int time = 10; // �ð� ����

DWORD WINAPI ThreadTimer(void* data) {

	while (time >= 0) {
		GotoXY(0, 21);
		printf("Time: %d    ", time--);
		Sleep(1000);
	}
	GotoXY(0, 21);
	printf("TIME OUT    ");
	exit(0);

	return 0;
}

int main(int argc, char* argv[]) {

	HANDLE timer = CreateThread(NULL, 0, ThreadTimer, NULL, 0, NULL); // Ÿ�̸� thread ����

	endFlag = 0;

	system("mode con cols=37 lines=30");

	int circlePosX = 4, circlePosY = 3;

	DrawMap(circlePosX, circlePosY);

	RunGame(circlePosX, circlePosY);

	return 0;
}

void TextColorChange(int colorNumber) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNumber);
}

void GotoXY(int x, int y) {

	COORD pos = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void DrawMap(int circlePosX, int circlePosY) {
	int idx = 0, idy = 0;

	GotoXY(0, 2);

	for (idx = 0; idx < HEIGHT; idx++) {
		for (idy = 0; idy < WIDTH; idy++) {

			switch (map[idx][idy]) {
			case 0:
				printf("  ");
				break;
			case 1:
				TextColorChange(8);
				printf("��");
				break;
			case 2:
				TextColorChange(11);
				printf("��");
				break;
			case 3:
				TextColorChange(12);
				printf("��");
				break;
			}

		}
		printf("\n");
	}
	GotoXY(circlePosX, circlePosY + 2);
	TextColorChange(14);
	printf("��");
}

void RunGame(int circlePosX, int circlePosY) {

	int cmd = 0;

	while (1) {
		TextColorChange(14);

		cmd = _getch(); // get character, ���� �����ϸ� stdin

		switch (cmd) {
		case UP:
			GotoXY(circlePosX, circlePosY + 2); // Y+2�� �迭�� cmdâ�� ���� ����
			printf("  ");

			circlePosY -= 1; // �ϴ� ������

			if (!Checker(circlePosX, circlePosY)) { // üĿ�� �̵��������� üũ
				circlePosY += 1; // �ȵǸ� �ٽ� ���ƿ�
			}
			break;
		case DOWN:
			GotoXY(circlePosX, circlePosY + 2);
			printf("  ");
			circlePosY += 1;

			if (!Checker(circlePosX, circlePosY)) {
				circlePosY -= 1;
			}
			break;
		case LEFT:
			GotoXY(circlePosX, circlePosY + 2);
			printf("  ");
			circlePosX -= 2;

			if (!Checker(circlePosX, circlePosY)) {
				circlePosX += 2;
			}
			break;
		case RIGHT:
			GotoXY(circlePosX, circlePosY + 2);
			printf("  ");
			circlePosX += 2;

			if (!Checker(circlePosX, circlePosY)) {
				circlePosX -= 2;
			}
			break;
		case EXIT:
			endFlag = 1;
		}
		GotoXY(circlePosX, circlePosY + 2);
		printf("��");
		if (endFlag)
			break;
	}
}

int Checker(int x, int y) { // üĿ�� 0�� �����ϸ� �� �����̰� 1�� �����ϸ� ������ �� ����

	switch (map[y][x]) {
	case 0:
		return 1;
		break;
	case 2:
		endFlag = 1;
		return 1;
		break;
	case 3:
		map[y][x] = 0;
		time += PLUS_TIME;
		return 1;
		break;
	default:
		return 0;
		break;
	}
}