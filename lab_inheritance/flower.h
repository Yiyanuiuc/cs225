/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 */

#ifndef FLOWER_H_
#define FLOWER_H_

#include "shape.h"
// modified: include
#include "rectangle.h"
#include "circle.h"
#include "triangle.h"

class Flower : public Drawable
{
  private:
  	// modified: pointer
    Rectangle* stem;
    Circle* pistil; // center piece of flower
    Triangle* leaf;

    void drawPetals(PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);

    // modified: add virtual
    virtual void draw(PNG* canvas) const;

    // modified: destructor
    virtual ~Flower();
};

#endif // FLOWER_H_
