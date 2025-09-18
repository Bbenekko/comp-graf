#include <memory>
class Circle;
using CirclePtr = std::shared_ptr<Circle>; 

#ifndef Circle_H
#define Circle_H

#include "shape.h"

class Circle : public Shape {
  unsigned int m_vao;
protected:
  Circle ();
public:
  static CirclePtr Make ();
  virtual ~Circle ();
  virtual void Draw ();
};
#endif