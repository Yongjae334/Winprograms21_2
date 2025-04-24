#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// PassOrFail 함수: 점수가 50점 이상이면 1, 아니면 0 반환
int PassOrFail(int score) {
    return (score >= 50) ? 1 : 0;
}

int main(void) {
    int myScore;
    // 예상 점수 입력 받기
    printf("본인의 예상 점수를 입력하세요: ");
    if (scanf_s("%d", &myScore) != 1) {
        printf("입력 오류입니다.\n");
        return 1;
    }

    if (PassOrFail(myScore))
        printf("재시험 없습니다!\n");
    else
        printf("우리는 망했다… 재시험이다…\n");

    return 0;
}
