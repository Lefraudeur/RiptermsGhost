#include "IntBuffer.h"

int IntBuffer::get(int index)
{
	if (!instance)
		return 0;
	return env->CallIntMethod(instance, IntBufferClass.getMethodID("get"), index);
}

Ripterms::Maths::Matrix IntBuffer::toMatrix(int lines, int columns)
{
	Ripterms::Maths::Matrix result(lines, columns);
	if (!instance)
		return result;

	int c = 0;
	for (int i = 0; i < lines; ++i)
	{
		for (int b = 0; b < columns; ++b)
		{
			result[i][b] = (float)get(c);
			c++;
		}
	}
	return result;
}
