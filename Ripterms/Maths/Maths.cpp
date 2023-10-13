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

Ripterms::Maths::Vector2d Ripterms::Maths::worldToScreen(const Vector3d& world_pos)
{
	float model_matrix[4][4] = {0};
	float view_matrix[4][4] = {0};
	float projection_matrix[4][4] = {0};

	float model_view_matrix[4][4] = { 0 };

	return {};
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

Ripterms::Maths::Matrix Ripterms::Maths::Matrix::operator*(const Matrix& other_matrix)
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

Ripterms::Maths::Matrix Ripterms::Maths::Matrix::operator+(const Matrix& other_matrix)
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

Ripterms::Maths::Matrix::~Matrix()
{
	if (data)
	{
		for (int i = 0; i < line_number; ++i)
		{
			delete[] data[i];
		}
		delete data;
	}
}
