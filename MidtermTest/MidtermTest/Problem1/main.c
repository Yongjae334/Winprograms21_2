#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// PassOrFail �Լ�: ������ 50�� �̻��̸� 1, �ƴϸ� 0 ��ȯ
int PassOrFail(int score) {
    return (score >= 50) ? 1 : 0;
}

int main(void) {
    int myScore;
    // ���� ���� �Է� �ޱ�
    printf("������ ���� ������ �Է��ϼ���: ");
    if (scanf_s("%d", &myScore) != 1) {
        printf("�Է� �����Դϴ�.\n");
        return 1;
    }

    if (PassOrFail(myScore))
        printf("����� �����ϴ�!\n");
    else
        printf("�츮�� ���ߴ١� ������̴١�\n");

    return 0;
}
