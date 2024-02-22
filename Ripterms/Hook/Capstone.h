#pragma once
#include <cstdint>

namespace Ripterms::Capstone
{
	bool init();
	void clean();

	uint8_t find_bytes_to_replace(const uint8_t* target);
}