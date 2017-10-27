#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "gElem.h"
#include "joyPanel.h"
#include "appRes.h"
using namespace sf;

extern AppRes* appRes;

class TextOut: public GElem {
public:
	TextOut();

	void setLabel(String s);
	enum CtlType{button, axis, pov};
	void setJoyLoc(int loc, CtlType tp);

	void update(GElem* parent);
private:
	String label;
	int joyLoc;
	CtlType type;
	String output;
};
