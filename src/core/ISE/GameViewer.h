#pragma once

#include "ISEExports.h"
#include "qmainwindow.h"
#include "qgraphicsview.h"
ISEBegin
class GameViewer : public QGraphicsView
{
public:
  /** Constructor */
  GameViewer(QMainWindow *window);
};
ISEEnd