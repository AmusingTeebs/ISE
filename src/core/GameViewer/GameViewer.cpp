// Project
#include "GameViewer.h"

//Our 2d viewer
#include "qgraphicsscene.h"
#include "qdir.h"
#include "qcoreapplication.h"
#include "qgraphicsitem.h"
#include "qpixmap.h"
#include "qdebug.h"
#include "qdesktopwidget.h"
#include "qapplication.h"

GameViewerBegin
  GameViewer::GameViewer(QMainWindow *window)
  : QGraphicsView(window)
{
  //Create a scene that we can change the background color of
  class GameScene : public QGraphicsScene 
  {

  public:
    GameScene()
      :QGraphicsScene()
    {
      QDir dir(QCoreApplication::applicationDirPath());
      dir.cdUp();
      dir.cdUp();
      QString path = dir.path() +  QDir::separator() + "images" + QDir::separator() + "background.jpg";
      QPixmap pim(path);
      item = new QGraphicsPixmapItem();
      QRect rect = QApplication::desktop()->screenGeometry();
      item->setPixmap(pim.scaled(rect.width(),rect.height()));
      addItem(item);
    }

    QGraphicsPixmapItem *item;
  };


  GameScene *scene = new GameScene;

  setScene(scene);
}

GameViewerEnd