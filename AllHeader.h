#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>

using namespace std;
using namespace sf;

inline float lenght(Vector2f vec)
{
	return sqrtf(pow(vec.x, 2) + pow(vec.y, 2));
}

inline Vector2f nomalize(Vector2f vec)
{
	float len = lenght(vec);
	if (len != 0)
		return vec / len;
	return vec;
}

inline int randint(int start, int stop)
{
	return rand() % (stop - start + 1) + start;
}

extern float multiplier;