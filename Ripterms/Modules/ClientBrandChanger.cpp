#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../Hook/JavaHook.h"

void Ripterms::Modules::ClientBrandChanger::renderGUI()
{
	static bool runonce = true;
	if (runonce)
	{
		std::strcpy(name, getClientModName().toStdString().c_str());
		runonce = false;
	}
	ImGui::Text("Client Brand Changer:");
	ImGui::InputText("name", name, sizeof(name));
	if (ImGui::Button("change"))
	{
		enabled = true;
	}
	ImGui::SameLine();
	if (ImGui::Button("reset"))
	{
		enabled = false;
		std::strcpy(name, getClientModName().toStdString().c_str());
	}
}

void Ripterms::Modules::ClientBrandChanger::onGetClientModName(JNIEnv* env, bool* cancel)
{
	if (!enabled)
		return;
	jobject new_name = env->NewStringUTF(name);
	Ripterms::JavaHook::set_return_value<void*>(cancel, *(void**)new_name);
	*cancel = true;
}

String Ripterms::Modules::ClientBrandChanger::getClientModName()
{
	Ripterms::JavaClassV2 ClientBrandRetrieverClass("net/minecraft/client/ClientBrandRetriever");
	return Ripterms::p_env->CallStaticObjectMethod(ClientBrandRetrieverClass.get_jclass(), ClientBrandRetrieverClass.getMethodID("getClientModName"));
}
