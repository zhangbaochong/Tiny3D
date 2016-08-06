#include "BoxShader.h"



BoxShader::BoxShader()
{
}


BoxShader::~BoxShader()
{
}

void BoxShader::SetWorldViewProj(const ZCMatrix& worldViewProj)
{
	this->m_worldViewProj = worldViewProj;
}

void BoxShader::SetTexture(const Texture2D& tex)
{
	this->m_tex = tex;
}

VertexOut BoxShader::VS(VertexIn vin)
{
	VertexOut out;
	out.posH = vin.pos * m_worldViewProj;
	out.color = vin.color;
	out.normal = vin.normal;
	out.tex = vin.tex;
	return out;
}

ZCFLOAT3 BoxShader::PS(VertexOut pin)
{
	//return pin.color;
	return m_tex.Sample(pin.tex);
}
