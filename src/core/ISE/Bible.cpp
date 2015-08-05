// Project
#include "Bible.h"
#include "qdebug.h"

ISEBegin

  Bible* Bible::instance = 0;

Bible::Bible()
{

}

Bible* Bible::Instance()
{
  if(!instance)
    instance = new Bible();
  return instance;
}

void Bible::load(QXmlStreamReader &xml)
{
  Book *currentBook = 0;
  Chapter *currentChapter = 0;
  while (!xml.atEnd())
  {
    if (xml.readNextStartElement())
    {
      QString type = xml.name().toString();
      QString indicator = xml.attributes().value("n").toString();
      QString text;
      if(type == "b")
      {
        currentBook = add(indicator);
      }
      if(type == "c")
      {
        currentChapter = currentBook->add(indicator);
      }
      if(type == "v")
      {
        currentChapter->add(indicator)->setText(xml.readElementText());
      }
    }
  }
}

QString Bible::find(const QString &book, const QString &chapter, const QString &verse)
{
  QString text;
  Book *foundBook = data.value(book, &defaultBook);
  QList<Chapter*> chapters = foundBook->find(chapter);
  foreach(Chapter* foundChapter, chapters)
  {
    QList<Verse*> verses = foundChapter->find(verse);
    foreach(Verse* foundVerse, verses)
      text.append(foundVerse->data);
  }
  return text;
}

Bible::~Bible()
{

}

ISEEnd