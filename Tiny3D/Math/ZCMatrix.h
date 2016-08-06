#pragma once
#include <cmath>

class ZCMatrix
{
public:
	union
	{
		float m[4][4];
		struct  
		{
			float _11; float _12; float _13; float _14;
			float _21; float _22; float _23; float _24;
			float _31; float _32; float _33; float _34;
			float _41; float _42; float _43; float _44;
		};		
	};
	
public:
	ZCMatrix() = default;
	ZCMatrix(float a1,float a2,float a3,float a4,
			 float b1,float b2,float b3,float b4,
			 float c1,float c2,float c3,float c4,
		     float d1,float d2,float d3,float d4)
	{
		_11 = a1; _12 = a2; _13 = a3; _14 = a4;
		_21 = b1; _22 = b2; _23 = b3; _24 = b4;
		_31 = c1; _32 = c2; _33 = c3; _34 = c4;
		_41 = d1; _42 = d2; _43 = d3; _44 = d4;
	}
	
	ZCMatrix(const ZCMatrix& rhs)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = rhs.m[i][j];
	}

	ZCMatrix& operator= (const ZCMatrix& rhs)
	{
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				m[i][j] = rhs.m[i][j];
		return *this;
	}

public:
	//单位化
	void Identity();
	//0矩阵
	void SetZero();
	//等于
	bool operator== (const ZCMatrix& rhs) const;
	//加
	ZCMatrix operator+ (const ZCMatrix& rhs) const;
	//减
	ZCMatrix operator- (const ZCMatrix& rhs) const;
	//乘
	ZCMatrix operator* (const ZCMatrix& rhs) const;
};

