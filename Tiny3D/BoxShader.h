#pragma once
#include "ShaderBase.h"
#include "ZCMath.h"

class BoxShader : public ShaderBase
{
public:
	BoxShader();
	~BoxShader();

private:
 	ZCMatrix						m_worldViewProj;		//世界视角投影矩阵	
	Texture2D					m_tex;				//纹理
 	ZCMatrix						m_world;				//世界矩阵
 	ZCMatrix						m_worldInvTranspose;	//世界矩阵逆矩阵的转置，用于调整法线
 	Lights::Material				m_material;			//材质
	Lights::DirectionalLight		m_dirLight;			//平行光
	ZCVector						m_eyePos;			//观察点

public:
	void SetWorldViewProj(const ZCMatrix& worldViewProj);
	void SetTexture(const Texture2D& tex);
	void SetWorld(const ZCMatrix& world);
	void SetWorldInvTranspose(const ZCMatrix& worldInvTrans);
	void SetEyePos(const ZCVector& eyePos);
	void SetMaterial(const Lights::Material& material);
	void SetDirLight(const Lights::DirectionalLight& dirLight);
public:
	VertexOut VS(const VertexIn& vin);	//顶点着色器
	ZCVector PS(VertexOut& pin);
};

