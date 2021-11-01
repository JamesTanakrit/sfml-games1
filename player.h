#pragma once
#include"AllHeader.h"
class Player
{
private:
	RectangleShape shape;
	Vector2f direction;
	float speed;

public:
	//constructor
	inline Player()
	{
		shape.setSize(Vector2f(40.f, 40.f));
		shape.setPosition(Vector2f(300.f, 300.f));
		speed = 150;
	}

	inline void update(float deltaTime)
	{
		direction = Vector2f(0.f, 0.f);
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			direction.y -= 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			direction.x -= 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			direction.y += 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			direction.x += 1;
		}
		shape.move(nomalize(direction) * speed * deltaTime);
	}

	inline void render(RenderWindow& window)
	{
		window.draw(shape);
	}

	inline FloatRect getGlobalBounds()
	{
		return shape.getGlobalBounds();
	}

	inline Vector2f getPosition()
	{
		return shape.getPosition();
	}

	inline Vector2f getSize()
	{
		return shape.getSize();
	}
};