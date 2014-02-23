/*
  Q Light Controller Plus
  monitor3dview.cpp

  Copyright (C) Jano Svitok

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

#include "monitor3dview.h"
#include "doc.h"

Monitor3dView::Monitor3dView(Doc *doc, QWidget *parent)
    : QWidget(parent)
    , m_doc(doc)
{
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_OpaquePaintEvent);

    irr::SIrrlichtCreationParameters createParams;
    createParams.WindowId = ( void * )this->winId();
    m_device = irr::createDeviceEx( createParams );
    m_scene = m_device->getSceneManager();
    m_driver = m_device->getVideoDriver();
    irr::scene::IAnimatedMesh* mesh = m_scene->getMesh("/home/janek/models/sydney.md2");
    irr::scene::IAnimatedMeshSceneNode* node = m_scene->addAnimatedMeshSceneNode( mesh );

    if (node)
    {
        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setMD2Animation(irr::scene::EMAT_STAND);
        node->setMaterialTexture( 0, m_driver->getTexture("/home/janek/models/sydney.bmp") );
    }
    m_scene->addCameraSceneNode(0, irr::core::vector3df(0,30,-40), irr::core::vector3df(0,5,0));
}

Monitor3dView::~Monitor3dView()
{
    m_device->drop();
}

void Monitor3dView::writeUniverse(int /*index*/, const QByteArray & /*ua*/)
{
    //update();
}

void Monitor3dView::paintEvent(QPaintEvent */*event*/)
{
    if (m_device && m_device->run())
    {
        m_device->getTimer()->tick();

        if (isVisible() && isEnabled())
        {
            m_driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
            m_scene->drawAll();
            m_driver->endScene();
        }
        else
        {
            m_device->yield();
        }
    }
}

QPaintEngine * Monitor3dView::paintEngine() const
{
    return 0;
}

