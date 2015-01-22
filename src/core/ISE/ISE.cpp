// Project
#include "ISE.h"

//Interface junk
#include "qmainwindow.h"
#include "qdockwidget.h"
#include "qpixmap.h"
#include "qdir.h"

ISEBegin
  ISE::ISE()
{

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

void ISE::initialize(QApplication *application)
{
  //Create the window screen for the program
  QMainWindow *window = new QMainWindow();
  window->resize(2200,1600);
  window->showMaximized();
  setBackground(window);

  // Adding some dock widgets to the window. Is for fun.
  QDockWidget *widget;
  for(int i = 0; i < 10; i++)
  {
    widget = new QDockWidget(0);
    window->addDockWidget(Qt::RightDockWidgetArea, widget);
  }

  //Set the background to this image
  widget->setStyleSheet("background-image:nothing;");
}
ISEEnd