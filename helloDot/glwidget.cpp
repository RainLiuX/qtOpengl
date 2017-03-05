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
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    static const GLfloat vertices[1][3] = {{0.0f, 0.0f, 0.0f}};
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    qDebug()<<"glwidget initialized";
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0,0,width,height);
    qDebug()<<"glwidget resized";
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDrawArrays(GL_POINTS, 0, 1);
    qDebug()<<"glwidget repainted";
}
