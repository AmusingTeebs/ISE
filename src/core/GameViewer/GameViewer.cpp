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
#include "qdialog.h"
#include "qgraphicsproxywidget.h"

GameViewerBegin
	QString imagesPath(const QString &fileName)
{
	 QDir dir(QCoreApplication::applicationDirPath());
  dir.cdUp();
  dir.cdUp();


  return dir.absolutePath() + QDir::separator() + "images" + QDir::separator() + fileName;
}

TextHolder::TextHolder()
{

}
QSize TextHolder::getNextPosition()
{
	int x = 0;
	if(items.size() > 5) 
		x = 700;
	return QSize(200+x,100 + 100*(items.size()%6));
}
void TextHolder::addItem(QGraphicsTextItem* item)
{
	item->setParentItem(this);
	item->setTextWidth(500);
	QSize size = getNextPosition();
	item->moveBy(size.width(),size.height());
	items.append(item);
}
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
      QString path = dir.path() +  QDir::separator() + "images" + QDir::separator() + "background.png";
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
  int w= sceneRect().width() * .70;
  int h = sceneRect().height() * .60;
  int x = .5 * (sceneRect().width() - w);
  int y = sceneRect().height() - h;

  //Text holder
  bible = new TextHolder();
  bible->setPixmap(QPixmap(imagesPath("book.png")).scaled(w,h));
  scene->addItem(bible);
  bible->moveBy(x,y+100);

  //Transparent overlay
  overlay = new QGraphicsRectItem();
  overlay->setRect(sceneRect());
  overlay->setOpacity(.75);
  overlay->setBrush(QBrush(QColor(Qt::black)));
  scene->addItem(overlay);
  }

  

void GameViewer::addCloud(QGraphicsItem *item)
{
	int width = item->boundingRect().width();
	QGraphicsPixmapItem *cloud = new QGraphicsPixmapItem(QPixmap(imagesPath("cloud.png")).scaled(width+20,60));
	item->setParentItem(cloud);
	item->moveBy(cloud->boundingRect().width()/2 - item->boundingRect().width()/2,cloud->boundingRect().height()/2 - item->boundingRect().height()/2);
	scene()->addItem(cloud);
	cloud->setFlag(QGraphicsItem::ItemIsMovable);
	int cloudx = 100 + clouds.count()*50;
	int cloudy = 200;
	cloud->moveBy(cloudx,cloudy);
	clouds.append(cloud);
}

void GameViewer::addHolder(QGraphicsTextItem *item)
{
	bible->addItem(item);
}
GameViewerEnd