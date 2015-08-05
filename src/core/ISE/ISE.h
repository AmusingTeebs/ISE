#pragma once

#include "ISEExports.h"
#include "GameScreen.h"
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

  void popup();

  void parseBible(const QString &path);

  static QString DataPath(const QString &path);
  static QString isePath(const QString &path);

private: 
  void createPlayerLayout(QHBoxLayout *widget);

  void createGameLayout(QHBoxLayout *widget);

  QList<QToolButton*> buttons;

  QLabel *firstLabel, *secondLabel;

  GameScreen *window;

  int firstScore, secondScore, currentPlayer;

  void makeGrid();

  void evaluate();

  QList< QList<QToolButton*> > grid;

  QHash<QString,QString> verses;

  QStackedWidget *stack;

  QTextEdit *result;

  QList<QWidget*> cache;
  public slots: 

    void findVerse();

    void start();

    void changeImage();

};

class LoginScreen : public QWidget
{

  Q_OBJECT

public:
  /** Constructor */
  LoginScreen(QStackedWidget *widget)
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
    QString path( ISE::DataPath("configuration") + ".ini");

    //soft catch
    QFile file(path);

    if(!file.exists())
      button->setEnabled(false);
    layout->addWidget(button);
  };

  QStackedWidget *stack;
  /** Deconstructor */
  ~LoginScreen() {};
  private slots:
    void next()
    {
      stack->setCurrentIndex(stack->currentIndex()+1);
    };

};

class SearchScreen : public QWidget
{

  Q_OBJECT

public:
  /** Constructor */
  SearchScreen(QStackedWidget *widget)
  {
    QList<Book*> books = Bible::Instance()->data.values();

    QHBoxLayout *layout = new QHBoxLayout(this);
    QTextEdit *edit = new QTextEdit();
    bool value = connect(edit,SIGNAL(textChanged()), this, SLOT(findVerse()));
    layout->addWidget(edit);
    result = new QTextEdit();
    layout->addWidget(result);

  };
  ~SearchScreen() {};

  public slots:

  void findVerse()
  {
    QString text = dynamic_cast<QTextEdit*>(QObject::sender())->toPlainText();
    if(text.isEmpty())
      return;
    QStringList values = text.split(" ");
    if(values.size() < 3)
      return;
    result->setPlainText(Bible::Instance()->find(values.at(0), values.at(1), values.at(2)));
  }
private: 
  QTextEdit *result;
  QStackedWidget *stack;
  /** Deconstructor */


};

ISEEnd