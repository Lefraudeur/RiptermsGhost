#include "Modules.h"
#include "../../java/lang/ClassLoader/ClassLoader.h"

void Ripterms::Modules::Test::run()
{
	jclass lol = Ripterms::JavaClass::findClass("io/github/lefraudeur/ClassPatcher");
	if (lol) {
		std::cout << "found" << std::endl;
	}
	else {
		std::cout << "not found" << std::endl;
	}
	if (lol) Ripterms::p_env->DeleteWeakGlobalRef(lol);
}

void Ripterms::Modules::Test::renderGUI()
{
	if (ImGui::Button("Run Test")) run();
}