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


using namespace GameViewer_space; // Ask me about this
ISEBegin
	ISE::ISE()
	:QObject()
{
	
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


void ISE::changeImage()
{
	qDebug() << "ohai!";
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
			//all unneeded now VVVV
			//button->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
			
			button->setIcon(QIcon("C:/Projects/ISE/images/redx.jpg"));
			
			connect(button, &QToolButton::pressed, this, &ISE::changeImage);

			//setting icon size to whatever the size of the button is
			button->setIconSize(button->size());
			button->setFixedSize(150,150);
			layout->addWidget(button);
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
	window->resize(1600,1200);
	window->showMaximized();
	
	//creating widget called container to hold game&score
	QWidget *container = new QWidget();

	//adding the larger container to the dock widget window
	window->setCentralWidget(container);

	//creating a layout to put scores 
	QHBoxLayout *mainLayout = new QHBoxLayout();
	container->setLayout(mainLayout);

	createPlayerLayout(mainLayout);
	createGameLayout(mainLayout);


}
ISEEnd