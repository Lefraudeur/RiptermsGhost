#include "Maths.h"

Ripterms::Maths::Vector2d Ripterms::Maths::getYawPitch(Vector3d playerPos, Vector3d facingPos)
{
	float pi = 3.1415926535f;
	Vector3d delta = facingPos - playerPos;

	float hypxz = std::sqrt(delta.x * delta.x + delta.z * delta.z);

	float pitchRad = std::atan(delta.y / hypxz);

	float yawDeg = 0.0f;
	float pitchDeg = pitchRad * (180.0f / pi) * -1.0f;

	if (delta.x != 0.0f)
	{
		float yawRad = std::atan(delta.z / delta.x);
		yawDeg = yawRad * (180.0f / pi) + (delta.x < 0.0f ? 90.0f : -90.0f);
	}

	return Vector2d(yawDeg, pitchDeg);
}

float Ripterms::Maths::cropAngle180(float angle)
{
	while (angle < -180.0f) angle += 360.0f;
	while (angle > 180.0f) angle -= 360.0f;
	return angle;
}

Ripterms::Maths::Vector3d::Vector3d()
{
}

Ripterms::Maths::Vector3d::Vector3d(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Ripterms::Maths::Vector3d Ripterms::Maths::Vector3d::operator-(const Vector3d& other_vector)
{
	return Vector3d(x - other_vector.x, y - other_vector.y, z - other_vector.z);
}

Ripterms::Maths::Vector3d Ripterms::Maths::Vector3d::operator+(const Vector3d& other_vector)
{
	return Vector3d(x + other_vector.x, y + other_vector.y, z + other_vector.z);
}

Ripterms::Maths::Vector3d Ripterms::Maths::Vector3d::operator*(float coef)
{
	return Vector3d(x * coef, y * coef, z * coef);
}

float Ripterms::Maths::Vector3d::distance()
{
	return std::sqrt(x*x + y*y + z*z);
}

Ripterms::Maths::Vector2d::Vector2d()
{
}

Ripterms::Maths::Vector2d::Vector2d(float x, float y)
{
	this->x = x;
	this->y = y;
}

Ripterms::Maths::Vector2d Ripterms::Maths::Vector2d::operator-(const Vector2d& other_vector)
{
	return Vector2d(x - other_vector.x, y - other_vector.y);
}

float Ripterms::Maths::Vector2d::distance()
{
	return std::sqrt(x * x + y * y);
}
