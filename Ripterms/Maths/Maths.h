#pragma once
#include <string>

namespace Ripterms
{
	namespace Maths
	{
		inline constexpr double pi = 3.14159265;

		class Vector3d
		{
		public:
			Vector3d();
			Vector3d(double x, double y, double z);
			double x = 0.0f, y = 0.0f, z = 0.0f;
			Vector3d operator-(const Vector3d& other_vector);
			Vector3d operator+(const Vector3d& other_vector);
			Vector3d operator*(double coef);
			double distance();
		};

		class Vector2d
		{
		public:
			Vector2d();
			Vector2d(double x, double y);
			double x = 0.0f, y = 0.0f; //in ripterms, little bit weird but x is yaw and y is pitch
			Vector2d operator-(const Vector2d& other_vector);
			Vector2d operator+(const Vector2d& other_vector);
			Vector2d operator*(double coef);
			Vector2d crop180();
			double distance();
		};

		Vector2d getYawPitch(Vector3d playerPos, Vector3d facingPos);
		Vector3d getCameraVector(Vector2d cameraRot, double distance = 1.0);

		double cropAngle180(double angle);
		double cropAngle360(double angle);

		class Matrix
		{
		public:
			Matrix(int line_number, int column_number, double fill_number = 0.0);
			Matrix(const Matrix& other_matrix);
			Matrix(std::initializer_list<std::initializer_list<double>> init);
			~Matrix();

			Matrix& operator=(const Matrix& other_matrix);
			double* operator [](int index);
			operator bool() const;
			Matrix operator *(const Matrix& other_matrix) const;
			Matrix operator +(const Matrix& other_matrix) const;

			bool is_valid() const;
			std::string to_string() const;
		private:
			int line_number;
			int column_number;
			double** data;

			void destroy_data();
		};

		//relative to camera pos
		//returns z, closer to 0 when closer to camera (negative when behind camera), but this func returns 0 when outside of cam
		double worldToScreen(Vector3d world_pos, Matrix modelView, Matrix projection, int screenWidth, int screenHeight, Vector2d& screen_pos);
	}
}