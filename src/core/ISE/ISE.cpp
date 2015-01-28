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


using namespace GameViewer_space; // Ask me about this
ISEBegin
	ISE::ISE()
{
	firstScore = 0;
	secondScore = 0;
}

ISE::~ISE()
{

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

void ISE::createGameLayout(QHBoxLayout *x)
{
	//Creating a new layout for our Game
	QHBoxLayout *gameLayout = new QHBoxLayout();

	//adding the game's layout to the container
	x->addLayout(gameLayout);

	for (int x=0; x<9; x++)
	{
		QToolButton *button = new QToolButton();
		button->setText("Button: " +QString::number(x));
		button->setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
		gameLayout->addWidget(button);
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
	QHBoxLayout *mainLayout = new QHBoxLayout();
	container->setLayout(mainLayout);

	createPlayerLayout(mainLayout);
	createGameLayout(mainLayout);


}
ISEEnd