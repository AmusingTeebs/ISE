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
#include "qformlayout.h"
#include "GameScreen.h"
#include "qdebug.h"
#include "GameViewer.h"
ISEBegin
  
class Stack : public QStackedWidget
{
  Q_OBJECT
public:
  Stack(QWidget *widget) : QStackedWidget(widget) {}
  void setCurrentIndex(int index);

signals:
  void finished();
};


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

  void parseBible(const QString &path);

  static QString DataPath(const QString &path);

  static QString imagesPath(const QString &path);
  static QString isePath(const QString &path);

  static ISE* Instance();
  void generateChunks(const QString &text);

	static ISE* instance;
  GameScreen *window;

  GameViewer_space::GameViewer *viewer;

  QHash<QString,QString> verses;

  Stack *stack;

  QTextEdit *result;

  QDialog *dialog;
  QList<QWidget*> cache;

  QStringList chosenValues;
  public slots: 

    void findVerse();

    void start();

};

class LoginScreen : public QWidget
{

  Q_OBJECT

public:
  /** Constructor */
  LoginScreen(Stack *widget)
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

  Stack *stack;
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
  SearchScreen(Stack *widget)
  {
    stack = widget;
    QHBoxLayout *hbox = new  QHBoxLayout(this);
    QFormLayout *layout = new QFormLayout;
    hbox->addLayout(layout);
    //QList<Book*> books = Bible::Instance()->data.values();
    //QComboBox *combo;
    //combo = new QComboBox(this);
    //foreach(Book* book, books)
    //  combo->addItem(book->name);
    //layout->addRow("Book",combo);
    //    combo = new QComboBox(this);
    //foreach(Book* book, books)
    //  combo->addItem(book->name);
    //layout->addRow("Beginning Chapter",combo);
    //    combo = new QComboBox(this);
    //foreach(Book* book, books)
    //  combo->addItem(book->name);
    //layout->addRow("Ending Chapter",combo);
    //    combo = new QComboBox(this);
    //foreach(Book* book, books)
    //  combo->addItem(book->name);
    //layout->addRow("Beginning Verse",combo);
    //        combo = new QComboBox(this);
    //foreach(Book* book, books)
    //  combo->addItem(book->name);
    //layout->addRow("Ending Verse",combo);

    QPushButton *button = new QPushButton("Start", this);
    layout->addWidget(button);
    connect(button,&QPushButton::clicked, this, &SearchScreen::next);
    QTextEdit *edit = new QTextEdit();
    hbox->addWidget(edit);
    bool value = connect(edit,SIGNAL(textChanged()), this, SLOT(findVerse()));
    hbox->addWidget(edit);
    result = new QTextEdit();
    hbox->addWidget(result);
    hbox->addWidget(result);

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
    result->setPlainText(Bible::Instance()->findText(values.at(0), values.at(1), values.at(2)));
  }
    private slots:
    void next()
    {
      stack->setCurrentIndex(stack->currentIndex()+1);
    };
private: 
  QTextEdit *result;
  Stack *stack;
  /** Deconstructor */


};

ISEEnd