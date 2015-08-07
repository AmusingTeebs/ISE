#pragma once

#include "ISEExports.h"
#include "qtoolbar.h"
#include "qtoolbutton.h"
ISEBegin
class GameBar : public QToolBar 
{
	Q_OBJECT
public:
  /** Constructor */
  GameBar();
  
  
  /** Deconstructor */
  ~GameBar();
  public slots:
	  void showOverlay();
  QToolButton* gameButton();
};
ISEEnd