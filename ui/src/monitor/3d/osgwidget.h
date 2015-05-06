#ifndef OSGWidget_h__
#define OSGWidget_h__

#include <QPoint>
#include <QtOpenGL>

#include <osg/ref_ptr>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>

class MyScene;

class OSGWidget : public QGLWidget
{
  Q_OBJECT

public:
  OSGWidget( MyScene * scene, QWidget* parent = 0,
             const QGLWidget* shareWidget = 0,
             Qt::WindowFlags f = 0 );

  virtual ~OSGWidget();

protected:

  virtual void paintEvent( QPaintEvent* paintEvent );
  virtual void paintGL();
  virtual void resizeGL( int width, int height );

  virtual void keyPressEvent( QKeyEvent* event );
  virtual void keyReleaseEvent( QKeyEvent* event );

  virtual void mouseMoveEvent( QMouseEvent* event );
  virtual void mousePressEvent( QMouseEvent* event );
  virtual void mouseReleaseEvent( QMouseEvent* event );
  virtual void wheelEvent( QWheelEvent* event );

  virtual bool event( QEvent* event );

private:

  virtual void onHome();

  osgGA::EventQueue* getEventQueue() const;

  osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> graphicsWindow_;
  osg::ref_ptr<osgViewer::Viewer> viewer_;

  QPoint selectionStart_;
  QPoint selectionEnd_;

  bool selectionActive_;
  bool selectionFinished_;

  void processSelection();

  MyScene * m_scene;
};

#endif
