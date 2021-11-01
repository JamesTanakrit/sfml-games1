#pragma once
#include"AllHeader.h"

class Item
{
private:
	RectangleShape shape;
	
public:
	int tag;

	inline Item(Vector2f position, Vector2f size, int tag = 0, Texture* texture = nullptr)
	{
		shape.setPosition(position);
		shape.setSize(size);
		shape.setTexture(texture);
		this->tag = tag;
	}
	
	inline bool isPickedUp(FloatRect bound)
	{
		return shape.getGlobalBounds().intersects(bound);
	}

	inline void render(RenderWindow& window)
	{
		window.draw(shape);
	}


};

