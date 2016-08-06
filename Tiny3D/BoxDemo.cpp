#include "BoxDemo.h"
#include <vector>
#include "Vertex.h"
#include "BoxShader.h"
#include "MathUtil.h"

//m_theta(1.5f*MathUtil::PI),m_phi(0.25*MathUtil::PI),
BoxDemo::BoxDemo():m_theta(0.25f * MathUtil::PI),m_phi(0.25*MathUtil::PI),m_radius(3.0f)
{	
	m_lastMousePos.x = 0;
	m_lastMousePos.y = 0;
}


BoxDemo::~BoxDemo()
{
}

bool BoxDemo::Init(HINSTANCE hInstance,HWND hWnd)
{	
	m_hWnd = hWnd;
	m_hInstance = hInstance;
	RECT rc;
	GetClientRect(m_hWnd, &rc);
	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	m_pDevice = new Tiny3DDevice(m_width, m_height);	
	m_pImmediateContext = new Tiny3DDeviceContext();
	m_pImmediateContext->Init(m_pDevice);
	m_pShader = new BoxShader();

	//创建顶点缓冲
	m_vertices = std::vector<VertexIn>{
	VertexIn(ZCVector(-0.5f, -0.5f, -0.5f, 1.f), ZCFLOAT3(1.f, 1.f, 1.f),ZCFLOAT2(0,0),ZCVector(2,1,3)),//white
	VertexIn(ZCVector(-0.5f, +0.5f, -0.5f, 1.f), ZCFLOAT3(0.f, 0.f, 0.f),ZCFLOAT2(0,0),ZCVector(2,1,3)),//black
	VertexIn(ZCVector(+0.5f, +0.5f, -0.5f, 1.f), ZCFLOAT3(1.f, 0.f, 0.f),ZCFLOAT2(0,0),ZCVector(2,1,3)),//red
	VertexIn(ZCVector(+0.5f, -0.5f, -0.5f, 1.f), ZCFLOAT3(0.f, 1.f, 0.f),ZCFLOAT2(0,0),ZCVector(2,1,3)),//green
	VertexIn(ZCVector(-0.5f, -0.5f, +0.5f, 1.f), ZCFLOAT3(0.f, 0.f, 1.f),ZCFLOAT2(0,0),ZCVector(2,1,3)),//blue
	VertexIn(ZCVector(-0.5f, +0.5f, +0.5f, 1.f), ZCFLOAT3(1.f, 1.f, 0.f),ZCFLOAT2(0,0),ZCVector(2,1,3)),//yellow
	VertexIn(ZCVector(+0.5f, +0.5f, +0.5f, 1.f), ZCFLOAT3(0.f, 1.f, 1.f),ZCFLOAT2(0,0),ZCVector(2,1,3)),//cyan
	VertexIn(ZCVector(+0.5f, -0.5f, +0.5f, 1.f), ZCFLOAT3(1.f, 0.f, 1.f),ZCFLOAT2(0,0),ZCVector(2,1,3))//blue

	};
	m_pImmediateContext->SetVertexBuffer(m_vertices);	

	//索引缓冲
	m_indices = std::vector<UINT>{
		// front face
		0, 1, 2,
		0, 2, 3,

		// back face
		4, 6, 5,
		4, 7, 6,

		// left face
		4, 5, 1,
		4, 1, 0,

		// right face
		3, 2, 6,
		3, 6, 7,

		// top face
		1, 5, 6,
		1, 6, 2,

		// bottom face
		4, 0, 3,
		4, 3, 7
		
	};
	m_pImmediateContext->SetIndexBuffer(m_indices);

	//设置着色器
	m_pImmediateContext->SetShader(m_pShader);

	return true;
}

void BoxDemo::Update(float dt)
{
	
	float x = m_radius * sinf(m_phi) * cosf(m_theta);
	float z = m_radius * sinf(m_phi) * sinf(m_theta);
	float y = m_radius * cosf(m_phi);

	ZCVector pos(x, y, z, 1.f);
	ZCVector target(0.f, 0.f, 0.f, 1.f);
	ZCVector up(0.f, 1.f, 0.f, 0.f);

	ZCMatrix view = MathUtil::ZCMatrixLookAtLH(pos, target, up);
	ZCMatrix proj = MathUtil::ZCMatrixPerspectiveFovLH(MathUtil::PI / 4, m_pDevice->GetClientWidth() /
		static_cast<float>(m_pDevice->getClientHeight()), 0.1f, 10.f);

	ZCMatrix world = MathUtil::ZCMatrixIdentity();
	m_worldViewProj = world*view*proj;

	//设置相机位置 以便背面消隐
	m_pImmediateContext->SetCameraPos(pos);
}

void BoxDemo::Render()
{
	//清空后缓冲图片
	m_pDevice->ClearBuffer(ZCFLOAT3(0.f, 0.f, 0.f));

	//设置渲染状态
	m_pImmediateContext->SetRenderMode(TINY3D_FILL_SOLIDE);
	//设置着色器变量
	m_pShader->SetWorldViewProj(m_worldViewProj);

	m_pImmediateContext->DrawIndexed(m_indices.size(), 0, 0);
}

void BoxDemo::Clear()
{
	delete m_pDevice;
	delete m_pImmediateContext;
}

void BoxDemo::OnMouseDown(WPARAM btnState, int x, int y)
{
	m_lastMousePos.x = x;
	m_lastMousePos.y = y;
	SetCapture(m_hWnd);
}

void BoxDemo::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void BoxDemo::OnMouseMove(WPARAM btnState, int x, int y)
{
	if ((btnState & MK_LBUTTON) != 0)
	{
		//角度转弧度
		float dx = MathUtil::ZCConvertToRadians(0.25f*static_cast<float>(x - m_lastMousePos.x));
		float dy = MathUtil::ZCConvertToRadians(0.25f*static_cast<float>(y - m_lastMousePos.y));

		m_theta -= dx;
		m_phi += dy;

		m_phi = MathUtil::Clamp(m_phi, 0.1f, MathUtil::PI - 0.1f);
	}
	else if ((btnState & MK_RBUTTON) != 0)
	{
		float dx = 0.2f*static_cast<float>(x - m_lastMousePos.x);
		float dy = 0.2f*static_cast<float>(y - m_lastMousePos.y);

		m_radius += dx - dy;

		m_radius = MathUtil::Clamp(m_radius, 3.0f, 300.0f);
	}

	m_lastMousePos.x = x;
	m_lastMousePos.y = y;
}

