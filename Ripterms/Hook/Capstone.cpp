#include "Capstone.h"
#include <capstone/capstone.h>

static csh handle = 0;


bool Ripterms::Capstone::init()
{
	return cs_open(CS_ARCH_X86, CS_MODE_64, &handle) == CS_ERR_OK;
}

void Ripterms::Capstone::clean()
{
	if (!handle) return;
	cs_close(&handle);
}

uint8_t Ripterms::Capstone::find_bytes_to_replace(const uint8_t* target)
{
	if (!handle) return 0;
	cs_insn* insn = nullptr;
	size_t count = cs_disasm(handle, target, 28, 0, 0, &insn);
	if (!count)
		return 0;

	uint8_t bytes_to_replace = 0;
	for (size_t i = 0; i < count; ++i)
	{
		bytes_to_replace += insn[i].size;
		if (bytes_to_replace >= 5)
			break;
	}
	cs_free(insn, count);
	return bytes_to_replace;
}
