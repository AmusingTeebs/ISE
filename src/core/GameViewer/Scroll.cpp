// Project
#include "Scroll.h"
#include "qicon.h"
#include "qdir.h"
#include "qcoreapplication.h"
GameViewerBegin
  Scroll::Scroll()
  : QGraphicsWidget()
{
   QDir dir(QCoreApplication::applicationDirPath());
  dir.cdUp();
  dir.cdUp();
  QString path = dir.path() +  QDir::separator() + "images" + QDir::separator() + "background.JPG";
  QPixmap background(path);
  background = background.scaled(QSize(1500,1000), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Background, background);
  setPalette(palette);
}

Scroll::~Scroll()
{
}

GameViewerEnd