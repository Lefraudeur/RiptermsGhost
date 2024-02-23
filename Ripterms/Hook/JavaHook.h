#pragma once
#include <JNI/jni.h>
#include "../../HotSpot/HotSpot.hpp"

namespace Ripterms::JavaHook
{
	void clean();

	template <typename T> inline void set_return_value(bool* cancel, T return_value)
	{
		*(T*)((void**)cancel + 8) = return_value; //see asm code to understand that
	}

	//param from left to right (arg0 beeing this for non static methods)
	template <typename T> inline T get_primitive_param_at(HotSpot::frame* frame, int index)
	{
		return *(T*)(frame->get_locals() - index);
	}

	inline jobject get_jobject_param_at(HotSpot::frame* frame, int index)
	{
		return (jobject)(frame->get_locals() - index);
	}

	typedef void(*i2i_detour_t)(HotSpot::frame* frame, HotSpot::Thread* thread, bool* cancel);
	class Midi2iHook
	{
	public:
		Midi2iHook(uint8_t* target, i2i_detour_t detour);
		~Midi2iHook();

		bool is_error = true;
	private:
		uint8_t* target = nullptr;
		uint8_t* allocated_assembly = nullptr;
	};

	bool hook(jmethodID methodID, i2i_detour_t detour);
}