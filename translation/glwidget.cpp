#include "glwidget.h"
#include <QDebug>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    timer = new QTimer;
    timer->start(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    scale = 0.0f;
    world = QMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
                       0.0f, 1.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
}

GLWidget::~GLWidget()
{
    glDisableVertexAttribArray(0);
}

void GLWidget::initializeGL()
{
    //set vertexes & read glsl
    static const GLfloat vertices[3][3] = {
        {0.866f, -0.5f, 0.0f}, {-0.866f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}};
    std::string vertexshader;
    std::string fragshader;
    std::ifstream file1("../translation/vertexshader.vsh");
    std::string temp;
    while(std::getline(file1, temp))
    {
        vertexshader += temp + "\n";
    }
    file1.close();
    std::ifstream file2("../translation/fragshader.frag");
    while(std::getline(file2,temp))
    {
        fragshader += temp + "\n";
    }
    file2.close();

    //initialize & set flags
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    //create vertex buffer(really confusing)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //enable attribute array
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //add shaders
    GLuint shaderProgram = glCreateProgram();
    addShader(shaderProgram, vertexshader.c_str(), vertexshader.size(), GL_VERTEX_SHADER);
    addShader(shaderProgram, fragshader.c_str(), fragshader.size(), GL_FRAGMENT_SHADER);

    //get location
    //gScaleLocation = glGetUniformLocation(shaderProgram, "gScale");
    gWorldLocation = glGetUniformLocation(shaderProgram, "gWorld");

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

void GLWidget::addShader(GLuint shaderProgram, const char* shaderText, const int length, GLenum shaderType)
{
    GLuint shaderObj = glCreateShader(shaderType);
    glShaderSource(shaderObj, 1, &shaderText, &length);
    glCompileShader(shaderObj);
    int success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        /*char log[1024];
        glGetShaderInfoLog(shaderObj, sizeof(log), NULL, log);
        qDebug()<<"Error sompiling shader type"<<shaderType<<":"<<log<<std::endl;*/
        qDebug()<<shaderType<<": compile error";
    }
    glAttachShader(shaderProgram, shaderObj);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        /*GLchar log[1024];
        glGetProgramInfoLog(shaderProgram, sizeof(log), NULL, log);
        qDebug()<<"Error linking shader program:"<<log<<std::endl;*/
        qDebug()<<"program link error";
    }
    glValidateProgram(shaderProgram);
    glUseProgram(shaderProgram);
}

void GLWidget::repaint()
{
    scale += 0.01f;
    world = QMatrix4x4(1.0f, 0.0f, 0.0f, sinf(scale),
                       0.0f, 1.0f, 0.0f, 0.0f,
                       0.0f, 0.0f, 1.0f, 0.0f,
                       0.0f, 0.0f, 0.0f, 1.0f);
    glUniformMatrix4fv(gWorldLocation, 1, GL_FALSE, world.data());
    update();
}
