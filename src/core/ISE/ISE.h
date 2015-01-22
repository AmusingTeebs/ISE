#pragma once

#include "ISEExports.h"
#include "qapplication.h"
#include "qobject.h"

ISEBegin
class ISEAPI ISE
{
public:
  /** Constructor */
  ISE();
  
  /** Deconstructor */
  ~ISE();

  /** Initialize ISE! */
  void initialize(QApplication *application);
};
ISEEnd