#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string.h>
#include <sstream>
#include <iostream>
#include "gElem.h"
#include "appRes.h"
using namespace sf;

extern AppRes* appRes;

class Console: public GElem {
public:
	Console();
	void scroll(Event::MouseWheelScrollEvent event);
	void print(const String &str);
	void update(GElem* parent);

private:
	std::stringstream cout;
	RenderTexture rt;
	Text conTxt;
	Vector2f oldSize;

	int txtIndex;

	int getTxtIndex(const Vector2i &pos);
	void toClipboard(const String &str);
};
