#include "Block.h"

String Block::toString()
{
	if (!instance) return String(env);
	return String(env->CallObjectMethod(instance, ObjectClass.getMethodID("toString")), env);
}

std::string Block::getName()
{
	if (!instance)
		return "";
	if (Ripterms::version.type == Ripterms::Version::MAJOR_1_7_10)
	{
		std::string name = String(env->GetObjectField(instance, BlockClass.getFieldID("unlocalizedName")), env).toStdString();
		for (char& c : name)
			c = std::tolower(c);
		return name;
	}
	return toString().toStdString();
}
