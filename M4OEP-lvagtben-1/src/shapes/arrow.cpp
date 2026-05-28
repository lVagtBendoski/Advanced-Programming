//
// Created by bobjo on 11/14/2024.
//

#include "Arrow.h"
using namespace std;
Arrow::Arrow(Shader &shader, vec2 pos, vec2 size, struct color color, direction dir){
    this->rect = make_unique<Rect>(shader, pos, size, color);
    this->dir = dir;
    if(dir == up) {pos.y += size.y;}
    else if(dir == right) {pos.x += size.x;}
    else if(dir == down) {pos.y -= size.y; size.y = -1 * size.y;}
    else if(dir == left) {pos.x -= size.x;}

    this->triangle = make_unique<Triangle> (shader, pos, size, color);
}
Arrow::Arrow(Rect const &otherRect, Triangle const &otherTriangle, direction dir) {
    this->rect = make_unique<Rect>(otherRect);
    this->triangle = make_unique<Triangle>(otherTriangle);
}
Arrow::~Arrow() {
    this->triangle = nullptr;
    this->rect = nullptr;
}
void Arrow::draw() const {
    //this->rect->draw();
    this->triangle->draw();
}
void Arrow::setUniforms() const {
    this->triangle->setUniforms();
     this->rect->setUniforms();
    if(dir == up) {triangle->setPosY(rect->getPosY() + rect->getSize().y/2);}
    else if(dir == right) {triangle->setPosX(rect->getPosX() + rect->getSize().x/2);}
    else if(dir == down) {triangle->setPosY(rect->getPosY() - rect->getSize().y/2);}
    else if(dir == left) {triangle->setPosY(rect->getPosX() - rect->getSize().x/2);}
}



