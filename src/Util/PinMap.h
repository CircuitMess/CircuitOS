#ifndef CIRCUITOS_PINMAP_H
#define CIRCUITOS_PINMAP_H

#include <unordered_map>

template<typename T>
struct EnumClassHash {
	std::size_t operator()(T t) const {
		return static_cast<std::size_t>(t);
	}
};

template<typename Key>
using PinDefMap = std::unordered_map<Key, int, EnumClassHash<Key>>;

template<typename T>
class PinMap {
public:
	void set(const PinDefMap<T>& map){
		this->map = map;
	}

	int get(T pin){
		const auto i = map.find(pin);
		if(i == map.end()) return -1;
		return i->second;
	}

private:
	PinDefMap<T> map;

};


#endif //CIRCUITOS_PINMAP_H
