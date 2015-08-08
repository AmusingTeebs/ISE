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
#include "GameOptions.h"
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


  QTextEdit *result;

  GameOptions *dialog;
  QList<QWidget*> cache;

  QStringList chosenValues;
  public slots: 

    void findVerse();

    void start();

};


ISEEnd