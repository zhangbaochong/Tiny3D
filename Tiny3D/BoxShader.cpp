#include "BoxShader.h"



BoxShader::BoxShader()
{
}


BoxShader::~BoxShader()
{
}

void BoxShader::SetWorldViewProj(ZCMatrix worldViewProj)
{
	this->m_worldViewProj = worldViewProj;
}

VertexOut BoxShader::VS(VertexIn vin)
{
	VertexOut out;
	out.posH = vin.pos * m_worldViewProj;
	out.color = vin.color;
	return out;
}

ZCFLOAT3 BoxShader::PS(VertexOut pin)
{
	return pin.color;
}
