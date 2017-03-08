#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class GLWidget : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    GLuint VBO;

private:
    void addShader(GLuint shaderProgram, const char* shaderText, const int length, GLenum shaderType);
    QTimer *timer;
    float scale;
    GLuint gScaleLocation;

private slots:
    void repaint();
};

#endif
