#include "gui.h"

GUI::GUI(){
	JoyPanel* joyPan0 = new JoyPanel();
	joyPan0->setParLoc(FloatRect(0.0f, 0.0f, 0.5f, 1.0f));
	joyPan0->setIndex(0);
	addElem(joyPan0);

	JoyPanel* joyPan1 = new JoyPanel();
	joyPan1->setParLoc(FloatRect(0.5f, 0.0f, 0.5f, 1.0f));
	joyPan1->setIndex(1);
	addElem(joyPan1);
}

void GUI::update(const RenderWindow& window){
	setSize((Vector2f)window.getSize());
	update(NULL);
}
