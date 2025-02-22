#ifndef QGL_MyGLWidget_H
#define QGL_MyGLWidget_H

#include"global.h"
#include"cube.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{


  public:
    MyGLWidget( QWidget *parent=0 );
    ~MyGLWidget();
    void RebuildCube();
    QVector3D getArcBallVector(int x, int y);
    void SetCube(Cube c){ cube = c;}
    void resetRotate();


  protected:
    void initializeGL(void);
    void resizeGL( int w, int h );
    void paintGL();
    void keyPressEvent( QKeyEvent *e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void timerEvent(QTimerEvent*);
    void updateMouse();

  private:
    QOpenGLShaderProgram shaderProgram;
    GLuint programID;
    QMatrix4x4 mModelMatrix;
    QMatrix4x4 mRotate;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mProjectionMatrix;
    QVector<QVector3D> mModelPosition;

    QVector3D cameraPos;
    QVector3D mPosition;
    QOpenGLTexture* mTexture;
    GLuint MatrixID;
    GLuint vertexPosition_modelspaceID;
    GLuint vertexUVID;
    GLuint vertexbuffer;
    GLuint uvbuffer;

    int mWidth;
    int mHeight;

    int oldX, oldY;
    int newX, newY;

    bool rotate;
    bool useArcBall;
    bool built = false;//用于标记是否运行过InitializeGL来确定是否要在析构函数中析构uv数组等
    Cube cube;
};


#endif // QGL_MyGLWidget_H
