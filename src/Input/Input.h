#ifndef CIRCUITOS_INPUT_H
#define CIRCUITOS_INPUT_H

#include "../Loop/LoopListener.h"
#include "../Util/Vector.h"
#include "InputListener.h"
#include <unordered_set>

#define PIN_MAX 45
#define DEBOUNCE_COUNT 1

class Input : public LoopListener {
public:
	Input(uint8_t _pinNumber);

	/**
	 * Sets a callback to be executed when a button press is detected.
	 * @param pin Input pin of the button.
	 * @param callback Callback to be executed.
	 */
	virtual void setBtnPressCallback(uint8_t pin, void (* callback)());

	/**
	 * Sets a callback to be executed when a button is released.
	 * @param pin Input pin of the button.
	 * @param callback Callback to be executed.
	 */
	virtual void setBtnReleaseCallback(uint8_t pin, void (* callback)());

	virtual void removeBtnPressCallback(uint8_t pin);
	virtual void removeBtnReleaseCallback(uint8_t pin);

	/**
	 * Sets a callback to be executed when a button is held for a certain ammount of time.
	 * The callback will be executed only once in a single button hold.
	 * @param pin Input pin of the button.
	 * @param holdTime Ammount of time after which the callback is executed.
	 * @param callback Callback to be executed.
	 */
	virtual void setButtonHeldCallback(uint8_t pin, uint32_t holdTime, void (* callback)());

	/**
	 * Sets a callback to be executed when a button is held for a certain ammount of time, periodically.
	 * The callback will be executed periodically, every time the specified ammount of time expires.
	 * For example, if periodTime is set to 100 and the button is held, the callback will be called at 100ms, 200ms and so on.
	 * @param pin Input pin of the button.
	 * @param periodTime Ammount of time the callback will be executed periodically.
	 * @param callback Callback to be executed. The callback also receives an uint parameter with the number of repetitions.
	 * The first time it's called, (uint)1 will be passed, the 2nd time (uint)2 and so on.
	 */
	virtual void setButtonHeldRepeatCallback(uint8_t pin, uint32_t periodTime, void (* callback)(uint));

	/**
	 * Returns the time in milliseconds a button is being held down.
	 * @param pin Input pin of the button.
	 * @return Ammount of time the button was held down.
	 */
	virtual uint32_t getButtonHeldMillis(uint8_t pin);

	/**
	 * Sets a callback to be executed when any button is pressed or released. 
	 * @param callback Callback to be executed.
	 * @param returnAfterCallback Optional parameter. If true, ignores button input after anyKeyCallback is executed.
	 * Useful to prevent button inputs after waking up from sleep, for example.
	 */
	virtual void setAnyKeyCallback(void(* callback)(), bool returnAfterCallback = false);

	/**
	 * Pre-register buttons. Buttons are automatically registered with callback functions, but pre-registration is nedded for anyKeyCallback.
	 * @param pins
	 */
	virtual void preregisterButtons(Vector<uint8_t> pins);

	static Input* getInstance();

	void loop(uint _time) override;

	void addListener(InputListener* listener);

	void removeListener(InputListener* listener);

protected:
	uint8_t pinNumber = 0;

	std::vector<void (*)()> btnPressCallback;
	std::vector<void (*)()> btnReleaseCallback;
	std::vector<void (*)()> btnHoldCallback;
	std::vector<void (*)(uint)> btnHoldRepeatCallback;

	static Input* instance;
	virtual void scanButtons() = 0;

	virtual void registerButton(uint8_t pin);

	Vector<uint8_t> buttons;
	std::vector<uint8_t> btnCount; // Read count per button
	std::vector<uint8_t> btnState; // Button state, 0 - released, 1 - pressed
	std::vector<uint32_t> btnHoldStart; //Counter in ms when a button is held
	std::vector<uint32_t> btnHoldValue; //Value in ms that the callback will be triggered after
	std::vector<uint32_t> btnHoldRepeatValue; //Value in ms that the callback will be triggered after periodically
	std::vector<uint32_t> btnHoldRepeatCounter;
	std::vector<bool> btnHoldOver;

	void (* anyKeyCallback)(void);

	bool anyKeyCallbackReturn;

	void btnPress(uint i);

	void btnRelease(uint);

	Vector<InputListener*> listeners;
	static std::unordered_set<InputListener*> removedListeners;
};


#endif //CIRCUITOS_INPUT_H
