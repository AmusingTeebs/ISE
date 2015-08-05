#pragma once

#include "ISEExports.h"
#include "qtextedit.h"
#include <QXmlStreamReader>
#include "qmap.h"
ISEBegin


class Verse 
{
  friend class Bible;
public:
  Verse() {};
  void setText(const QString &value)  { data = value;};

protected:
  QString data;
};

class Chapter 
{
  friend class Bible;
public:
  Chapter() {};
  Verse* add(const QString &key) { Verse *v = new Verse(); data.insert(key,v); return v;};
  QList<Verse*> find(const QString &range) 
  {
    if(range.isEmpty())
      return data.values();
      QList<Verse*> verses;
      QStringList values = range.split("-");
      int first = values.first().toInt();
      int last = values.last().toInt();
      while(first <= last)
      {
        Verse *verse = data.value(QString::number(first));
        if(verse)
          verses.append(verse);
        first++;
      }
      return verses;
  };
protected:
  QMap<QString,Verse*> data;
};

class Book 
{
  friend class Bible;
public:
  Book() {};
  Chapter* add(const QString &key)  { Chapter *c = new Chapter(); data.insert(key,c); return c;};
 
  QList<Chapter*> find(const QString &range) 
    {
      if(range.isEmpty())
        return data.values();
      QList<Chapter*> chapters;
      QStringList values = range.split("-");
      int first = values.first().toInt();
      int last = values.last().toInt();
      do
      {
        Chapter *chapter = data.value(QString::number(first));
        if(chapter)
          chapters.append(chapter);
        first++;
      }
      while(first <= last);
      return chapters;
  };
protected:
  QMap<QString,Chapter*> data;
};

class Bible 
{


public:
  /** Constructor */
  Bible();

  Book* add(const QString &key) { Book *b = new Book(); data.insert(key,b); return b;};

  QString find(const QString &book, const QString &chapter, const QString &verse);

  void load(QXmlStreamReader &reader);

  /** Deconstructor */
  ~Bible();

  static Bible* Instance();
  static Bible* instance;
  QMap<QString,Book*> data;

  Book defaultBook;
  Chapter defaultChapter;
  Verse defaultVerse;

};
ISEEnd