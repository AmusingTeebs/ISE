// Project
#include "ISE.h"

// Viewer
#include "GameViewer.h"
#include "Scroll.h"
#include "GameOptions.h"

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
#include "BibleChunk.h"
#include "qgraphicsproxywidget.h"


using namespace GameViewer_space; // Ask me about this
ISEBegin
	ISE* ISE::instance = 0;

ISE* ISE::Instance()
{
	if(!instance)
		instance = new ISE();
	return instance;
}
  QString ISE::isePath(const QString &name)
{
  // Get the executable location
  QDir dir(QCoreApplication::applicationDirPath());
  dir.cdUp();
  dir.cdUp();

  return dir.absolutePath() + QDir::separator() + name;
}

QString ISE::imagesPath(const QString &name)
{
  QString sep = QDir::separator();
  return isePath("images" + sep + name);
}

QString ISE::DataPath(const QString &name)
{
  QString sep = QDir::separator();
  return isePath("data" + sep + name);
}

	ISE::ISE()
	:QObject()
{
}

ISE::~ISE()
{

	//I'm editing this on my phone through an app

}

void ISE::start()
{ 
  dialog->close();
  generateChunks("");
}

void ISE::findVerse()
{
  QString text = dynamic_cast<QTextEdit*>(QObject::sender())->toPlainText();
  if(text.isEmpty())
    return;
  chosenValues = text.split(" ");
  if(chosenValues.size() < 3)
    return;
  result->setPlainText(Bible::Instance()->findText(chosenValues.at(0), chosenValues.at(1), chosenValues.at(2)));
}

void ISE::parseBible(const QString &path)
{
  QFile file(path);
  if(!file.open(QIODevice::ReadOnly| QIODevice::Text))
    return;

  QXmlStreamReader xml(&file);

  Bible::Instance()->load(xml);
}
void ISE::generateChunks(const QString &text)
{
	chosenValues = QStringList() << "Hebrews" << "1" << "";
	if(chosenValues.isEmpty())
		return;
	QList<Verse*> verses = Bible::Instance()->findVerses(chosenValues.at(0), chosenValues.at(1), chosenValues.at(2));
	int count = verses.count();
	int rand = qrand() %3, counter = 0, total = 0;
	while(total < verses.count())
	{
		BibleChunk *chunk = new BibleChunk();
		if(total >= rand)
		{
			rand = qrand()%3;
			rand += total;
		}
		for(total; total < rand; total++)
		{
			chunk->load(verses.at(total));
		}
		chunk->generatePieces();
		foreach(Slot *item, chunk->holders)
		{
			viewer->addHolder(item);
		}
		foreach(Piece *item, chunk->pieces)
		{
			viewer->addCloud(item);
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


  //Viewer
  viewer = new GameViewer(window);
  window->setCentralWidget(viewer);

  //Options screen
  dialog = GameOptions::Instance();

  //connect(stack, &GameOptions::finished, this,  &ISE::start);
  dialog->show();
  QGraphicsProxyWidget *item = viewer->scene()->addWidget(dialog);
  item->setOpacity(.8);

  //Search Screen
  viewer->scene()->addItem(dialog->searchScreen);
  dialog->searchScreen->moveBy(1000,200);

}

ISEEnd