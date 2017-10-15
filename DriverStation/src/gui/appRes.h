#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

struct AppRes {
	AppRes(){
		if(!arial.loadFromFile("arial.ttf"))
			arial.loadFromFile("../../res/arial.ttf");
		if (!icon.loadFromFile("icon.png"))
			icon.loadFromFile("../../res/icon.png");
	};

	Font arial;
	Image icon;
};