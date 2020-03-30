#ifndef CIRCUITOS_GRIDMENU_H
#define CIRCUITOS_GRIDMENU_H


#include "../UI/Layout.h"
#include "../UI/Image.h"
#include "../UI/GridLayout.h"
#include "../UI/LinearLayout.h"
#include "../UI/ScrollLayout.h"
#include "../Util/Vector.h"

struct GridMenuItem {
	String title;
	Element* icon;
};

class GridMenu : public LinearLayout {
public:
	GridMenu(ElementContainer* parent, uint cols);
	virtual ~GridMenu();

	void reflow() override;

	void addItem(const GridMenuItem& item);

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

	void setSelectedColor(Color selectedColor);

	void draw() override;

	void setTitleColor(Color titleBgColor, Color titleFgColor);

private:
	Image* title;
	ScrollLayout* scroller;
	GridLayout* grid;

	Vector<GridMenuItem> items;
	Color selectedColor = TFT_RED;
	Color titleBgColor = TFT_DARKGREEN;
	Color titleFgColor = TFT_BLACK;

	uint selected = 0;
	bool scroll();
	void drawTitle();

};


#endif //CIRCUITOS_GRIDMENU_H
