#pragma once
#include <glm/glm.hpp>

class Circle
{
public:
	Circle(const glm::vec2& position,float radius) : Position(position), Radius(radius) {};
	~Circle() {};

public:
	glm::vec2 Position;
	float     Radius;
};

class Rectangle
{
public:
	Rectangle(const glm::vec2& position, const glm::vec2& size) : Position(position), Size(size){};
	~Rectangle() {};

public:
	glm::vec2 Position;
	glm::vec2 Size;
};