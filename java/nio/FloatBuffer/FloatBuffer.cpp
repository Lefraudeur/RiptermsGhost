#include "FloatBuffer.h"

float FloatBuffer::get(int index)
{
	if (!instance)
		return 0.0f;
	return env->CallFloatMethod(instance, FloatBufferClass.getMethodID("get"), index);
}

Ripterms::Maths::Matrix FloatBuffer::toMatrix(int lines, int columns)
{
	Ripterms::Maths::Matrix result(lines, columns);
	if (!instance)
		return result;
	int c = 0;
	for (int i = 0; i < lines; ++i)
	{
		for (int b = 0; b < columns; ++b)
		{
			result[i][b] = get(c);
			c++;
		}
	}
	return result;
}
