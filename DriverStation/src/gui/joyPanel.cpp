#include "joyPanel.h"

JoyPanel::JoyPanel():
	index(0)
{
	Text* joyText = new Text();
	joyText->setFont(appRes->arial);
	joyText->setCharacterSize(20);
	joyText->setFillColor(Color::White);
	joyText->setString("Controller 0");
	addElem(joyText, ELEM_FUNC{
		Text* txt = (Text*)ptr;
		JoyPanel* ths = (JoyPanel*)par;
		txt->setPosition(0.0f, -5.0f);
		txt->setString("Controller "+std::to_string(ths->getIndex()));
	});

	Text* conText = new Text();
	conText->setFont(appRes->arial);
	conText->setCharacterSize(20);
	conText->setFillColor(Color::Red);
	conText->setString("Disconnected");
	addElem(conText, ELEM_FUNC{
		Text* txt = (Text*)ptr;
		JoyPanel* ths = (JoyPanel*)par;
		float padding = par->getPadding();
		bool connected = Joystick::isConnected(ths->getIndex());
		txt->setFillColor(connected? Color::Green: Color::Red);
		txt->setString(connected? "Connected": "Disconnected");
		float textX = par->getSize().x - 1 - padding - txt->getLocalBounds().width;
		txt->setPosition(textX, -5.0f);
	});

	RectangleShape* outline = new RectangleShape();
	outline->setFillColor(Color(24,24,24));
	outline->setOutlineColor(Color::White);
	outline->setOutlineThickness(1);
	addElem(outline, ELEM_FUNC{
		RectangleShape* rect = (RectangleShape*)ptr;
		float padding = par->getPadding();
		rect->setSize(par->getSize()-Vector2f(padding, 20.0f));
		rect->setPosition(0.0f, 20.0f);
	});

	// sticks
	Text* label = new Text();
	label->setFont(appRes->arial);
	label->setCharacterSize(16);
	label->setFillColor(Color::White);
	label->setString("Sticks");
	label->setPosition(5.0f, 22.0f);
	addElem(label, NULL);
	TextOut* txtOut = new TextOut();
	txtOut->setPosition(0.0f, 44.0f);
	txtOut->setLabel("Left X");
	txtOut->setJoyLoc(0, TextOut::CtlType::axis);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 66.0f);
	txtOut->setLabel("Left Y");
	txtOut->setJoyLoc(1, TextOut::CtlType::axis);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 88.0f);
	txtOut->setLabel("Left Click");
	txtOut->setJoyLoc(8, TextOut::CtlType::button);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 110.0f);
	txtOut->setLabel("Right X");
	txtOut->setJoyLoc(4, TextOut::CtlType::axis);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 132.0f);
	txtOut->setLabel("Right Y");
	txtOut->setJoyLoc(3, TextOut::CtlType::axis);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 154.0f);
	txtOut->setLabel("Right Click");
	txtOut->setJoyLoc(9, TextOut::CtlType::button);
	addElem(txtOut);

	// face buttons
	label = new Text();
	label->setFont(appRes->arial);
	label->setCharacterSize(16);
	label->setFillColor(Color::White);
	label->setString("Face Buttons");
	label->setPosition(5.0f, 180.0f);
	addElem(label, NULL);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 202.0f);
	txtOut->setLabel("A");
	txtOut->setJoyLoc(0, TextOut::CtlType::button);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 224.0f);
	txtOut->setLabel("B");
	txtOut->setJoyLoc(1, TextOut::CtlType::button);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 246.0f);
	txtOut->setLabel("X");
	txtOut->setJoyLoc(2, TextOut::CtlType::button);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 268.0f);
	txtOut->setLabel("Y");
	txtOut->setJoyLoc(3, TextOut::CtlType::button);
	addElem(txtOut);
	
	// d-pad
	label = new Text();
	label->setFont(appRes->arial);
	label->setCharacterSize(16);
	label->setFillColor(Color::White);
	label->setString("D-Pad");
	label->setPosition(5.0f, 294.0f);
	addElem(label, NULL);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 316.0f);
	txtOut->setLabel("Up");
	txtOut->setJoyLoc(0x07, TextOut::CtlType::pov);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 338.0f);
	txtOut->setLabel("Down");
	txtOut->setJoyLoc(0x17, TextOut::CtlType::pov);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 360.0f);
	txtOut->setLabel("Left");
	txtOut->setJoyLoc(0x16, TextOut::CtlType::pov);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 382.0f);
	txtOut->setLabel("Right");
	txtOut->setJoyLoc(0x06, TextOut::CtlType::pov);
	addElem(txtOut);
	
	// back buttons
	label = new Text();
	label->setFont(appRes->arial);
	label->setCharacterSize(16);
	label->setFillColor(Color::White);
	label->setString("Back Buttons");
	label->setPosition(5.0f, 408.0f);
	addElem(label, NULL);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 430.0f);
	txtOut->setLabel("Left Bumper");
	txtOut->setJoyLoc(4, TextOut::CtlType::button);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 452.0f);
	txtOut->setLabel("Right Bumper");
	txtOut->setJoyLoc(5, TextOut::CtlType::button);
	addElem(txtOut);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 474.0f);
	txtOut->setLabel("Triggers");
	txtOut->setJoyLoc(2, TextOut::CtlType::axis);
	addElem(txtOut);
	
	// control buttons
	label = new Text();
	label->setFont(appRes->arial);
	label->setCharacterSize(16);
	label->setFillColor(Color::White);
	label->setString("Control Buttons");
	label->setPosition(5.0f, 500.0f);
	addElem(label, NULL);
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 522.0f);
	txtOut->setLabel("Start");
	txtOut->setJoyLoc(7, TextOut::CtlType::button);
	addElem(txtOut);
	/* not available on windows
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 566.0f);
	txtOut->setLabel("Guide");
	txtOut->setJoyLoc(8, TextOut::CtlType::button);
	addElem(txtOut);*/
	txtOut = new TextOut();
	txtOut->setPosition(0.0f, 544.0f);
	txtOut->setLabel("Back");
	txtOut->setJoyLoc(6, TextOut::CtlType::button);
	addElem(txtOut);
	
}

void JoyPanel::setIndex(int i){
	index = i;
}

int JoyPanel::getIndex() const {
	return index;
}
