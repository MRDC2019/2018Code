#include "gElem.h"

void GElem::update(GElem* parent){
	(void)parent;
	Vector2f sp = size - Vector2f(2*padding, 2*padding);
	for(vector<GElemPtr>::iterator it=children.begin(); it != children.end(); ++it){
		const GElemPtr& ptr = *it;
		if(ptr.isGElem && ptr.gElem->canUseParLoc()){
			FloatRect loc = ptr.gElem->getParLoc();
			Vector2f pos = Vector2f(loc.left*sp.x+padding, loc.top*sp.y+padding);
			Vector2f size = Vector2f(loc.width*sp.x, loc.height*sp.y);
			ptr.gElem->setPosition(pos);
			ptr.gElem->setSize(size);
		}
		if(ptr.update)
			ptr.update(ptr.sfElem, this);
		if(ptr.isGElem)
			ptr.gElem->update(this);
	}
}

void GElem::draw(RenderTarget& target, RenderStates states) const{
	states.transform *= getTransform();
	for(vector<GElemPtr>::const_iterator it=children.begin(); it != children.end(); ++it){
		const GElemPtr& ptr = *it;
		target.draw(*ptr.sfElem, states);
	}
}

GElem::~GElem(){
	for(vector<GElemPtr>::iterator it=children.begin(); it != children.end(); ++it){
		const GElemPtr& ptr = *it;
		if(ptr.isGElem){
			delete ptr.gElem;
		}else{
			delete ptr.sfElem;
		}
	}
}
