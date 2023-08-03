#include "List.h"

bool List::init()
{
	ListClass = new Ripterms::JavaClass("java/util/List");
	Ripterms::classes.push_back(ListClass);
	return ListClass->isSuccess;
}
