#include "Modules.h"
#include "../Patcher/Patcher.h"
#include "../../java/lang/String/String.h"

namespace {
	char name[128] = { 0 };
	String old_ClientModName{};
	String getClientModName() {
		return Ripterms::p_env->CallStaticObjectMethod(Ripterms::classcache->ClientBrandRetrieverClass.javaClass, Ripterms::classcache->ClientBrandRetrieverClass.methods["getClientModName"]);
	}
}

void Ripterms::Modules::ClientBrandChanger::renderGUI()
{
	static bool runonce = true;
	if (runonce) {
		old_ClientModName = getClientModName();
		std::strcpy(name, old_ClientModName.toString().c_str());
		runonce = false;
	}
	ImGui::Text("Client Brand Changer:");
	ImGui::InputText("name", name, sizeof(name));
	if (ImGui::Button("change")) {
		Ripterms::cache->EMPTY_MAP.put(
			String("client_brand"),
			String(name)
		);
	}
	ImGui::SameLine();
	if (ImGui::Button("reset")) {
		std::strcpy(name, old_ClientModName.toString().c_str());
		disable();
	}
}

void Ripterms::Modules::ClientBrandChanger::disable()
{
	Ripterms::cache->EMPTY_MAP.put(
		String("client_brand"),
		old_ClientModName
	);
	old_ClientModName.clear();
}