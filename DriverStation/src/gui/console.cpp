#include "console.h"

Console::Console(){
	std::cout.rdbuf(cout.rdbuf());

	RectangleShape* back = new RectangleShape();
	back->setPosition(0.0f, 20.0f);
	back->setOutlineColor(Color::White);
	back->setOutlineThickness(1);
	addElem(back, ELEM_FUNC{
		RectangleShape* back = (RectangleShape*)ptr;
		Console* con = (Console*)par;
		Vector2f size = par->getSize();
		if(size != con->oldSize){
			con->oldSize = size;
			back->setSize(size - Vector2f(0.0f, 20.0f));
			con->rt.create((unsigned int)size.x, (unsigned int)size.y - 20);
			back->setTexture(&con->rt.getTexture(), true);
		}
		con->rt.clear(Color(12, 12, 12));
		con->rt.draw(con->conTxt);
		con->rt.display();
	});

	Text* labelText = new Text();
	labelText->setFont(appRes->arial);
	labelText->setCharacterSize(20);
	labelText->setFillColor(Color::White);
	labelText->setString("Console");
	labelText->setPosition(5.0f, -5.0f);
	addElem(labelText, NULL);

	conTxt.setFont(appRes->arial);
	conTxt.setCharacterSize(16);
	conTxt.setFillColor(Color::White);
	conTxt.setOrigin(-4.0f, -1.0f);
	//conTxt.setPosition(0.0f, -18.0f);

	txtIndex = -1;
}


void Console::scroll(Event::MouseWheelScrollEvent event){
	Vector2u size = rt.getSize();
	FloatRect bounds = conTxt.getLocalBounds();
	if(event.wheel == Mouse::Wheel::VerticalWheel){
		float maxHeight = size.y - bounds.height - 9.0f;
		if(maxHeight < 0.0f){
			conTxt.move(0.0f, event.delta*18.0f);
			Vector2f pos = conTxt.getPosition();
			if(event.delta > 0){
				if(pos.y > 0.0f)
					conTxt.setPosition(pos.x, 0.0f);
			} else {
				if(pos.y < maxHeight)
					conTxt.setPosition(pos.x, maxHeight);
			}
		}
	} else {
		float maxWidth = size.x - bounds.width - 9.0f;
		if(maxWidth < 0.0f){
			conTxt.move(event.delta*18.0f, 0.0f);
			Vector2f pos = conTxt.getPosition();
			if(event.delta > 0){
				if(pos.x > 0.0f)
					conTxt.setPosition(0.0f, pos.y);
			} else {
				if(pos.x < maxWidth)
					conTxt.setPosition(maxWidth, pos.y);
			}
		}
	}
}

void Console::print(const String &str){
	conTxt.setString(conTxt.getString() + str);
	// scroll to bottom
	Vector2u size = rt.getSize();
	FloatRect bounds = conTxt.getLocalBounds();
	float height = size.y - bounds.height - 9.0f;
	if(height < 0.0f)
		conTxt.setPosition(0.0f, height);
}

void Console::update(GElem* parent){
	GElem::update(parent);

	string out = cout.str();
	if(!out.empty()){
		print(out);
		cout.str("");
	}

	/*if(txtIndex >= 0){
		if(!Mouse::isButtonPressed(Mouse::Left)){

		}
	}else if(Mouse::isButtonPressed(Mouse::Left)){
		txtIndex = getTxtIndex(Mouse::getPosition());
	}*/
}

int Console::getTxtIndex(const Vector2i &pos){
	return 0;
}

void Console::toClipboard(const String &str){
	std::string s = str.toAnsiString();
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size()+1);
	if(!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}