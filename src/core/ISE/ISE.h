#pragma once

#include "ISEExports.h"
#include "qapplication.h"
#include "qobject.h"
#include "qlabel.h"
#include "qmainwindow.h"
#include "qtoolbutton.h"
#include "qlayout.h"



ISEBegin
class ISEAPI ISE
{
public:
  /** Constructor */
  ISE();
  
  /** Deconstructor */
  ~ISE();

  /** Initialize ISE! */
  void initialize(QApplication *application);

private: 
	void createPlayerLayout(QHBoxLayout *widget);

	void createGameLayout(QHBoxLayout *widget);

	QList<QToolButton*> buttons;

	QLabel *firstLabel, *secondLabel;

	QMainWindow *window;

	int firstScore, secondScore;



};
ISEEnd