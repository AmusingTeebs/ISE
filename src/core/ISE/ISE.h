#pragma once

#include "ISEExports.h"
#include "qapplication.h"
#include "qobject.h"
#include "qlabel.h"
#include "qmainwindow.h"
#include "qtoolbutton.h"
#include "qlayout.h"
#include "qobject.h"




ISEBegin
class ISE : public QObject
{

	Q_OBJECT

public:
  /** Constructor */
  ISE();
  
  /** Deconstructor */
  ~ISE();

  /** Initialize ISE! */
  void initialize(QApplication *application);

  void ISE::makeButtons(QLayout *layout);


private: 
	void createPlayerLayout(QHBoxLayout *widget);

	void createGameLayout(QHBoxLayout *widget);

	QList<QToolButton*> buttons;

	QLabel *firstLabel, *secondLabel;

	QMainWindow *window;

	int firstScore, secondScore, currentPlayer;

	void makeGrid();

	void evaluate();

	QList< QList<QToolButton*> > grid;


public slots: 

	void changeImage();

};
ISEEnd