#pragma once
#include <JNI/jni.h>

namespace Ripterms
{
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
			PRE_MOTION = 13371337,
			POST_MOTION = 13371338,
			PRE_ATTACK = 13371339,
			POST_ATTACK = 13371340

		};
		Type type = UNKNOWN;

		JNIEnv* env = nullptr;
		bool isCanceled = false;
	};
}
