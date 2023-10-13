#pragma once
#include <cmath>
#include <string>

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
			float x = 0.0f, y = 0.0f; //in ripterms, little bit weird but x is yaw and y is pitch
			Vector2d operator-(const Vector2d& other_vector);
			float distance();
		};

		Vector2d getYawPitch(Vector3d playerPos, Vector3d facingPos);

		float cropAngle180(float angle);
		float cropAngle360(float angle);

		class Matrix
		{
		public:
			Matrix(int line_number, int column_number, float fill_number = 0.0f);
			Matrix(const Matrix& other_matrix);
			Matrix(std::initializer_list<std::initializer_list<float>> init);
			~Matrix();

			float* operator [](int index);
			operator bool() const;
			Matrix operator *(const Matrix& other_matrix);
			Matrix operator +(const Matrix& other_matrix);

			bool is_valid() const;
			std::string to_string() const;
		private:
			const int line_number;
			const int column_number;
			float** data;
		};

		Vector2d worldToScreen(const Vector3d& world_pos);
	}
}