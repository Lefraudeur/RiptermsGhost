#pragma once
#include <cmath>

namespace Ripterms
{
	namespace Maths
	{
		class Vector3d
		{
		public:
			Vector3d(float x, float y, float z);
			float x = 0, y = 0, z = 0;
			Vector3d operator-(const Vector3d& other_vector);
			float distance();
		};

		class Vector2d
		{
		public:
			Vector2d(float x, float y);
			float x = 0, y = 0;
			Vector2d operator-(const Vector2d& other_vector);
			float distance();
		};

		Vector2d getYawPitch(Vector3d playerPos, Vector3d facingPos);

		float cropAngle0_360(float angle);
		float cropAngle180(float angle);
	}
}