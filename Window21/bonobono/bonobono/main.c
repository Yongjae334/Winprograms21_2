#include <GLFW/glfw3.h>
#include <math.h>
#define PI 3.14159265358979323846f

// ���� �׸��� �Լ�
void drawCircle(float cx, float cy, float r, int segments, float rCol, float gCol, float bCol, float aspect) {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(rCol, gCol, bCol);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float x = cosf(angle);
        float y = sinf(angle);
        glVertex2f(cx + r * x / aspect, cy + r * y);
    }
    glEnd();
}

// �׵θ� �׸��� �Լ�
void drawCircleOutline(float cx, float cy, float r, int segments, float aspect, float lineWidth) {
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float x = cosf(angle);
        float y = sinf(angle);
        glVertex2f(cx + r * x / aspect, cy + r * y);
    }
    glEnd();
}

// ���� �׸��� �Լ�
void drawWhiskers() {
    glColor3f(0, 0, 0);
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // ���� (ª�� ����)
    glVertex2f(-0.15f, -0.1f); glVertex2f(-0.30f, 0.0f);
    glVertex2f(-0.15f, -0.15f); glVertex2f(-0.30f, -0.15f);
    glVertex2f(-0.15f, -0.2f); glVertex2f(-0.30f, -0.3f);

    // ������ (ª�� ����)
    glVertex2f(0.15f, -0.1f); glVertex2f(0.30f, 0.0f);
    glVertex2f(0.15f, -0.15f); glVertex2f(0.30f, -0.15f);
    glVertex2f(0.15f, -0.2f); glVertex2f(0.30f, -0.3f);




    glEnd();
}

int main() {
    int width = 800, height = 600;
    float aspect = (float)width / height;

    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(width, height, "Seal Face", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }

    glfwMakeContextCurrent(window);

    // ��� ���
    glClearColor(1, 1, 1, 1);

    // ��ǥ�� ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        // �� (�Ķ� ��)
        drawCircle(0.0f, 0.0f, 0.8f, 100, 0.0f, 0.45f, 0.87f, aspect);
        drawCircleOutline(0.0f, 0.0f, 0.8f, 100, aspect, 2.0f);

        // ���� �� (�� �ٱ�����)
        drawCircle(-0.45f, 0.3f, 0.07f, 50, 0, 0, 0, aspect);

        // ������ �� (�� �ٱ�����)
        drawCircle(0.45f, 0.3f, 0.07f, 50, 0, 0, 0, aspect);


        // �� (���)
        drawCircle(-0.08f, -0.15f, 0.15f, 50, 1, 1, 1, aspect);
        drawCircle(0.08f, -0.15f, 0.15f, 50, 1, 1, 1, aspect);

        // ��
        drawCircle(0.0f, -0.02f, 0.12f, 50, 0, 0, 0, aspect);




        // ����
        drawWhiskers();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
    