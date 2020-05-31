#include "GridMenu.h"
#include "../Util/Debug.h"

GridMenu::GridMenu(ElementContainer* parent, uint cols) : LinearLayout(parent, VERTICAL){
	title = new Image(this, 0, 0);
	scroller = new ScrollLayout(this);
	grid = new GridLayout(scroller, cols);

	scroller->setWHType(PARENT, FIXED);

	grid->setWHType(PARENT, CHILDREN);
	grid->setPadding(10).setGutter(10);

	children.push_back(title);
	children.push_back(scroller);
	scroller->addChild(grid);
}

GridMenu::~GridMenu(){
	delete title;
	delete grid;
	delete scroller;
}

void GridMenu::draw(){
	drawTitle();
	LinearLayout::draw();
}

void GridMenu::drawTitle(){
	Sprite* sprite = title->getSprite();

	sprite->clear(titleBgColor);
	sprite->fillTriangle(0, 8, 0, 15, 8, 15, titleFgColor);

	if(items.empty()) return;

	sprite->setCursor(10, 1);
	sprite->setTextFont(1);
	sprite->setTextSize(2);
	sprite->setTextColor(titleFgColor);
	sprite->print(items[selected].title);
}

void GridMenu::selectElement(uint element){
	uint oldSelected = selected;

	bool needsRedraw = setSelected(element);

	items[oldSelected].icon->draw();
	items[element].icon->draw();

	drawTitle();

	if(needsRedraw){
		// TODO: clipping
		grid->clear();
		grid->draw();
	}

	title->draw();
}

bool GridMenu::setSelected(uint element){
	items[selected].icon->setBorderWidth(0);
	items[element].icon->setBorderWidth(3);

	selected = element;

	return scroll();
}

void GridMenu::selectNext(){
	selectElement((selected+1) % items.size());
}

void GridMenu::selectPrev(){
	if(selected == 0){
		selectElement(items.size() - 1);
	}else{
		selectElement(selected - 1);
	}
}

uint GridMenu::getSelected() const{
	return selected;
}

GridMenuItem& GridMenu::getSelectedItem(){
	return items[selected];
}

bool GridMenu::scroll(){
	Element* gridImage = items[selected].icon;

	uint elStart = grid->getPadding() + (selected/2) * (gridImage->getHeight() + grid->getGutter());
	uint elEnd = elStart + gridImage->getHeight();

	uint scrollerStart = scroller->getScrollY();
	uint scrollerEnd = scrollerStart + scroller->getHeight();

	uint newScroll = scroller->getScrollY();
	logln("Element end / screen end: " + String(elEnd) + " / " + String(scrollerEnd));
	if(elStart < scrollerStart){
		newScroll = elStart;

		if(newScroll == grid->getPadding()){
			newScroll = 0;
		}else{
			newScroll -= grid->getGutter() / 2;
		}
	}else if(elEnd > scrollerEnd){
		newScroll += elEnd - scrollerEnd;

		logln("A / B: " + String(newScroll + scroller->getHeight()) + " / " + String(grid->getHeight() - grid->getPadding()));
		if(newScroll + scroller->getHeight() == grid->getHeight() - grid->getPadding()){
			newScroll += grid->getPadding();
		}else{
			newScroll += grid->getGutter() / 2;
		}
	}

	if(newScroll == scroller->getScrollY()){
		return false;
	}

	scroller->setScroll(0, newScroll);
	return true;
}

void GridMenu::addItem(const GridMenuItem& item){
	items.push_back(item);
	grid->addChild(item.icon);
	item.icon->setParent(grid);
	item.icon->setBorderColor(selectedColor);

	if(items.size() == 1){
		item.icon->setBorderWidth(3);
	}
}

void GridMenu::reflow(){
	LinearLayout::reflow();

	title->setSize(getAvailableWidth(), 16);
	title->unpack(); // resize sprite

	scroller->setHeight(getAvailableHeight() - 16);
	scroller->reflow();

	grid->reflow();
}

void GridMenu::relocate(uint oldPos, uint newPos){
	items.relocate(oldPos, newPos);
	grid->getChildren().relocate(oldPos, newPos);

	if(selected == oldPos || selected == newPos){
		items[oldPos].icon->setBorderWidth(0);
		items[newPos].icon->setBorderWidth(0);
		setSelected(selected == oldPos ? newPos : oldPos);
	}
}

Color GridMenu::getSelectedColor() const{
	return selectedColor;
}

void GridMenu::setSelectedColor(Color selectedColor){
	GridMenu::selectedColor = selectedColor;

	for(Element* el : grid->getChildren()){
		el->setBorderColor(selectedColor);
	}
}

void GridMenu::setTitleColor(Color titleBgColor, Color titleFgColor){
	GridMenu::titleBgColor = titleBgColor;
	GridMenu::titleFgColor = titleFgColor;
}
