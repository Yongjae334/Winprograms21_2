#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define WIDTH 25

// 메뉴 출력
void showMenu() {
    puts("--------------------------");
    puts("-   돌맹이 옮기기 게임   -");
    puts("--------------------------");
    puts("1. 게임 시작");
    puts("2. 종료");
}

// 돌맹이 줄 출력 (한 줄씩 문자로 출력)
void printLine(int position) {
    char line[WIDTH + 1];

    for (int i = 0; i < WIDTH; i++) {
        if (i == position)
            line[i] = '0';
        else
            line[i] = '_';
    }
    line[WIDTH] = '\0';  // 문자열 종료

    puts(line);  // 한 줄 출력
}

// 게임 실행
void playGame() {
    int position = WIDTH / 2;
    char key;

    while (1) {
        system("cls");
        printLine(position);
        puts("");
        puts("←[A]   →[D]   종료[Q]");

        key = _getch();

        if (key == 'a' || key == 'A') {
            if (position > 0)
                position--;
        }
        else if (key == 'd' || key == 'D') {
            if (position < WIDTH - 1)
                position++;
        }
        else if (key == 'q' || key == 'Q') {
            break;
        }
    }

    puts("");
    puts("게임 종료! 아무 키나 누르면 메뉴로 돌아갑니다.");
    _getch();
}

// 메인
int main() {
    char menuInput;

    while (1) {
        system("cls");
        showMenu();
        menuInput = _getch();

        if (menuInput == '1') {
            playGame();
        }
        else if (menuInput == '2') {
            puts("");
            puts("게임을 종료합니다.");
            break;
        }
        else {
            puts("");
            puts("잘못된 입력입니다. 아무 키나 누르세요.");
            _getch();
        }
    }

    return 0;
}