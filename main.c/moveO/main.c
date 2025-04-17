#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define WIDTH 25

// �޴� ���
void showMenu() {
    puts("--------------------------");
    puts("-   ������ �ű�� ����   -");
    puts("--------------------------");
    puts("1. ���� ����");
    puts("2. ����");
}

// ������ �� ��� (�� �پ� ���ڷ� ���)
void printLine(int position) {
    char line[WIDTH + 1];

    for (int i = 0; i < WIDTH; i++) {
        if (i == position)
            line[i] = '0';
        else
            line[i] = '_';
    }
    line[WIDTH] = '\0';  // ���ڿ� ����

    puts(line);  // �� �� ���
}

// ���� ����
void playGame() {
    int position = WIDTH / 2;
    char key;

    while (1) {
        system("cls");
        printLine(position);
        puts("");
        puts("��[A]   ��[D]   ����[Q]");

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
    puts("���� ����! �ƹ� Ű�� ������ �޴��� ���ư��ϴ�.");
    _getch();
}

// ����
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
            puts("������ �����մϴ�.");
            break;
        }
        else {
            puts("");
            puts("�߸��� �Է��Դϴ�. �ƹ� Ű�� ��������.");
            _getch();
        }
    }

    return 0;
}