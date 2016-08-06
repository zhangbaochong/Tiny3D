#pragma once
#include "ShaderBase.h"

class BoxShader : public ShaderBase
{
public:
	BoxShader();
	~BoxShader();

private:
 	ZCMatrix m_worldViewProj;		//世界视角投影矩阵	
// 	ZCMatrix m_world;				//世界矩阵
// 	ZCMatrix m_worldInvTranspose;	//世界矩阵逆矩阵的转置，用于调整法线
// 	ZCMatrix m_texTrans;				//纹理变换
// 	Lights::Material m_material;		//材质
public:
	void SetWorldViewProj(ZCMatrix worldViewProj);
public:
	VertexOut VS(VertexIn vin);	//顶点着色器
	ZCFLOAT3 PS(VertexOut pin);
};

