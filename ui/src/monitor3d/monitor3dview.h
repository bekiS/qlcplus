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

#ifndef MONITOR3DVIEW_H
#define MONITOR3DVIEW_H

#include <QWidget>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <irrlicht.h>

#pragma GCC diagnostic pop

#include "fixture.h"

class Doc;

class Monitor3dView : public QWidget
{
    Q_OBJECT

public:
    Monitor3dView(Doc *doc, QWidget *parent = 0);
    ~Monitor3dView();

    void writeUniverse(int index, const QByteArray& ua);

private:
    Doc *m_doc;

protected:
    virtual void paintEvent (QPaintEvent * event);
    QPaintEngine * paintEngine() const;

private:
    irr::IrrlichtDevice *m_device;
    irr::video::IVideoDriver* m_driver;
    irr::scene::ISceneManager* m_scene;
};

#endif // MONITOR3DVIEW_H
