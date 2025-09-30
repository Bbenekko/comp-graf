#include <memory>
class Circle;
using CirclePtr = std::shared_ptr<Circle>; 

#ifndef Circle_H
#define Circle_H

#include "shape.h"

class Circle : public Shape {
  unsigned int m_vao;
  int nSegments;
protected:
  Circle (float thickness, float radius, int segments);
public:
  static CirclePtr Make (float thickness, float radius = 1.0f, int segments = 100);
  virtual ~Circle ();
  virtual void Draw (StatePtr st);
};
#endif