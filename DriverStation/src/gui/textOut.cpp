#include "textOut.h"

TextOut::TextOut(){
	RectangleShape* labelBack = new RectangleShape();
	labelBack->setFillColor(Color(12,12,12));
	addElem(labelBack, ELEM_FUNC{
		RectangleShape* back = (RectangleShape*)ptr;
		Vector2f size = par->getSize();
		float padding = par->getPadding();
		Vector2f backSize = Vector2f((size.x-5*padding)/2, size.y-padding);
		back->setSize(backSize);
		back->setPosition(2*padding, 0.0f);
	});

	RectangleShape* outBack = new RectangleShape();
	outBack->setFillColor(Color(12,12,12));
	addElem(outBack, ELEM_FUNC{
		RectangleShape* back = (RectangleShape*)ptr;
		Vector2f size = par->getSize();
		float padding = par->getPadding();
		Vector2f backSize = Vector2f((size.x-5*padding)/2, size.y-padding);
		back->setSize(backSize);
		back->setPosition((size.x+padding)/2, 0.0f);
	});

	Text* labelText = new Text();
	labelText->setFont(appRes->arial);
	labelText->setCharacterSize(16);
	labelText->setFillColor(Color::White);
	addElem(labelText, ELEM_FUNC{
		Text* txt = (Text*)ptr;
		float padding = par->getPadding();
		txt->setPosition(2*padding+5, 0.0f);
		txt->setString(((TextOut*)par)->label);
	});

	Text* outText = new Text();
	outText->setFont(appRes->arial);
	outText->setCharacterSize(16);
	outText->setFillColor(Color::White);
	addElem(outText, ELEM_FUNC{
		Text* txt = (Text*)ptr;
		Vector2f size = par->getSize();
		float padding = par->getPadding();
		txt->setPosition((size.x+padding)/2+5, 0.0f);
		txt->setString(((TextOut*)par)->output);
	});

	setPadding(2.0);
}

void TextOut::update(GElem* parent){
	float parPad = parent->getPadding();
	Vector2f parSize = parent->getSize();
	int index = ((JoyPanel*)parent)->getIndex();
	setSize(Vector2f(parSize.x-parPad, 22.0f));
	switch(type){
	case button:
		output = std::to_string(Joystick::isButtonPressed(index, joyLoc));
		break;
	case axis:
		output = std::to_string(Joystick::getAxisPosition(index, (Joystick::Axis)joyLoc));
		break;
	case pov:
		float axis = Joystick::getAxisPosition(index, (Joystick::Axis)(joyLoc&0xf));
		output = std::to_string((joyLoc>>4)? (axis<-0.1f): (axis>0.1f));
		break;
	};

	GElem::update(parent);
}

void TextOut::setLabel(String s){
	label = s;
}

void TextOut::setJoyLoc(int loc, CtlType tp){
	joyLoc = loc;
	type = tp;
}
