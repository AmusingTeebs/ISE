#pragma once

#include "ISEExports.h"
#include "qtextedit.h"
#include <QXmlStreamReader>
#include "qlabel.h"
#include "qgraphicsitem.h"
#include "Bible.h"
ISEBegin

class Slot : public QGraphicsTextItem
{
public:
	Slot(int _id, const QString &_data) 
	{ id = _id; data = _data; setPlainText(_data); }
	int id;
	QString data;
};
class Piece : public QGraphicsTextItem
{
public:
	Piece(int _id, const QString &_data, Slot *_slot) 
	{ id = _id; data = _data; slot = _slot; setPlainText(_data); }
	Slot *slot;
	int id;
	QString data;
};

class BibleChunk : public QGraphicsTextItem
{

	Q_OBJECT

public:
	/** Constructor */
	BibleChunk();

	void load(Verse *verse);

	void generatePieces();

	/** Deconstructor */
	~BibleChunk();

	static QList<BibleChunk*> chunks;

	QList<Slot*> holders;
	QList<Piece*> pieces;
	QList<Verse*> verses;
	QString data;
};
ISEEnd