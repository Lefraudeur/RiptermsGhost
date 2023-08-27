#pragma once
#include <JNI/jni.h>
#include <JNI/jvmti.h>
#include "../../java/lang/Object/Object.h"
#include "../../java/lang/String/String.h"
#include "../../java/util/Map/Map.h"

class Event
{
public:
	Event(JNIEnv* env, int mask);

	void dispatch();
	bool isEvent();
	void cancel();

	enum Type
	{
		UNKNOWN,
		PACKET_SEND
	};
	Type type = UNKNOWN;

	JNIEnv* env = nullptr;
	bool isCanceled = false;
	Map EMPTY_MAP{};
private:
	inline static std::unordered_map<int, Type> events =
	{
		{1337, PACKET_SEND}
	};
};
