#ifndef CIRCUITOS_LISTMENU_H
#define CIRCUITOS_LISTMENU_H


#include "../UI/LinearLayout.h"
#include "../UI/ScrollLayout.h"
#include "../UI/Image.h"

class ListMenu : public LinearLayout {
public:
	ListMenu(ElementContainer* parent, String title);
	virtual ~ListMenu();

	void reflow() override;

	void addItem(String title);

	/**
	 * Relocate a menu item. See Vector::relocate
	 * @see Vector::relocate
	 * @param oldPos
	 */
	void relocate(uint oldPos, uint newPos);

	/**
	 * Selects an element in the menu. Clears and redraws parent.
	 * @param element
	 */
	void selectElement(uint element);
	void selectNext();
	void selectPrev();

	/**
	 * Sets the selected element. Does not perform any drawing.
	 * @param element
	 * @return True if a redraw is needed due to scrolling.
	 */
	bool setSelected(uint element);
	uint getSelected() const;

	Color getSelectedColor() const;
	void setSelectedBgColor(Color selectedBgColor);
	void setItemColor(Color titleBgColor, Color titleFgColor);
	void setTitleColor(Color titleBgColor, Color titleFgColor);

	void draw() override;

private:
	struct ListMenuItem {
		String title;
		Image* image;
	};

	Image* titleImage;
	ScrollLayout* scroller;
	LinearLayout* list;

	Vector<ListMenuItem> items;
	Color selectedBgColor = TFT_LIGHTGREY;
	Color itemBgColor = TFT_DARKGREY;
	Color itemFgColor = TFT_BLACK;
	Color titleBgColor = TFT_DARKGREEN;
	Color titleFgColor = TFT_BLACK;

	String title = "";

	uint selected = 0;
	bool scroll();
	void drawTitle();
	void drawItems();
	void drawItem(uint index);

};


#endif //CIRCUITOS_LISTMENU_H
