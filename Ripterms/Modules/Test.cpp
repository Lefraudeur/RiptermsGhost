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
	if (lol) Ripterms::p_env->DeleteGlobalRef(lol);
}

void Ripterms::Modules::Test::renderGUI()
{
	ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
	if (ImGui::Button("Run Test")) run();
}