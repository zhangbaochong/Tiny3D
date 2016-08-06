#pragma once
#include "Tiny3D.h"
#include "BoxShader.h"
#include "ZCMath.h"
#include "GeometryGenerator.h"

class BoxDemo
{
public:
	BoxDemo();
	~BoxDemo();
public:
	bool Init(HINSTANCE hInstance, HWND hWnd);
	void Update(float dt);
	void Render();
	void Clear();	

	//鼠标事件控制
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
public:
	inline Tiny3DDevice*& GetDevice() { return m_pDevice; }
private:
	int							m_width, m_height;
	HINSTANCE					m_hInstance;
	HWND							m_hWnd;

	Tiny3DDevice*				m_pDevice;
	Tiny3DDeviceContext*			m_pImmediateContext;
	BoxShader*					m_pShader;
	ZCMatrix						m_worldViewProj;

	//顶点缓冲和索引缓冲
	std::vector<VertexIn>		m_vertices;
	std::vector<UINT>			m_indices;

	GeometryGenerator::MeshData	m_box;

	//纹理
	Texture2D					m_tex;

	//控制摄像机位置角度等
	float						m_theta;
	float						m_phi;
	float						m_radius;
	POINT						m_lastMousePos;
};

