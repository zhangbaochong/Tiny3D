#include "Texture2D.h"


Texture2D::Texture2D(UINT width, UINT height)
{
	m_width = width;
	m_height = height;
	m_pixelBuffer = new ZCVector*[width];
	for (int i = 0; i < width; ++i)
	{
		m_pixelBuffer[i] = new ZCVector[height];
	}
}

Texture2D::~Texture2D()
{
	if (m_pixelBuffer)
	{
		for (int i = 0; i < m_width; ++i)
		{
			delete[] m_pixelBuffer[i];
		}
	}
}

ZCVector Texture2D::Sample(const ZCFLOAT2& tex)
{
	//纹理寻址采用d3d中的wrap方式 当坐标大于1时，通过去掉整数部分，根据得到的小数部分来得到纹理值；
	//坐标小于0，则加上一个最小正数，让坐标大于0。
	
	if (tex.u >= 0 && tex.u <= 1 && tex.v >= 0 && tex.v <= 1)
	{
		UINT x = tex.u * (m_width - 1);
		UINT y = tex.v * (m_height - 1);
		return m_pixelBuffer[x][y];
	}
	else
	{
		float u, v;
		if (tex.u > 1)
			u = tex.u - static_cast<int>(tex.u);
		else if (tex.u < 0)
			u = (static_cast<int>(-tex.u) + 1) + tex.u;
		if (tex.v > 1)
			v = tex.v - static_cast<int>(tex.v);
		else if (tex.v < 0)
			v = (static_cast<int>(-tex.v) + 1) + tex.v;
		UINT x = u * (m_width - 1);
		UINT y = v * (m_height - 1);
		return m_pixelBuffer[x][y];
	}
}
