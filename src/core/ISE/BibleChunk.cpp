// Project
#include "BibleChunk.h"
#include "qdebug.h"
ISEBegin
QList<BibleChunk*> BibleChunk::chunks;

	BibleChunk::BibleChunk()
  :QGraphicsTextItem()
{
	chunks.append(this);
	setFlag(QGraphicsItem::ItemIsMovable);
	setTextWidth(100);
}

void BibleChunk::load(Verse *verse)
{
	verses.append(verse);
	setPlainText(toPlainText()+verse->data);
}

void BibleChunk::generatePieces()
{
	QString output;
	int id = 0;
	foreach(Verse* verse, verses)
	{ 
		id++;
		QString temp = verse->data;
		QStringList words = temp.split(" ");
		int size = words.count();
		int chosenIndex = qrand() %size;
		QString replacement = "____";
		QString replaced = words.at(chosenIndex);
		//QString replacement = words.at(chosenIndex);
		//replacement.replace(QRegExp("[^a-zA-Z]"),"_");
		words.replace(chosenIndex, replacement);
		output.append(words.join(" "));
		Slot *slot = new Slot(id, words.join(" "));
		Piece *piece = new Piece(id,replaced,slot);
		pieces.append(piece);
		holders.append(slot);
	}
	setPlainText(output);
}



BibleChunk::~BibleChunk()
{

}

ISEEnd