#include <GLFW/glfw3.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define PI 3.14159265358979323846f

void drawRainbowCircle(float centerX, float centerY, float radius, int segments, float aspect) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f); // �߽� ���
    glVertex2f(centerX, centerY);

    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * PI * i / segments;
        float x = cosf(angle);
        float y = sinf(angle);

        // HSV �� RGB ������ ������ ���� ��ȭ (������)
        float t = (float)i / segments;
        float r = fabsf(sinf(t * PI));
        float g = fabsf(sinf(t * PI + 2.0f));
        float b = fabsf(sinf(t * PI + 4.0f));

        glColor3f(r, g, b);
        glVertex2f(centerX + radius * x / aspect, centerY + radius * y);
    }

    glEnd();
}

int main(void) {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rainbow Circle", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    float aspect = (float)WINDOW_WIDTH / WINDOW_HEIGHT;

    // ��ǥ�� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        drawRainbowCircle(0.0f, 0.0f, 0.8f, 100, aspect);  // �߽ɿ� ������ 0.8¥�� ������ ��

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
