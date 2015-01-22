// Project
#include "GameViewer.h"

//Our 2d viewer
#include "qgraphicsscene.h"

GameViewerBegin
  GameViewer::GameViewer(QMainWindow *window)
  : QGraphicsView(window)
{
  //Create a scene that we can change the background color of
  class GameScene : public QGraphicsScene 
  {
  public:
    void drawBackground( QPainter * painter, const QRectF & rect )
    {
      // Set the background to blue for now
      painter->setBackground(QBrush(QColor(Qt::blue)));
    }
  };

  //Render the 2d scene
  GameScene *scene = new GameScene;
  setScene(scene);
}

GameViewerEnd