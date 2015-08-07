#pragma once

#include "GameViewerExports.h"
#include "qmainwindow.h"
#include "qgraphicsview.h"
#include "qgraphicsitem.h"
GameViewerBegin
	class TextHolder : public QGraphicsPixmapItem
	{
	public:
		TextHolder();
		void addItem(QGraphicsTextItem* item);

		QSize getNextPosition();

		QList<QGraphicsItem*> items;
	};
class GameViewerAPI GameViewer : public QGraphicsView
{
public:
  /** Constructor */

  GameViewer(QMainWindow *window);

  void addCloud(QGraphicsItem *item);

  void addHolder(QGraphicsTextItem *item);

  QGraphicsRectItem *overlay;
  TextHolder* bible;
  QList<QGraphicsPixmapItem*> clouds;
};
GameViewerEnd