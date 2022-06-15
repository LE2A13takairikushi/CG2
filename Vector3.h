#pragma once
class Vector3
{
public:
	float x;	// x����
	float y;	// y����
	float z;	// z����
public:
	Vector3();
	Vector3(float x, float y, float z);

	//�����o�֐�
	float length() const;
	Vector3& normalize();
	float dot(const Vector3& v)const;
	Vector3 cross(const Vector3& v)const;

	Vector3 operator+()const;
	Vector3 operator-()const;

	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v1, float s);
const Vector3 operator*(float s, const Vector3& v1);
const Vector3 operator/(const Vector3& v1, float s);
