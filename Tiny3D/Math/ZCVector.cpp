#include "ZCVector.h"

float ZCVector::Length() const
{
	float sq = x*x + y*y + z*z;
	return static_cast<float>(sqrt(sq));
}

//归一化
ZCVector ZCVector::Normalize()
{
	float length = Length();
	if (length != 0.0f)
	{
		float inv = 1.0f / length;
		x *= inv;
		y *= inv;
		z *= inv;
	}
	return *this;
}

//点乘
float ZCVector::Dot(ZCVector v) const
{
	return x * v.x + y*v.y + z*v.z;
}

//叉乘
ZCVector ZCVector::Cross(ZCVector rhs) const
{
	float m1 = y * rhs.z - z * rhs.y;
	float m2 = z * rhs.x - x * rhs.z;
	float m3 = x * rhs.y - y * rhs.x;
	return ZCVector(m1, m2, m3, 0.0f);
}

//v1 == v2 ?
bool ZCVector::operator==(const ZCVector& rhs) const
{
	if (abs(x - rhs.x) <= 0.000001f 
		&& abs(y - rhs.y) <= 0.000001f 
		&& abs(z - rhs.z) <= 0.000001f 
		&& abs(w - rhs.w) <= 0.000001f)
		return true;
	else
		return false;
}

//v1 = v2 * m
ZCVector ZCVector::operator* (const ZCMatrix& rhs) const
{
	return ZCVector(x*rhs._11 + y*rhs._21 + z*rhs._31 + w*rhs._41,
					x*rhs._12 + y*rhs._22 + z*rhs._32 + w*rhs._42,
					x*rhs._13 + y*rhs._23 + z*rhs._33 + w*rhs._43,
					x*rhs._14 + y*rhs._24 + z*rhs._34 + w*rhs._44);
}

//分量相乘
ZCVector ZCVector::operator*(const ZCVector& rhs) const
{
	return ZCVector(
		x * rhs.x,
		y * rhs.y,
		z * rhs.z,
		w * rhs.w
	);
}

ZCVector ZCVector::operator*(float factor) const
{
	return ZCVector(
		x * factor,
		y * factor,
		z * factor,
		w
	);
}

//v1 = v2 + v3
ZCVector ZCVector::operator+(const ZCVector& rhs) const
{
	return ZCVector(x + rhs.x, y + rhs.y, z + rhs.z, 0.0f);
}

//v1 = v2 - v3
ZCVector ZCVector::operator-(const ZCVector& rhs) const
{
	return ZCVector(x - rhs.x, y - rhs.y, z - rhs.z, 0.0f);
}

ZCVector ZCVector::operator-() const
{
	return ZCVector(-x, -y - z, w);
}
