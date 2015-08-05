#pragma once

#include "ISEExports.h"
#include "qtextedit.h"
#include <QXmlStreamReader>

ISEBegin
class BibleChunk : public QTextEdit
{

	Q_OBJECT

public:
  /** Constructor */
  BibleChunk();
  
  void load(const QString &value);

  /** Deconstructor */
  ~BibleChunk();

};
ISEEnd