#pragma once
#include "Vertex.h"
#include "ZCVector.h"
#include "ZCMatrix.h"
#include "LightHelper.h"

class ShaderBase
{
public:
	ShaderBase();
	virtual ~ShaderBase();

public:
	virtual VertexOut VS(VertexIn vin) = 0;	//顶点着色器
	virtual ZCFLOAT3 PS(VertexOut pin) = 0;	//像素着色器
};

