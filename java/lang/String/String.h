#pragma once
#include "../Object/Object.h"

class String : public Object {
public:
	using Object::Object;
	String(const std::string& str);
	String(const char* str);
	int size() const;
	std::string toStdString() const;
};
