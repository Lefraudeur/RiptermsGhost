#include "Collection.h"

bool Collection::init()
{
	CollectionClass = new Ripterms::JavaClass("java/util/Collection");
	Ripterms::classes.push_back(CollectionClass);
	return CollectionClass->isSuccess;
}
