// Project
#include "GameScreen.h"
#include "ISE.h"
#include "qfile.h"
#include "qtextstream.h"
ISEBegin
	GameScreen::GameScreen()
  : QMainWindow()
{
  QFile file(ISE::DataPath("charcoal.txt"));
  if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
    return;
  QTextStream in(&file);
  setStyleSheet(in.readAll());
}


GameScreen::~GameScreen()
{

}

ISEEnd