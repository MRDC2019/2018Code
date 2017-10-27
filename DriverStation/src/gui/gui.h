#pragma once

#include <SFML/Graphics.hpp>
#include "gElem.h"
#include "joyPanel.h"
#include "console.h"
using namespace sf;

class GUI: public GElem {
public:
	GUI();
	
	void update(const RenderWindow& window);

private:
	using GElem::update;
};
