#include <search.h>
#include "ListMenu.h"
#include "../Util/Debug.h"

ListMenu::ListMenu(ElementContainer* parent, String title) : LinearLayout(parent, VERTICAL), title(title){
	titleImage = new Image(this, 0, 0);
	scroller = new ScrollLayout(this);
	list = new LinearLayout(scroller, VERTICAL);

	scroller->setWHType(PARENT, FIXED);

	list->setWHType(PARENT, CHILDREN);
	list->setPadding(5).setGutter(5);

	children.push_back(titleImage);
	children.push_back(scroller);
	scroller->addChild(list);
}

ListMenu::~ListMenu(){
	delete titleImage;
	delete list;
	delete scroller;
}

void ListMenu::draw(){
	drawTitle();
	drawItems();
	LinearLayout::draw();
}

void ListMenu::drawTitle(){
	Sprite* sprite = titleImage->getSprite();

	sprite->clear(titleBgColor);
	sprite->fillTriangle(0, 8, 0, 15, 8, 15, TFT_BLACK);

	sprite->setCursor(10, 1);
	sprite->setTextFont(1);
	sprite->setTextSize(2);
	sprite->setTextColor(titleFgColor);
	sprite->print(title);
}

void ListMenu::drawItems(){
	for(uint i = 0; i < items.size(); i++){
		drawItem(i);
	}
}

void ListMenu::drawItem(uint index){
	const ListMenuItem& item = items[index];
	Sprite* image = item.image->getSprite();

	image->clear(index == selected ? selectedBgColor : itemBgColor);
	image->fillTriangle(0, 0, 0, 15, 6, 16, TFT_BLACK);
	image->fillTriangle(0, 0, 3, 0, 0, 5, TFT_BLACK);
	image->fillRect(6, 15, 1, 1, TFT_BLACK);

	image->setCursor(9, 1);
	image->setTextFont(0);
	image->setTextSize(2);
	image->setTextColor(titleFgColor);
	image->print(item.title);
}

void ListMenu::selectElement(uint element){
	uint oldSelected = selected;

	bool needsRedraw = setSelected(element);

	drawItem(oldSelected);
	drawItem(selected);

	drawTitle();

	if(needsRedraw){
		// TODO: clipping
		list->clear();
		list->draw();
	}

	items[oldSelected].image->draw();
	items[selected].image->draw();
	titleImage->draw();
}

bool ListMenu::setSelected(uint element){
	selected = element;

	return scroll();
}

void ListMenu::selectNext(){
	selectElement((selected+1) % items.size());
}

void ListMenu::selectPrev(){
	if(selected == 0){
		selectElement(items.size() - 1);
	}else{
		selectElement(selected - 1);
	}
}

uint ListMenu::getSelected() const{
	return selected;
}

ListMenuItem& ListMenu::getSelectedItem(){
	return items[selected];
}

bool ListMenu::scroll(){
	Element* listImage = items[selected].image;

	uint elStart = list->getPadding() + selected * (listImage->getHeight() + list->getGutter());
	uint elEnd = elStart + listImage->getHeight();

	uint scrollerStart = scroller->getScrollY();
	uint scrollerEnd = scrollerStart + scroller->getHeight();

	uint newScroll = scroller->getScrollY();
	logln("Element end / screen end: " + String(elEnd) + " / " + String(scrollerEnd));
	if(elStart < scrollerStart){
		newScroll = elStart;

		if(newScroll == list->getPadding()){
			newScroll = 0;
		}else{
			newScroll -= list->getGutter() / 2;
		}
	}else if(elEnd > scrollerEnd){
		newScroll += elEnd - scrollerEnd;

		logln("A / B: " + String(newScroll + scroller->getHeight()) + " / " + String(list->getHeight() - list->getPadding()));
		if(newScroll + scroller->getHeight() == list->getHeight() - list->getPadding()){
			newScroll += list->getPadding();
		}else{
			newScroll += list->getGutter() / 2;
		}
	}

	if(newScroll == scroller->getScrollY()){
		return false;
	}

	scroller->setScroll(0, newScroll);
	return true;
}

void ListMenu::addItem(const char* title){
	Image* image = new Image(list, list->getAvailableWidth(), 16);
	items.push_back({ title, image });

	list->addChild(image);
	image->setBorderColor(selectedBgColor);

	if(items.size() == 1){
		selected = 0;
	}

	drawItem(items.size()-1);
}

void ListMenu::reflow(){
	LinearLayout::reflow();

	titleImage->setSize(getAvailableWidth(), 16);
	titleImage->unpack(); // resize sprite

	scroller->setHeight(getAvailableHeight() - 16);
	scroller->reflow();

	list->reflow();
	for(const ListMenuItem& item : items){
		item.image->setSize(list->getAvailableWidth(), 16);
		item.image->unpack();
	}
	list->reflow();
}

void ListMenu::relocate(uint oldPos, uint newPos){
	items.relocate(oldPos, newPos);
	list->getChildren().relocate(oldPos, newPos);

	if(selected == oldPos || selected == newPos){
		setSelected(selected == oldPos ? newPos : oldPos);
	}
}

Color ListMenu::getSelectedColor() const{
	return selectedBgColor;
}

void ListMenu::setSelectedBgColor(Color selectedBgColor){
	ListMenu::selectedBgColor = selectedBgColor;

	for(Element* el : list->getChildren()){
		el->setBorderColor(selectedBgColor);
	}
}

void ListMenu::setItemColor(Color itemBgColor, Color itemFgColor){
	ListMenu::itemBgColor = itemBgColor;
	ListMenu::itemFgColor = itemFgColor;
}

void ListMenu::setTitleColor(Color titleBgColor, Color titleFgColor){
	ListMenu::titleBgColor = titleBgColor;
	ListMenu::titleFgColor = titleFgColor;
}

void ListMenu::clearItems(){
	int i = 0;
	for(Element* child : list->getChildren()){
		delete child;
		// TODO: use stdstring
		// delete items[i].title;
		i++;
	}

	list->getChildren().clear();
	items.clear();
	selected = 0;
}
