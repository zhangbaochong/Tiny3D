#pragma once
#include <cmath>
#include "ZCMatrix.h"

class ZCVector
{
public:
	float x;
	float y;
	float z;
	float w;	//0代表向量 1代表点

public:
	ZCVector() = default;
	ZCVector(float x1, float y1, float z1, float w1 = 0) :x(x1), y(y1), z(z1), w(w1) {}
	ZCVector(const ZCVector& rhs) :x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {}
	ZCVector& operator= (const ZCVector& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return *this;
	}

public:
	//向量长度
	float Length() const;	
	//归一化
	ZCVector Normalize();
	//点乘
	float Dot(ZCVector v) const;
	//叉乘
	ZCVector Cross(ZCVector rhs) const;
	//重载== 
	bool operator==(const ZCVector& rhs) const;
	//与变换矩阵相乘
	ZCVector operator* (const ZCMatrix& rhs) const;
	//与ZCVector分量相乘
	ZCVector operator* (const ZCVector& rhs) const;
	//与float相乘
	ZCVector operator*(float factor) const;
	//加
	ZCVector operator+ (const ZCVector& rhs) const;
	//减
	ZCVector operator- (const ZCVector& rhs) const;
	//负号
	ZCVector operator-() const;
	
};


class ZCFLOAT3
{
public:
	float x;
	float y;
	float z;
public:
	ZCFLOAT3() = default;
	ZCFLOAT3(float r,float b,float g):x(r),y(b),z(g){}
	ZCFLOAT3(const ZCFLOAT3& rhs) :x(rhs.x), y(rhs.y), z(rhs.z) {}
	ZCFLOAT3& operator= (const ZCFLOAT3& rhs)
	{
		if (this == &rhs)
			return *this;
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
};


//二维向量主要用于表示纹理坐标
class ZCFLOAT2
{
public:
	float u;
	float v;
public:
	ZCFLOAT2() = default;
	ZCFLOAT2(float x, float y) :u(x), v(y) {}
	ZCFLOAT2(const ZCFLOAT2& rhs):u(rhs.u),v(rhs.v){}
	ZCFLOAT2& operator= (const ZCFLOAT2& rhs)
	{
		if (this == &rhs)
			return *this;
		u = rhs.u;
		v = rhs.v;
		return *this;
	}
};