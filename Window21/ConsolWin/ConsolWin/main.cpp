#include <stdio.h>
#include <Windows.h>

void gotoxy(int x, int y)
{
	COORD cur;
	cur.X = x;
	cur.Y = y;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, cur); 
}

int main()
{

	puts("\n\n\n\n");
	puts("---------------------------------------------------------------------------------- \n");
	puts("|                                                                                | \n");
	puts("---------------------------------------------------------------------------------- \n");
	puts("|                                                                                | \n");
	puts("|                                                                                | \n");
	puts("|                                                                                | \n");
	puts("|                                                                                | \n");
	puts("---------------------------------------------------------------------------------- \n");

	return 0;
}

int show() {
	int width, height;

	while (1) {
		puts("  가로 사이즈를 입력하시오.");
		scanf_s("%d, &width");
		printf(" 세로 사이즈를 입력하시오.");
		scanf_s("%d", &height);

		system("cls");

		if (width >= 2 && height >= 2) break;
		printf("가로와 세로는 최소 2 이상이어야 합니다. 다시 입력하세요.\n\n"); //2 미만으로 나올 경우 생성이 불가능하니까 이렇게 출력함
	}

	int middle = 2; // 두 번째 줄에서는 무조건 *이 나오게 하기 위해 입력 됨

	// 상단 테두리 출력
	gotoxy(0, 0); // 맨 위에 부터 출력이 되어야 합니다.
	for (int i = 0; i < width; i++) printf("*"); //첫 줄 테두리 입력

	// 중간 줄 출력
	for (int i = 1; i < height - 1; i++) {
		gotoxy(0, i); //중간부터니까 0, i임

		// 중간 위치에 '*' 테두리 출력
		if (i == middle) {
			for (int j = 0; j < width; j++) printf("*");
		}
		else {
			printf("[");
			for (int j = 1; j < width - 1; j++) printf(" ");
			printf("]");
		}
	}

	// 하단 테두리 출력
	gotoxy(0, height - 1); // 마지막 줄에서 * 출력함
	for (int i = 0; i < width; i++) printf("*");

	gotoxy(0, height + 1); // 커서 박스를 아래로 내리기
	return 0;
}
