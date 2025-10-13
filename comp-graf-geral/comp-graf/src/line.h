#include <memory>
class Line;
using LinePtr = std::shared_ptr<Line>; 

#ifndef LINE_H
#define LINE_H

#include "shape.h"

class Line : public Shape {
  unsigned int m_vao;
protected:
  Line ();
public:
  static LinePtr Make ();
  virtual ~Line ();
  virtual void Draw (StatePtr st);
};
#endif