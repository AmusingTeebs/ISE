#pragma once

#include "ISEExports.h"
#include "qstackedwidget.h"
#include "qapplication.h"
#include "qobject.h"
#include "qlabel.h"
#include "qmainwindow.h"
#include "qtoolbutton.h"
#include "qlayout.h"
#include "qobject.h"
#include "qpushbutton.h"
#include "qtextedit.h"
#include "qstackedwidget.h"
#include "qfile.h"
#include "Bible.h"
#include "qcombobox.h"
#include "qformlayout.h"
#include "qgraphicsproxywidget.h"
#include "GameScreen.h"
#include "qdebug.h"
#include "GameViewer.h"
#include "qlineedit.h"
#include "qdialog.h"
ISEBegin
	class SearchScreen;
class GameOptions : public QDialog 
{
	Q_OBJECT
public:
  /** Constructor */
	GameOptions(QWidget *parent);
  
  void setCurrentIndex(int index);

  static GameOptions* Instance();

  QStackedWidget *stack; 
  static GameOptions *instance;
  /** Deconstructor */
  ~GameOptions();

  SearchScreen *searchScreen;
signals:
  void finished();

};

class ProfileScreen : public QWidget
{
	Q_OBJECT

public:
  /** Constructor */
  ProfileScreen(GameOptions *widget);

  GameOptions *stack;
  /** Deconstructor */
  ~ProfileScreen() {};
  private slots:
	  void submit();
private:
	QFormLayout *layout;
};
class LoginScreen : public QWidget
{

  Q_OBJECT

public:
  /** Constructor */
  LoginScreen(GameOptions *widget)
  {
    stack = widget;
    QHBoxLayout *layout = new QHBoxLayout(this);
    //New profile
    QPushButton *button = new QPushButton("New");
    button->setStyleSheet("font: 30px");
    layout->addWidget(button);
    connect(button,SIGNAL(clicked()),this, SLOT(next()));

    //Existing profile
    button = new QPushButton("Existing");
    button->setStyleSheet("font: 30px");

    //working path
    QString path;//( ISE::DataPath("configuration") + ".ini");

    //soft catch
    QFile file(path);

    if(!file.exists())
      button->setEnabled(false);
    layout->addWidget(button);
  };

  GameOptions *stack;
  /** Deconstructor */
  ~LoginScreen() {};
  private slots:
    void next()
    {
		stack->setCurrentIndex(stack->stack->currentIndex()+1);
    };

};


class SearchScreen : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
public:
  /** Constructor */
 SearchScreen(GameOptions *options);

  ~SearchScreen() {};

	void findText();

	GameOptions *options;

  public slots:
	  void currentIndexChanged(int index);
private: 
	void updateComboBoxes();
	void loadBox(QComboBox* box);
  QTextEdit *result;

  QString currentBook;
  QString currentChapter;

  GameOptions *stack;
  /** Deconstructor */

  QFormLayout *layout;

};
ISEEnd