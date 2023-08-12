#include "Modules.h"
#include "../Patcher/Patcher.h"
#include "../../java/lang/String/String.h"

namespace {
	char name[128] = { 0 };
	String getClientModName() {
		return Ripterms::p_env->CallStaticObjectMethod(Ripterms::classcache->ClientBrandRetrieverClass.javaClass, Ripterms::classcache->ClientBrandRetrieverClass.methods["getClientModName"]);
	}
}

void Ripterms::Modules::ClientBrandChanger::renderGUI()
{
	static bool runonce = true;
	if (runonce) {
		std::strcpy(name, getClientModName().toString().c_str());
		runonce = false;
	}
	ImGui::Text("Client Brand Changer:");
	ImGui::InputText("name", name, sizeof(name));
	ImGui::NewLine();
	if (ImGui::Button("change")) {
		Ripterms::Patcher::patchGetClientModName(name);
		Ripterms::cache->theMinecraft.getUsageSnooper().getSnooperStats().put(String("client_brand"), String(name));
	}
	ImGui::SameLine();
	if (ImGui::Button("reset")) {
		disable();
	}
}

void Ripterms::Modules::ClientBrandChanger::disable()
{
	Ripterms::p_tienv->RetransformClasses(1, &Ripterms::classcache->ClientBrandRetrieverClass.javaClass);
	String clientname = getClientModName();
	Ripterms::cache->theMinecraft.getUsageSnooper().getSnooperStats().put(String("client_brand"), clientname);
	std::strcpy(name, clientname.toString().c_str());
}