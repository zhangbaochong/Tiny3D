#pragma once
#include <windows.h>
#include "ZCVector.h"


class Texture2D
{
public:
	Texture2D() = default;
	Texture2D(UINT width,UINT height);
	~Texture2D();

	Texture2D(const Texture2D& rhs) :m_width(rhs.m_width), m_height(rhs.m_height)
	{
		//Éî¿½±´
		m_pixelBuffer = new ZCFLOAT3*[m_width];
		for (int i = 0; i < m_width; ++i)
		{
			m_pixelBuffer[i] = new ZCFLOAT3[m_height];
		}
		for (int i = 0; i < m_width; ++i)
		{
			for (int j = 0; j < m_height; ++j)
			{
				m_pixelBuffer[i][j] = rhs.m_pixelBuffer[i][j];
			}
		}
	}
	Texture2D& operator=(const Texture2D& rhs)
	{
		if (this == &rhs)
			return *this;
		m_width = rhs.m_width;
		m_height = rhs.m_height;
		m_pixelBuffer = new ZCFLOAT3*[m_width];
		for (int i = 0; i < m_width; ++i)
		{
			m_pixelBuffer[i] = new ZCFLOAT3[m_height];
		}
		for (int i = 0; i < m_width; ++i)
		{
			for (int j = 0; j < m_height; ++j)
			{
				m_pixelBuffer[i][j] = rhs.m_pixelBuffer[i][j];
			}
		}
		return *this;
	}

public:
	ZCFLOAT3 Sample(const ZCFLOAT2& tex);
public:
	UINT m_width;
	UINT m_height;
	ZCFLOAT3** m_pixelBuffer;
};

