#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    this->setFocusPolicy(Qt::StrongFocus);


    m_meshProgram = NULL;
    m_skeletonProgram = NULL;
    m_pointProgram = NULL;

    m_polygonMode = true;


    m_horAngle = 45.0f;
    m_verAngle = 0.0f;
    distance = 100.0f;
    scale = 1.0f;
    m_eyeDist = QVector3D(0.0f,0.0f,0.0f);


    connect(&m_timer,SIGNAL(timeout()),this,SLOT(on_gameCycle()));
    m_timer.setInterval(10);
    m_timer.start();
}


void GLWidget::initShaders(QOpenGLShaderProgram*& m_program,const QString& shaderName,
                           bool v = false,bool c = false, bool n = false, bool t=false)
{
    m_program = new QOpenGLShaderProgram(this);

    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,  QString(":/shader/res/%1VShader.glsl").arg(shaderName));
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(":/shader/res/%1FShader.glsl").arg(shaderName));

    if(v)
        m_program->bindAttributeLocation("a_position",VERTEX_ATTRIBUTE);
    if(c)
        m_program->bindAttributeLocation("a_color"   ,COLOUR_ATTRIBUTE);
    if(n)
        m_program->bindAttributeLocation("a_normal"  ,NORMAL_ATTRIBUTE);
    if(t)
        m_program->bindAttributeLocation("a_texCoord",TEXTURE_ATTRIBUTE);

    m_program->link();
    m_program->bind();
}


void GLWidget::setupShaders(QOpenGLShaderProgram *&m_program)
{
    m_program->bind();

    m_program->setUniformValue("mat_projection",m_projectMatrix);
    m_program->setUniformValue("mat_view",m_viewMatrix);
}

void GLWidget::setupTexture(QOpenGLTexture *&texture, const QString &filename)
{
    if(texture)
        delete texture;

    QImage img(filename);
    texture = new QOpenGLTexture(img);

    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
}


void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1.0,1.0,1.0,1.0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_TEXTURE_2D);


    initShaders(m_skeletonProgram,"Graph",true,false,true,false);

    qsrand(QTime::currentTime().msec()*QTime::currentTime().second());


    m_terrain.LoadTerrainMesh("E:/Projects/QtProjects_new/MyPysicsSimulator/res/models/bucketOBJ.obj",
                              _TRIANGLES,1.0f);


    Collider ball;
    ball.LoadMeshs("C:/Users/liuzh/Downloads/only_quad_sphere1.obj",
                   _TRIANGLES,2.0f);
    ball.dir = QVector3D(1.0,1.0,1.0).normalized();
    m_balls.append(ball);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,width(),height());

    m_projectMatrix.setToIdentity();

    m_projectMatrix.perspective(45.0f,(float)w/(float)h,0.1f,100000.0f);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_eyePos = m_eyeDist+QVector3D(scale*distance*cos(PI*m_verAngle/180.0)*cos(PI*m_horAngle/180.0),
                                   scale*distance*sin(PI*m_verAngle/180.0),
                                   scale*distance*cos(PI*m_verAngle/180.0)*sin(PI*m_horAngle/180.0));
    m_viewMatrix.setToIdentity();
    m_viewMatrix.lookAt(m_eyePos,m_eyeDist,QVector3D(0,1,0));
    m_modelMat.setToIdentity();


//    if(!m_polygonMode)
//        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//    else
//        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    setupShaders(m_skeletonProgram);
    m_skeletonProgram->setUniformValue("viewPos",m_eyePos);
    m_skeletonProgram->setUniformValue("objectColor",QVector3D(0.56,0.49,0.44));
    m_terrain.RenderMesh(m_skeletonProgram,m_modelMat);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    for(int i=0; i<m_balls.size(); ++i)
    {
        m_skeletonProgram->setUniformValue("objectColor",m_balls[i].color);
        m_balls[i].RenderCollider(m_skeletonProgram,m_modelMat);
    }

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_clickpos = event->pos();

    // 求左上角的坐标
    if(event->modifiers() == Qt::ControlModifier && event->buttons() == Qt::LeftButton)
    {

        double min = 999999;
        int id = -1;


        for(int i=0; i<m_terrain.findex.size(); i+=2)
        {
            int _id = m_terrain.findex[i];
            QVector4D pos = QVector4D(m_terrain.vertexes[_id],1);
            QVector4D project_pos = m_projectMatrix*m_viewMatrix*m_modelMat*pos;
            QVector3D project_pos2(project_pos*(1.0/project_pos.w()));
            QVector2D screen_pos(project_pos2.x()*(width()/2)+width()/2,
                             project_pos2.y()*(-height()/2)+height()/2);
            double dist = screen_pos.distanceToPoint(QVector2D(m_clickpos));

            if(dist < min)
            {
                min = dist;
                id =  _id;
            }
        }

        Collider ball;
        ball.LoadMeshs("C:/Users/liuzh/Downloads/only_quad_sphere1.obj",_TRIANGLES,2.0f);


        QVector3D new_pos = m_terrain.vertexes[id];

        ball.pos = new_pos;
        ball.dir = -(m_terrain.normals[id+1]).normalized();
        m_balls.append(ball);
        update();
    }


}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QPoint cur = event->pos();

        double dx = (cur.x() - m_clickpos.x())/5.0;
        double dy = (cur.y() - m_clickpos.y())/5.0;

        m_horAngle +=dx;
        if(m_verAngle+dy <90.0 && m_verAngle+dy>-90.0)
            m_verAngle +=dy;

        m_clickpos = cur;
        update();
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W)
        m_eyeDist.setY(m_eyeDist.y()+5);
    if(e->key() == Qt::Key_S)
        m_eyeDist.setY(m_eyeDist.y()-5);
    if(e->key() == Qt::Key_C)
        m_polygonMode = ! m_polygonMode;
    this->update();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    double ds = 0.03;
    if(event->delta()>0 && scale-ds>0)
        scale-=ds;
    else if(event->delta()<0)
        scale+=ds;
    update();
}

void GLWidget::on_gameCycle()
{
    for(int i=0; i<m_balls.size(); ++i)
    {
        m_balls[i].Move();
    }
    update();
}

GLWidget::~GLWidget(){}
