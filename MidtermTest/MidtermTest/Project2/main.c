// main.c
#include <stdio.h>

int main(void) {
    const int WIDTH = 80;
    const int HEIGHT = 25;
    const int TOP_MARGIN = 1;
    const int BOTTOM_MARGIN = 1;
    const int LEFT_MARGIN = 2;
    const int RIGHT_MARGIN = 2;

    // 1) ��ü ȭ�� �����
    printf("\x1b[2J");

    // 2) �Ķ� ������� ä���
    //    ��: TOP_MARGIN+1 ���� HEIGHT-BOTTOM_MARGIN
    //    �� ����: LEFT_MARGIN+1
    //    �ʺ�   : WIDTH - LEFT_MARGIN - RIGHT_MARGIN
    for (int row = TOP_MARGIN + 1; row <= HEIGHT - BOTTOM_MARGIN; ++row) {
        // Ŀ�� �̵�
        printf("\x1b[%d;%dH", row, LEFT_MARGIN + 1);
        // �Ķ� ��� ���� (44m), ���� ���, ���� ���� (0m)
        printf("\x1b[44m");
        for (int col = 0; col < WIDTH - LEFT_MARGIN - RIGHT_MARGIN; ++col) {
            putchar(' ');
        }
        printf("\x1b[0m");
    }

    // 3) Ŀ���� �� �Ʒ� �������� �Ű� ����
    printf("\x1b[%d;1H", HEIGHT + 1);

    return 0;
}
