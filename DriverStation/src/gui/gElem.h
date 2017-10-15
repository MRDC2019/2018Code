#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

#define ELEM_FUNC [](void* ptr, GElem* par)

class GElem;

struct GElemPtr{
	GElemPtr(GElem* elem, void(*up)(void*, GElem*)=NULL):
		isGElem(true), gElem(elem), update(up){}
	GElemPtr(Drawable* elem, void(*up)(void*, GElem*)):
		isGElem(false), sfElem(elem), update(up){}

	bool isGElem;
	union{
		GElem* gElem;
		Drawable* sfElem;
	};
	void (*update)(void*, GElem*);
};

class GElem: public Drawable, public Transformable {
public:
	GElem(): useParLoc(false), padding(10.0f) {}
	~GElem();

	void setParLoc(FloatRect _parLoc) {parLoc=_parLoc; useParLoc=true;}
	FloatRect getParLoc() const {return parLoc;}
	bool canUseParLoc() const {return useParLoc;}
	void setSize(Vector2f _size) {size=_size;}
	Vector2f getSize() const {return size;}
	void setPadding(float _padding) {padding=_padding;}
	float getPadding() const {return padding;}

	void addElem(GElem* elem, void(*up)(void*, GElem*)=NULL) { children.push_back(GElemPtr(elem, up)); }
	void addElem(Drawable* elem, void(*up)(void*, GElem*)) { children.push_back(GElemPtr(elem, up)); }

	virtual void update(GElem* parent);
private:
	virtual void draw(RenderTarget& target, RenderStates states) const;

	FloatRect parLoc;
	bool useParLoc;
	Vector2f size;
	float padding;
	vector<GElemPtr> children;
};
