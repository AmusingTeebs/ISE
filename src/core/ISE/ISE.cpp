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
}

ISE::~ISE()
{

	//I'm editing this on my phone through an app

}

void ISE::start()
{  
  stack->close();
  viewer->close();
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
  stack = new Stack(dialog);
  layout->addWidget(stack);

  stack->addWidget(new LoginScreen(stack));
  stack->addWidget(new SearchScreen(stack));
  bool good = connect(stack, &Stack::finished, this,  &ISE::start);
  dialog->show();
  viewer = new GameViewer(window);
  window->setCentralWidget(viewer);
}

void Stack::setCurrentIndex(int index)
{ 
  QStackedWidget::setCurrentIndex(index);
  if(index >= count())
    emit finished();
}
ISEEnd