#include "pickhandler.h"
#include <osgViewer/Viewer>

bool PickHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    if ( ea.getEventType()!=osgGA::GUIEventAdapter::RELEASE ||
      ea.getButton()!=osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON ||
      !((ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL) ||
      (ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_SHIFT)))
    return false;

    osgViewer::View* viewer = dynamic_cast<osgViewer::View*>(&aa);
    if ( viewer )
    {
    osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
        new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
    osgUtil::IntersectionVisitor iv( intersector.get() );
    viewer->getCamera()->accept( iv );

    if ( intersector->containsIntersections() )
    {
        osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
        doUserOperations( result, ea );
    }
    }
    return false;
}

void PickHandler::doUserOperations(osgUtil::LineSegmentIntersector::Intersection &result, const osgGA::GUIEventAdapter &ea)
{
    osg::Drawable* shape = dynamic_cast<osg::Drawable*>( result.drawable.get() );
    if ( shape ){
       if(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_SHIFT)
       {
           _scene->setToBeRotatable(shape);
       }
       else //in case both shift and ctrl or only ctrl
        _scene->setToBeMovable(shape);
    }
}