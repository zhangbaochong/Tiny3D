#pragma once
#include <windows.h>
#include "ZCVector.h"
#include "Vertex.h"

class Tiny3DDevice
{
public:
	Tiny3DDevice(int width, int height);
	~Tiny3DDevice();
public:
	void DrawPixel(int x, int y, ZCVector color);	
	float GetZ(int x, int y) const;
	void SetZ(int x, int y, float z);
	inline UINT*& GetFrameBuffer() { return m_pFramebuffer; }
	inline int GetClientWidth() { return m_width; }
	inline int getClientHeight() { return m_height; }
	void ClearBuffer(ZCVector color);
private:
	int m_width;
	int m_height;
	UINT* m_pFramebuffer;
	float **m_zBuffer;		//z»º´æ
};