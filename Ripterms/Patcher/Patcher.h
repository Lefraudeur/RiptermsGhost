#pragma once
#include <string>

namespace Ripterms::Patcher
{
	bool init();
	void clean();
	void patchGetMouseOver(double reach);
	void patchGetClientModName(const std::string& client_name);
}