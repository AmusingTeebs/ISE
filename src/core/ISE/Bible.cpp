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
        currentBook = add(indicator);
      if(type == "c")
        currentChapter = currentBook->add(indicator);
      if(type == "v")
        currentChapter->add(indicator)->setText(xml.readElementText());
    }
  }
}

QString Bible::findText(const QString &book, const QString &chapter, const QString &verse)
{
  QString text;
  Book *foundBook = data.value(book, &defaultBook);
  QList<StructureType*> chapters = foundBook->find(chapter);
  foreach(StructureType* foundChapter, chapters)
  {
    QList<StructureType*> verses = foundChapter->find(verse);
    foreach(StructureType* foundVerse, verses)
	{
	  Verse *v =static_cast<Verse*>(foundVerse);
	  text.append(v->number + " " );
      text.append(v->data);
	}
  }
  return text;
}
QList<Verse*> Bible::findVerses(const QString &book, const QString &chapter, const QString &verse)
{
  QList<Verse*> foundVerses;
  Book *foundBook = data.value(book, &defaultBook);
  QList<StructureType*> chapters = foundBook->find(chapter);
  foreach(StructureType* foundChapter, chapters)
  {
    QList<StructureType*> verses = foundChapter->find(verse);
    foreach(StructureType* foundVerse, verses)
	  foundVerses.append(static_cast<Verse*>(foundVerse));
  }
  return foundVerses;
}

QList<StructureType*> StructureType::find(const QString &range) 
{
  if(range.isEmpty())
    return data.values();
  QList<StructureType*> chapters;

  //Setup
  QStringList values = range.split("-");
  int first = values.first().toInt();
  int last = values.last().toInt();

  //Loop
  do
  {
    StructureType *chapter = data.value(QString::number(first));
    if(chapter)
      chapters.append(chapter);
    first++;
  }
  while(first <= last);

  return chapters;
};

ISEEnd