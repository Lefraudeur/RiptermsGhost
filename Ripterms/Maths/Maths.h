#pragma once
#include <cmath>

namespace Ripterms
{
	namespace Maths
	{
		class Vector3d
		{
		public:
			Vector3d();
			Vector3d(float x, float y, float z);
			float x = 0.0f, y = 0.0f, z = 0.0f;
			Vector3d operator-(const Vector3d& other_vector);
			Vector3d operator+(const Vector3d& other_vector);
			Vector3d operator*(float coef);
			float distance();
		};

		class Vector2d
		{
		public:
			Vector2d();
			Vector2d(float x, float y);
			float x = 0.0f, y = 0.0f;
			Vector2d operator-(const Vector2d& other_vector);
			float distance();
		};

		Vector2d getYawPitch(Vector3d playerPos, Vector3d facingPos);

		float cropAngle180(float angle);
	}
}