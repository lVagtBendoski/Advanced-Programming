//
// Created by bobjo on 11/14/2024.
//

#ifndef ARROW_H
#define ARROW_H

#include <memory>

#include "rect.h"
#include "triangle.h"

class Arrow {
private:
    std::unique_ptr<Shape> rect;
    std::unique_ptr<Shape> triangle;
public:
    enum direction { left, right, up, down };
    Arrow(Rect const& rect, Triangle const& triangle, direction dir);
    Arrow(Shader & shader, vec2 pos, vec2 size, struct color color, direction dir);
    ~Arrow( );
    direction dir;

    void draw() const;
    void setUniforms() const;
    float getLeft() const;
    float getRight() const;
    float getTop() const;
    float getBottom() const;
    bool isOverlapping(vec2 const& point) const;
};



#endif //ARROW_H
