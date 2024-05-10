#include "Modules.h"
#include "../Cache/Cache.h"
#include <ImGui/imgui.h>
#include "../Hook/JavaHook.h"

void Ripterms::Modules::ClientBrandChanger::renderGUI()
{
	static bool runonce = true;
	if (runonce)
	{
		std::strcpy(client_name, getClientModName().toStdString().c_str());
		runonce = false;
	}
	ImGui::Text("Client brand:");
	ImGui::InputText("name", client_name, sizeof(client_name));
	if (ImGui::Button("reset"))
	{
		std::strcpy(client_name, getClientModName().toStdString().c_str());
	}
}

void Ripterms::Modules::ClientBrandChanger::onGetClientModName(JNIEnv* env, bool* cancel)
{
	if (!enabled || client_name[0] == '\0') return;
	jobject new_name = env->NewStringUTF(client_name);
	Ripterms::JavaHook::set_return_value<void*>(cancel, *(void**)new_name);
	*cancel = true;
}

String Ripterms::Modules::ClientBrandChanger::getClientModName()
{
	Ripterms::JavaClassV2 ClientBrandRetrieverClass("net/minecraft/client/ClientBrandRetriever");
	return Ripterms::p_env->CallStaticObjectMethod(ClientBrandRetrieverClass.get_jclass(), ClientBrandRetrieverClass.getMethodID("getClientModName"));
}
