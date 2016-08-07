#pragma once
#include "Tiny3DDevice.h"
#include "Vertex.h"
#include <vector>
#include "ShaderBase.h"

enum TINY3D_FILL_MODE//渲染模式
{
	TINY3D_FILL_WIREFRAME,//线框模式
	TINY3D_FILL_SOLIDE	  //实体模式
};

class Tiny3DDeviceContext
{
public:
	Tiny3DDeviceContext();
	~Tiny3DDeviceContext();
public:
	void Init(Tiny3DDevice* pDevice);										//初始化
	void SetRenderMode(TINY3D_FILL_MODE mode);								//设置渲染模式
	void SetVertexBuffer(std::vector<VertexIn> vertices);					//设置顶点缓冲
	void SetCameraPos(const ZCVector& pos);									//设置相机位置
	void SetIndexBuffer(std::vector<UINT> indices);							//设置索引缓冲
	void SetShader(ShaderBase* base);										//设置着色器
	void DrawIndexed(UINT indexCount,UINT startIndexLocation,UINT startVertexLocation);																//绘制图形
private:
	void ToCVV(VertexOut& v);																	//投影后的坐标转化为cvv
	bool Clip(const VertexOut& v);																//cvv裁剪
	VertexOut TransformToProj(const VertexIn& v);													//转到齐次裁剪空间
	void TransformToScreen(const ZCMatrix& m,VertexOut& v);										//转换到屏幕坐标
	bool BackFaceCulling(const VertexIn& v1, const VertexIn& v2, const VertexIn& v3);			//背面消隐测试
	void BresenhamDrawLine(int x1, int y1, int x2, int y2);										//画线
	void ScanlineFill(const VertexOut& left, const VertexOut& right, int yIndex);				//扫描线
	void DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);			//画三角形
	void DrawTriangleTop(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);			//画平顶三角形
	void DrawTriangleBottom(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3); 		//画平底三角形
	void TriangleRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3);	//光栅化三角形
private:
	Tiny3DDevice* m_pDevice;													//设备
	TINY3D_FILL_MODE m_renderMode;											//渲染状态
	std::vector<VertexIn> m_vertices;										//顶点缓冲
	std::vector<UINT> m_indices;												//索引缓冲
	ShaderBase* m_pShader;													//着色器
	ZCVector m_cameraPos;													//相机位置 用于背面消隐
};

