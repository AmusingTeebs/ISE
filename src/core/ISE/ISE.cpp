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
#include "qdialog.h"
#include <QXmlStreamReader>
#include "qtextedit.h"
#include "qfile.h"
#include "Bible.h"
#include "GameScreen.h"
#include "qsettings.h"
#include "qpushbutton.h"

using namespace GameViewer_space; // Ask me about this
ISEBegin

  QString ISE::isePath(const QString &name)
{
  // Get the executable location
  QDir dir(QCoreApplication::applicationDirPath());
  dir.cdUp();
  dir.cdUp();

  return dir.absolutePath() + QDir::separator() + name;
}

QString ISE::DataPath(const QString &name)
{
  QString sep = QDir::separator();
  return isePath("data" + sep + name);
}

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

void ISE::popup()
{

}

void ISE::start()
{  

}

void ISE::findVerse()
{
  QString text = dynamic_cast<QTextEdit*>(QObject::sender())->toPlainText();
  if(text.isEmpty())
    return;
  QStringList values = text.split(" ");
  if(values.size() < 3)
    return;
  result->setPlainText(Bible::Instance()->find(values.at(0), values.at(1), values.at(2)));
}

void ISE::parseBible(const QString &path)
{
  QFile file(path);
  if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
    return;

  QXmlStreamReader xml(&file);

  Bible::Instance()->load(xml);

  Bible::Instance()->find("Genis","1","2");
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
void createNew()
{

}
void login(QMainWindow *window)
{
      //working path
  QString path( ISE::DataPath("configuration") + ".ini");

  QFile file(path);
  if(!file.exists())
    createNew();

  if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
    return;

  //open  the profile settings
  QSettings *settings = new QSettings(path, QSettings::IniFormat);

  //Load Kraken Settings
  settings->beginGroup("Settings");
  QString user = settings->value("User").toString();
  QString userPath = settings->value("Path").toString();
  settings->endGroup();

}

void ISE::initialize(QApplication *application)
{

	//Create the window screen for the program
	window = new GameScreen();
  window->resize(1000,1000);
  window->showFullScreen();


    //working path
  QString path( DataPath("configuration") + ".ini");

  //soft catch
  QFile file(path);

  //Load in the bible xml
  parseBible("C:\\Projects\\ISE\\docs\\esv.xml");

  //show the initial dialog
  QDialog *dialog = new QDialog(window,Qt::SplashScreen);
  QHBoxLayout *layout = new QHBoxLayout;
  dialog->setLayout(layout);
  stack = new QStackedWidget(dialog);
  layout->addWidget(stack);

  stack->addWidget(new LoginScreen(stack));
  stack->addWidget(new SearchScreen(stack));
  dialog->show();

}
ISEEnd