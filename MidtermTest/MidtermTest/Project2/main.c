// main.c
#include <stdio.h>

int main(void) {
    const int WIDTH = 80;
    const int HEIGHT = 25;
    const int TOP_MARGIN = 1;
    const int BOTTOM_MARGIN = 1;
    const int LEFT_MARGIN = 2;
    const int RIGHT_MARGIN = 2;

    // 1) 전체 화면 지우기
    printf("\x1b[2J");

    // 2) 파란 배경으로 채우기
    //    행: TOP_MARGIN+1 부터 HEIGHT-BOTTOM_MARGIN
    //    열 시작: LEFT_MARGIN+1
    //    너비   : WIDTH - LEFT_MARGIN - RIGHT_MARGIN
    for (int row = TOP_MARGIN + 1; row <= HEIGHT - BOTTOM_MARGIN; ++row) {
        // 커서 이동
        printf("\x1b[%d;%dH", row, LEFT_MARGIN + 1);
        // 파란 배경 설정 (44m), 공백 출력, 색상 리셋 (0m)
        printf("\x1b[44m");
        for (int col = 0; col < WIDTH - LEFT_MARGIN - RIGHT_MARGIN; ++col) {
            putchar(' ');
        }
        printf("\x1b[0m");
    }

    // 3) 커서를 맨 아래 왼쪽으로 옮겨 놓기
    printf("\x1b[%d;1H", HEIGHT + 1);

    return 0;
}
