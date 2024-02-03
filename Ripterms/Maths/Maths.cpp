#include "Maths.h"
#include <Windows.h>
#include <gl/GLU.h>
#include <cmath>
#include <iostream>

Ripterms::Maths::Vector2d Ripterms::Maths::getYawPitch(Vector3d playerPos, Vector3d facingPos)
{
	constexpr float pi = 3.14159265f;
	Vector3d delta = facingPos - playerPos;

	float hypxz = std::sqrt(delta.x * delta.x + delta.z * delta.z);

	float pitchRad = std::atan(-delta.y / hypxz);

	float yawDeg = 0.0f;
	float pitchDeg = pitchRad * (180.0f / pi);

	if (delta.x != 0.0f)
	{
		float yawRad = std::atan2(delta.z, delta.x) - pi/2;
		yawDeg = yawRad * (180.0f / pi);
	}

	return Vector2d(yawDeg, pitchDeg);
}

float Ripterms::Maths::cropAngle180(float angle)
{
	while (angle <= -180.0f) angle += 360.0f;
	while (angle > 180.0f) angle -= 360.0f;
	return angle;
}

float Ripterms::Maths::cropAngle360(float angle)
{
	while (angle < 0) angle += 360.0f;
	while (angle >= 360.0f) angle -= 360.0f;
	return angle;
}

bool Ripterms::Maths::worldToScreen(Vector3d world_pos, Matrix modelView, Matrix projection, int screenWidth, int screenHeight, Vector2d& screen_pos)
{
	Matrix world_matrix =
	{
		{world_pos.x, world_pos.y, world_pos.z, 1.0f}
	};

	Matrix clip_space_pos = (world_matrix * modelView) * projection;
	Vector3d ndc
	(
		clip_space_pos[0][0] / clip_space_pos[0][3],
		clip_space_pos[0][1] / clip_space_pos[0][3],
		clip_space_pos[0][2] / clip_space_pos[0][3]
	);

	if (std::abs(ndc.x) <= 1.0f && std::abs(ndc.y) <= 1.0f && ndc.z <= 1.0f)
	{
		screen_pos.x = ((ndc.x + 1.0f) / 2.0f) * screenWidth;
		screen_pos.y = ((-ndc.y + 1.0f) / 2.0f) * screenHeight; //-1 is bottom of screen, whereas 0px is top of window
		return true;
	}
	return false;
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

Ripterms::Maths::Matrix::Matrix(int line_number, int column_number, float fill_number) :
	line_number(line_number),
	column_number(column_number),
	data(new float*[line_number]{nullptr})
{
	for (int i = 0; i < line_number; ++i)
	{
		data[i] = new float[column_number] {0};
		if (fill_number != 0.0f)
		{
			for (int b = 0; b < column_number; b++)
				data[i][b] = fill_number;
		}
	}
}

Ripterms::Maths::Matrix::Matrix(const Matrix& other_matrix) :
	Matrix(other_matrix.line_number, other_matrix.column_number)
{
	for (int i = 0; i < line_number; ++i)
	{
		memcpy(data[i], other_matrix.data[i], column_number * sizeof(float));
	}
}

Ripterms::Maths::Matrix::Matrix(std::initializer_list<std::initializer_list<float>> init) :
	Matrix((int)init.size(), (int)init.begin()->size())
{
	for (int i = 0; i < line_number; ++i)
	{
		memcpy(data[i], (init.begin() + i)->begin(), column_number * sizeof(float));
	}
}

Ripterms::Maths::Matrix& Ripterms::Maths::Matrix::operator=(const Matrix& other_matrix)
{
	if (other_matrix.line_number != this->line_number || other_matrix.column_number != this->column_number)
	{
		destroy_data();
		this->line_number = other_matrix.line_number;
		this->column_number = other_matrix.column_number;
		data = new float* [line_number] {nullptr};
		for (int i = 0; i < line_number; ++i)
		{
			data[i] = new float[column_number] {0.0f};
		}
	}

	for (int i = 0; i < line_number; ++i)
	{
		memcpy(data[i], other_matrix.data[i], column_number * sizeof(float));
	}
	return *this;
}

float* Ripterms::Maths::Matrix::operator[](int index)
{
	if (is_valid() && index < line_number)
		return data[index];
	return nullptr;
}

Ripterms::Maths::Matrix::operator bool() const
{
	return is_valid();
}

Ripterms::Maths::Matrix Ripterms::Maths::Matrix::operator*(const Matrix& other_matrix) const
{
	if (!is_valid() || !other_matrix.is_valid() || this->column_number != other_matrix.line_number)
		return { {0} };
	Matrix result(this->line_number, other_matrix.column_number);
	for (int i = 0; i < result.line_number; ++i)
	{
		for (int b = 0; b < result.column_number; ++b)
		{
			for (int c = 0; c < other_matrix.line_number; ++c)
			{
				result[i][b] += data[i][c] * other_matrix.data[c][b];
			}
		}
	}
	return result;

}

Ripterms::Maths::Matrix Ripterms::Maths::Matrix::operator+(const Matrix& other_matrix) const
{
	if (line_number != other_matrix.line_number || column_number != other_matrix.column_number)
		return { {0} };
	Matrix result(line_number, column_number);
	for (int i = 0; i < result.line_number; ++i)
	{
		for (int b = 0; b < result.column_number; ++b)
		{
			result[i][b] = data[i][b] + other_matrix.data[i][b];
		}
	}
	return result;
}

bool Ripterms::Maths::Matrix::is_valid() const
{
	return line_number && column_number;
}

std::string Ripterms::Maths::Matrix::to_string() const
{
	std::string result{};
	for (int i = 0; i < line_number; i++)
	{
		for (int b = 0; b < column_number; b++)
		{
			result += std::to_string(data[i][b]) + ", ";
		}
		result.pop_back();
		result.pop_back();
		result += '\n';
	}
	return result;
}

void Ripterms::Maths::Matrix::destroy_data()
{
	if (data)
	{
		for (int i = 0; i < line_number; ++i)
		{
			delete[] data[i];
		}
		delete[] data;
	}
}

Ripterms::Maths::Matrix::~Matrix()
{
	destroy_data();
}
