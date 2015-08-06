// Project
#include "BibleChunk.h"
ISEBegin
	BibleChunk::BibleChunk()
  :QTextEdit()
{

}

void BibleChunk::load(const QString &value)
{
  setPlainText(value);
}

BibleChunk::~BibleChunk()
{

}

ISEEnd