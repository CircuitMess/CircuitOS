#ifndef CIRCUITOS_VECTOR_H
#define CIRCUITOS_VECTOR_H

#include <Arduino.h>
#include <vector>

template<typename T>
class Vector : public std::vector<T> {
public:

	/**
	 * Change the position of of an element. All elements after the new position, including the element that was
	 * formerly at that position, will be moved one position to the right.
	 * @param oldPos Index of the element to be moved.
	 * @param newPos Index of the position where the element should be moved.
	 */
	void relocate(uint oldPos, uint newPos);

	/**
	 * Swap the position of two elements.
	 * @param posA First element.
	 * @param posB Second element.
	 */
	void swap(uint posA, uint posB);

	/**
	 * Remove an element from the array.
	 * @param element Index of the element to be removed.
	 */
	void remove(uint i);

	/**
	 * Find the index of an element.
	 * @param element The element.
	 * @return Index of the element. -1 (uint max) if element isn't in the array.
	 */
	uint indexOf(T element);

};

template<typename T>
void Vector<T>::relocate(uint oldPos, uint newPos){
	if(oldPos == newPos) return;

	T tmp;
	memmove(&tmp, &this->data()[oldPos], sizeof(T));

	if(newPos < oldPos){
		memmove(&this->data()[newPos+1], &this->data()[newPos], (oldPos - newPos) * sizeof(T));
	}else{
		memmove(&this->data()[oldPos], &this->data()[oldPos+1], (newPos - oldPos) * sizeof(T));
	}

	memmove(&this->data()[newPos], &tmp, sizeof(T));
}

template<typename T>
void Vector<T>::swap(uint posA, uint posB){
	T tmp;
	memmove(&tmp, &this->data()[posA], sizeof(T));
	memmove(&this->data()[posA], &this->data()[posB], sizeof(T));
	memmove(&this->data()[posB], &tmp, sizeof(T));
}

template<typename T>
void Vector<T>::remove(uint i){
	this->erase(this->begin() + i);
}

template<typename T>
uint Vector<T>::indexOf(T element){
	for(int i = 0; i < this->size(); i++){
		if(this->data()[i] == element) return i;
	}

	return -1;
}

#endif //CIRCUITOS_VECTOR_H
