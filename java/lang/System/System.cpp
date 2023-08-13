#include "System.h"

void System::gc()
{
	Ripterms::p_env->CallStaticVoidMethod(Ripterms::classcache->SystemClass.javaClass, Ripterms::classcache->SystemClass.methods["gc"]);
}