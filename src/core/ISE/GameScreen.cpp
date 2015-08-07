// Project
#include "GameScreen.h"
#include "ISE.h"
#include "qfile.h"
#include "qtextstream.h"
#include "GameBar.h"
ISEBegin

  void setStyles(GameScreen *screen)
{  
  QFile file(ISE::DataPath("charcoal.txt"));
  if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
    return;
  QTextStream in(&file);
  screen->setStyleSheet(in.readAll());

}

GameScreen::GameScreen()
  : QMainWindow()
{
  setStyles(this);
  addToolBar(Qt::ToolBarArea::LeftToolBarArea,new GameBar());
}


GameScreen::~GameScreen()
{

}

ISEEnd