#include "Texture2D.h"


Texture2D::Texture2D(UINT width, UINT height)
{
	m_width = width;
	m_height = height;
	m_pixelBuffer = new ZCFLOAT3*[width];
	for (int i = 0; i < width; ++i)
	{
		m_pixelBuffer[i] = new ZCFLOAT3[height];
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

ZCFLOAT3 Texture2D::Sample(ZCFLOAT2 tex)
{
	UINT u = tex.u * (m_width-1);
	UINT v = tex.v * (m_height-1);
	return m_pixelBuffer[u][v];
}
