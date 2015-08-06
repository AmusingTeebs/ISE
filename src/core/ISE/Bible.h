#pragma once

#include "ISEExports.h"
#include "qtextedit.h"
#include <QXmlStreamReader>
#include "qmap.h"
ISEBegin

  class StructureType
  {
  public:
    StructureType(){};

    QList<StructureType*> find(const QString &range);

      QMap<QString,StructureType*> data;
  };

class Verse : public StructureType
{
  friend class Bible;
public:
  Verse() {};
  void setText(const QString &value)  { data = value;};

protected:
  QString data;
};

class Chapter : public StructureType
{
  friend class Bible;
public:
  Chapter(const QString &_name= "") {name = _name;};
  Verse* add(const QString &key) { Verse *v = new Verse(); data.insert(key,v); return v;};

  QString name;
};

class Book : public StructureType
{
  friend class Bible;
public:
  Book(const QString &_name = "") {name = _name;};

  Chapter* add(const QString &key)  { Chapter *c = new Chapter(key); data.insert(key,c); return c;};
 
  QString name;

};

class Bible 
{


public:
  /** Constructor */
  Bible();

  Book* add(const QString &key) { Book *b = new Book(key); data.insert(key,b); return b;};

  QString find(const QString &book, const QString &chapter, const QString &verse);

  void load(QXmlStreamReader &reader);


  static Bible* Instance();

private:

  Book defaultBook;

  static Bible* instance;

  QMap<QString,Book*> data;
};
ISEEnd