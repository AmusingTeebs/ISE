#pragma once

#include "ISEExports.h"
#include "qmainwindow.h"

ISEBegin
class GameScreen : public QMainWindow 
{

	Q_OBJECT

public:
  /** Constructor */
  GameScreen();
  

  /** Deconstructor */
  ~GameScreen();

};
ISEEnd