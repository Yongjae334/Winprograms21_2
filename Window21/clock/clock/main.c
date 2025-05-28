#include <GLFW/glfw3.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#ifdef _WIN32
#include <stdlib.h>
#else
#include <unistd.h>
#endif

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static float deg2rad(float deg) {
    return deg * (M_PI / 180.0f);
}

static void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

static void drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * M_PI * i / segments;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

static void drawCircleOutline(float radius, int segments) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = deg2rad(360.0f * i / segments);
        glVertex2f(cosf(theta) * radius, sinf(theta) * radius);
    }
    glEnd();
}

static void drawTicks() {
    float radius = 0.9f;
    for (int i = 0; i < 60; i++) {
        float angle = deg2rad(i * 6.0f);
        float c = cosf(angle), s = sinf(angle);
        float inner = (i % 5 == 0) ? radius - 0.1f : radius - 0.05f;
        drawLine(c * inner, s * inner, c * radius, s * radius);
    }
}

static const bool segMap[10][7] = {
    {1,1,1,1,1,1,0},
    {0,1,1,0,0,0,0},
    {1,1,0,1,1,0,1},
    {1,1,1,1,0,0,1},
    {0,1,1,0,0,1,1},
    {1,0,1,1,0,1,1},
    {1,0,1,1,1,1,1},
    {1,1,1,0,0,0,0},
    {1,1,1,1,1,1,1},
    {1,1,1,1,0,1,1}
};

static void drawDigit(int d, float x, float y, float scale) {
    float w = 0.10f * scale, h = 0.15f * scale;
    glLineWidth(4.0f);
    if (segMap[d][0]) drawLine(x - w, y + h, x + w, y + h);
    if (segMap[d][1]) drawLine(x + w, y + h, x + w, y);
    if (segMap[d][2]) drawLine(x + w, y, x + w, y - h);
    if (segMap[d][3]) drawLine(x - w, y - h, x + w, y - h);
    if (segMap[d][4]) drawLine(x - w, y, x - w, y - h);
    if (segMap[d][5]) drawLine(x - w, y + h, x - w, y);
    if (segMap[d][6]) drawLine(x - w, y, x + w, y);
    glLineWidth(1.0f);
}

static void drawColon(float x, float y, float scale, bool visible) {
    if (!visible) return;
    float r = 0.015f * scale;
    glColor3f(0.2f, 1.0f, 0.2f);
    drawCircle(x, y + 0.05f * scale, r, 20);
    drawCircle(x, y - 0.05f * scale, r, 20);
}

static void drawTextAMPM(bool isPM, float x, float y, float scale) {
    glLineWidth(2.0f);
    // p
    drawLine(x, y, x, y - scale * 0.1f);
    drawLine(x, y, x + scale * 0.05f, y);
    drawLine(x + scale * 0.05f, y, x + scale * 0.05f, y - scale * 0.05f);
    drawLine(x + scale * 0.05f, y - scale * 0.05f, x, y - scale * 0.05f);
    // m
    drawLine(x + scale * 0.1f, y - scale * 0.05f, x + scale * 0.1f, y - scale * 0.1f);
    drawLine(x + scale * 0.1f, y - scale * 0.05f, x + scale * 0.125f, y - scale * 0.075f);
    drawLine(x + scale * 0.125f, y - scale * 0.075f, x + scale * 0.15f, y - scale * 0.05f);
    drawLine(x + scale * 0.15f, y - scale * 0.05f, x + scale * 0.15f, y - scale * 0.1f);
    glLineWidth(1.0f);
}

static void drawDigitalSub(int hour, int minute, int second, bool colonVisible, bool isPM) {
    float scale = 1.0f;
    float yPos = 0.0f;
    float startX = -0.60f;

    glColor3f(0.2f, 1.0f, 0.2f);
    drawDigit(hour / 10, startX, yPos, scale);
    drawDigit(hour % 10, startX + 0.24f, yPos, scale);
    drawColon(startX + 0.42f, yPos, scale, colonVisible);
    drawDigit(minute / 10, startX + 0.60f, yPos, scale);
    drawDigit(minute % 10, startX + 0.84f, yPos, scale);
    drawColon(startX + 1.02f, yPos, scale, colonVisible);
    drawDigit(second / 10, startX + 1.20f, yPos, scale);
    drawDigit(second % 10, startX + 1.44f, yPos, scale);

    drawTextAMPM(isPM, startX + 1.65f, yPos + 0.05f, scale);
}

static void drawHourHand(int hour, int minute) {
    float deg = (hour % 12 + minute / 60.0f) * 30.0f;
    float ang = deg2rad(90.0f - deg), len = 0.5f;
    glLineWidth(6.0f);
    drawLine(0, 0, cosf(ang) * len, sinf(ang) * len);
    glLineWidth(1.0f);
}

static void drawMinuteHand(int minute, int second) {
    float deg = (minute + second / 60.0f) * 6.0f;
    float ang = deg2rad(90.0f - deg), len = 0.7f;
    glLineWidth(4.0f);
    drawLine(0, 0, cosf(ang) * len, sinf(ang) * len);
    glLineWidth(1.0f);
}

static void drawSecondHand(int second) {
    float deg = second * 6.0f;
    float ang = deg2rad(90.0f - deg), len = 0.7f;
    glLineWidth(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawLine(0, 0, cosf(ang) * len, sinf(ang) * len);
    glLineWidth(1.0f);
    glColor3f(0.2f, 1.0f, 0.2f);
}

int main(void) {
#ifdef _WIN32
    _putenv_s("TZ", "KST-9");
    _tzset();
#else
    setenv("TZ", "Asia/Seoul", 1);
    tzset();
#endif

    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dark Digital + Analog Clock", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // 다크모드
        glClear(GL_COLOR_BUFFER_BIT);

        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        int hour = t->tm_hour;
        int minute = t->tm_min;
        int second = t->tm_sec;
        bool colonVisible = (second % 2 == 0);
        bool isPM = (hour >= 12);

        glColor3f(0.2f, 1.0f, 0.2f);
        drawCircleOutline(0.92f, 100);
        drawTicks();
        drawHourHand(hour, minute);
        drawMinuteHand(minute, second);

        glPushMatrix();
        glTranslatef(-0.5f, 0.0f, 0.0f);
        glScalef(0.3f, 0.3f, 1.0f);
        drawCircleOutline(0.92f, 100);
        drawTicks();
        drawSecondHand(second);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.5f, 0.0f, 0.0f);
        glScalef(0.3f, 0.3f, 1.0f);
        drawDigitalSub(hour % 12 == 0 ? 12 : hour % 12, minute, second, colonVisible, isPM);
        glPopMatrix();

        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwWaitEventsTimeout(0.01);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
