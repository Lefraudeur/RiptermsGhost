#pragma once
#include "../Collection/Collection.h"

class List : public Collection {
public:
	using Collection::Collection;
	static bool init();
protected:
	inline static Ripterms::JavaClass ListClass{};
};