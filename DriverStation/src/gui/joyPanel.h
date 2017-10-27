#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "gElem.h"
#include "textOut.h"
#include "appRes.h"
using namespace sf;

extern AppRes* appRes;

class JoyPanel: public GElem {
public:
	JoyPanel();

	void setIndex(int i);
	int getIndex() const;

private:
	int index;
};
