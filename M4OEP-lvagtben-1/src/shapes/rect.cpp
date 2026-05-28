 #include "rect.h"
#include "../util/color.h"

Rect::Rect(Shader & shader, vec2 pos, vec2 size, struct color color)
        : Shape(shader, pos, size, color) {
    initVectors();
    initVAO();
    initVBO();
    initEBO();
}
Rect::Rect(Shader & shader, vec2 pos, vec2 size, double angle, struct color color)
        : Shape(shader, pos, size, color) {
    initVectors(angle);
    initVAO();
    initVBO();
    initEBO();
}

Rect::Rect(Rect const& other) : Shape(other) {
    initVectors();
    initVAO();
    initVBO();
    initEBO();
}

Rect::~Rect() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Rect::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Rect::initVectors() {
    this->vertices.insert(vertices.end(), {
            // TODO: Add other three corners here
            0.5f, -0.5f, // x, y of bottom right corner
           -0.5f, -0.5f,
            0.5f,  0.5f,
           -0.5f,  0.5f
    });

    this->indices.insert(indices.end(), {
            0, 1, 2, // First triangle
            1, 2, 3  // Second triangle
    });
}

//TODO: fix this. Right now as angle increases, everything just stretches out into a line
void Rect::initVectors(double angle) {
    angle = angle * M_PI / 180;
    vec2 midpoint1((0.5f*sin(angle)),(0.5f*cos(angle)));
    vec2 midpoint2(-(0.5f*sin(angle)),-(0.5f*cos(angle)));
    this->vertices.insert(vertices.end(), {
            // TODO: Add other three corners here
            midpoint2.x + cos(angle)*0.5f, midpoint2.y - sin(angle)*0.5f, // x, y of bottom right corner
            midpoint2.x - cos(angle)*0.5f, midpoint2.y - sin(angle)*0.5f,
            midpoint1.x + cos(angle)*0.5f, midpoint1.y + sin(angle)*0.5f,
            midpoint1.x - cos(angle)*0.5f, midpoint1.y + sin(angle)*0.5f
    });

    this->indices.insert(indices.end(), {
            0, 1, 2, // First triangle
            1, 2, 3,  // Second triangle
    });
}
// Overridden Getters from Shape
float Rect::getLeft() const        { return pos.x - (size.x / 2); }
float Rect::getRight() const       { return pos.x + (size.x / 2); }
float Rect::getTop() const         { return pos.y + (size.y / 2); }
float Rect::getBottom() const      { return pos.y - (size.y / 2); }
