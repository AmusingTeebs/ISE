#pragma once

#include "GameViewerExports.h"
#include "qmainwindow.h"
#include "qgraphicsview.h"
GameViewerBegin
class GameViewerAPI GameViewer : public QGraphicsView
{
public:
  /** Constructor */
  GameViewer(QMainWindow *window);
};
GameViewerEnd