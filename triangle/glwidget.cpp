#include "glwidget.h"
#include <QDebug>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
}

GLWidget::~GLWidget()
{
    glDisableVertexAttribArray(0);
}

void GLWidget::initializeGL()
{
    static const GLfloat vertices[3][3] = {
        {0.866f, -0.5f, 0.0f}, {-0.866f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}};
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
