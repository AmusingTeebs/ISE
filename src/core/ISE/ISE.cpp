// Project
#include "ISE.h"

// Viewer
#include "GameViewer.h"
#include "Scroll.h"

//Interface junk
#include "qmainwindow.h"
#include "qdockwidget.h"
#include "qpixmap.h"
#include "qdir.h"
#include "qgraphicsitem.h"
#include "qlayout.h"
#include "qlabel.h"
#include "qtoolbutton.h"
#include "qboxlayout.h"
#include "qobject.h"
#include "qdebug.h"
#include "qcoreapplication.h"
#include "qaction.h"


using namespace GameViewer_space; // Ask me about this
ISEBegin
	ISE::ISE()
	:QObject()
{
	currentPlayer=1;
	firstScore = 0;
	secondScore = 0;
}

ISE::~ISE()
{

	//I'm editing this on my phone through an app

}

void setBackground(QMainWindow* window)
{
	//Don't worry about this function... just getting a image and setting it to the background.
	QDir dir(QCoreApplication::applicationDirPath());
	dir.cdUp();
	dir.cdUp();
	QString path = dir.path() +  QDir::separator() + "images" + QDir::separator() + "background.JPG";
	QPixmap background(path);
	background = background.scaled(window->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, background);
	window->setPalette(palette);
}





void ISE::createPlayerLayout(QHBoxLayout *c)
{

	QHBoxLayout *playerLayout = new QHBoxLayout();

	//adding the player score layout to the container
	c->addLayout(playerLayout);


	//added first player label & adding it to the playerLayout
	firstLabel = new QLabel();
	firstLabel->setText("Player 1: " + QString::number(firstScore));
	playerLayout->addWidget(firstLabel);

	//adding second player label & adding to playerLayout
	secondLabel = new QLabel();
	secondLabel->setText("Player 2: "+QString::number(secondScore));
	playerLayout->addWidget(secondLabel);

}


void ISE::makeButtons(QLayout *layout)
{
	QToolButton *button = new QToolButton();

	//button->setText("Button: " +QString::number(x));
	button->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
	button->setIcon(QIcon("C:/Projects/ISE/images/background.jpg"));
	connect(button, &QToolButton::pressed, this, &ISE::changeImage);

	//setting icon size to whatever the size of the button is
	button->setIconSize(button->size());
	button->setFixedSize(150,150);
	buttons.append(button);
	layout->addWidget(button);
}


void ISE::changeImage()
{
	qDebug() << "ohai!";
	QToolButton *button_clicked = dynamic_cast<QToolButton*>(QObject::sender());
	
	foreach(QToolButton *button, buttons)
  {

    if(button == button_clicked && currentPlayer == 1 && button->text() == "")
    {
      button->setText("x");
      button->setIcon(QIcon("C:/Projects/ISE/images/redx.jpg"));
	  currentPlayer = 2;
    }

    else if (button  == button_clicked && currentPlayer == 2  && button->text() == "")
	  {
		  button ->setText("y");
		  button->setIcon(QIcon("C:/Projects/ISE/images/blueo.jpg"));
		  currentPlayer = 1;
	}
  }

	evaluate();

}

void ISE::evaluate()
{
  int winner = 0;
  int count_1 = 0;
  int count_2 = 0;
  //rows
  for(int i = 0; i < 3; i ++)
  {
    for( int j = 0; j < 3; j++)
    {
      if(grid.at(i).at(j)->text().contains("x"))
         count_1++;
      
      if(grid.at(i).at(j)->text().contains("y"))
         count_2++;
    }
    if(count_1 == 3)
      winner = 1;
    else if(count_2 == -3)
      winner = 2;
  }
   count_1 = 0;
  count_2 = 0;

  //collumns
  for(int i = 0; i < 3; i ++)
  {
    for( int j = 0; j < 3; j++)
      
    {
          if(grid.at(i).at(j)->text().contains("x"))
         count_1++;
      
      if(grid.at(i).at(j)->text().contains("y"))
         count_2++;
    }
    if(count_1 == 3)
      winner = 1;
    else if(count_2 == -3)
      winner = 2;
  }
    count_1 = 0;
  count_2 = 0;

  //diagonals
  for(int i = 0; i < 3; i ++)
  {
      if( grid.at(i).at(i)->text().contains("x")) count_1++ ;
      if( grid.at(i).at(i)->text().contains("y")) count_2++ ;
  }
    if(count_1 == 3)
      winner = 1;
    else if(count_2 == -3)
      winner = 2;
    count_1 = 0;
    count_2 = 0;

   //diagonals
  for(int i = 0; i < 3; i ++)
  {
     if( grid.at(i).at(2-i)->text().contains("x") )
        count_1++;
      if( grid.at(i).at(2-i)->text().contains("y") )
        count_2++;
  }
    if(count_1 == 3)
      winner = 1;
    else if(count_2 == -3)
      winner = 2;

  if(winner)
  {
    qDebug() << "Winner is planer number " + QString(winner);
    foreach(QToolButton *button, buttons)
    {
      button->setText("");
      button->setIcon(QIcon());
    }
  }
}
void ISE::makeGrid()
{

  for(int i = 0; i < 3; i++)
  {
    QList<QToolButton*> list;
    for(int j = 1; j < 4; j++)
    {
      list.append(buttons.at(i + (j)));
    }
    grid.append(list);
  }
}



void ISE::createGameLayout(QHBoxLayout *x)
{
	//Creating a new layout for our Game
	QVBoxLayout *gameLayout = new QVBoxLayout();
	
	//adding the game's layout to the container
	x->addLayout(gameLayout);

	for (int x=0; x<3; x++)
	{
		//creates new hbox 3 times
		QHBoxLayout * ttLayout = new QHBoxLayout();

		//adds new hbox to the gamelayout
		gameLayout->addLayout(ttLayout);

		//create & add 3 buttons, 3 times, into ttLayout
		for (int x=0; x<3; x++)
		{
			makeButtons(ttLayout);
		}

	}



}

void ISE::initialize(QApplication *application)
{

	//Create the window screen for the program
	window = new QMainWindow();
	window->resize(1300,800);
	window->setStyleSheet("color: purple");
	window->show();

	//creating widget called container to hold game&score
	QWidget *container = new QWidget();

	//adding the larger container to the dock widget window
	window->setCentralWidget(container);

	//creating a layout to put scores 
	QHBoxLayout *mainLayout = new QHBoxLayout();
	container->setLayout(mainLayout);
	createPlayerLayout(mainLayout);
	createGameLayout(mainLayout);
	makeGrid();

}
ISEEnd