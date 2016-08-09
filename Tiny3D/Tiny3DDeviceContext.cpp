#include "Tiny3DDeviceContext.h"
#include "MathUtil.h"
#include <algorithm>

Tiny3DDeviceContext::Tiny3DDeviceContext():m_renderMode(TINY3D_FILL_WIREFRAME),m_cameraPos(ZCVector(0.f,0.f,0.f,1.f))
{
}


Tiny3DDeviceContext::~Tiny3DDeviceContext()
{
}

void Tiny3DDeviceContext::Init(Tiny3DDevice* pDevice)
{
	m_pDevice = pDevice;
}

//设置渲染模式
void Tiny3DDeviceContext::SetRenderMode(TINY3D_FILL_MODE mode)
{
	m_renderMode = mode;
}

//设置顶点缓冲
void Tiny3DDeviceContext::SetVertexBuffer(std::vector<VertexIn> vertices)
{
	m_vertices = vertices;
}

//设置相机位置
void Tiny3DDeviceContext::SetCameraPos(const ZCVector& pos)
{
	m_cameraPos = pos;
}

//设置索引缓冲
void Tiny3DDeviceContext::SetIndexBuffer(std::vector<UINT> indices)
{
	m_indices = indices;
}

//设置着色器
void Tiny3DDeviceContext::SetShader(ShaderBase* base)
{
	m_pShader = base;
}

//绘制顶点缓冲中的三角形
void Tiny3DDeviceContext::DrawIndexed(UINT indexCount, UINT startIndexLocation, UINT startVertexLocation)
{
	//得到屏幕变换矩阵
	ZCMatrix screenTransformMat = MathUtil::ZCMatrixScreenTransform(m_pDevice->GetClientWidth(),
		m_pDevice->getClientHeight());

 	for (int i = startIndexLocation; i < indexCount / 3; ++i)
 	{
		VertexIn p1 = m_vertices[startVertexLocation + m_indices[3 * i]];
		VertexIn p2 = m_vertices[startVertexLocation + m_indices[3 * i + 1]];
		VertexIn p3 = m_vertices[startVertexLocation + m_indices[3 * i + 2]];
		//背面消隐
		if (BackFaceCulling(p1, p2, p3) == false)
		{
			continue;
		}

		//转换到齐次裁剪空间，即投影后的坐标
		VertexOut v1 = TransformToProj(p1);
		VertexOut v2 = TransformToProj(p2);
		VertexOut v3 = TransformToProj(p3);


		//判断是否通过cvv裁剪
		if (Clip(v1) == false || Clip(v2) == false || Clip(v3) == false)
		{
			continue;
		}

		//进行透视除法 转到cvv
		ToCVV(v1);
		ToCVV(v2);
		ToCVV(v3);

		//将投影得到的坐标转化为屏幕坐标
		TransformToScreen(screenTransformMat, v1);
		TransformToScreen(screenTransformMat, v2);
		TransformToScreen(screenTransformMat, v3);
		
		DrawTriangle(v1, v2, v3);
 	}
}

//转化到cvv
void Tiny3DDeviceContext::ToCVV(VertexOut& v)
{
	v.posH.x /= v.posH.w;
	v.posH.y /= v.posH.w;
	v.posH.z /= v.posH.w;
	v.posH.w = 1;
}

//简单cvv裁剪
bool Tiny3DDeviceContext::Clip(const VertexOut& v)
{
	//cvv为 x-1,1  y-1,1  z0,1
	if (v.posH.x >= -v.posH.w && v.posH.x <= v.posH.w &&
		v.posH.y >= -v.posH.w && v.posH.y <= v.posH.w &&
		v.posH.z >= 0.f && v.posH.z <= v.posH.w)
	{
		return true;
	}
	return false;
}

//转到齐次裁剪空间
VertexOut Tiny3DDeviceContext::TransformToProj(const VertexIn& v)
{
	VertexOut out = m_pShader->VS(v);
	//设置oneDivZ
	out.oneDivZ = 1 / out.posH.w;
	//由于1/z和x,y成线性关系
	//这里将需要插值的信息都乘以1/z 得到 s/z和t/z等，方便光栅化阶段进行插值
	out.color.x *= out.oneDivZ;
	out.color.y *= out.oneDivZ;
	out.color.z *= out.oneDivZ;

	out.normal.x *= out.oneDivZ;
	out.normal.y *= out.oneDivZ;
	out.normal.z *= out.oneDivZ;

	out.tex.u *= out.oneDivZ;
	out.tex.v *= out.oneDivZ;

	return out;
}

//转换到屏幕坐标
void Tiny3DDeviceContext::TransformToScreen(const ZCMatrix& m, VertexOut& v)
{
	v.posH = v.posH * m;
}

//背面消隐
bool Tiny3DDeviceContext::BackFaceCulling(const VertexIn& v1, const VertexIn& v2, const VertexIn& v3)
{
	//线框模式不进行背面消隐
	if (m_renderMode == TINY3D_FILL_WIREFRAME)
	{
		return true;
	}
	else
	{
		ZCVector vector1 = v2.pos - v1.pos;
		ZCVector vector2 = v3.pos - v2.pos;
		//顶点缓存中顺序为顺时针
		//叉积得到的方向与右手系一致
		ZCVector normal = vector1.Cross(vector2);

		ZCVector viewDir = v1.pos - m_cameraPos;
		if (normal.Dot(viewDir) < 0)
		{
			return true;
		}
		return false;
	}
}

//画三角形
void Tiny3DDeviceContext::DrawTriangle(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	//线框模式
	if (m_renderMode == TINY3D_FILL_WIREFRAME)
	{
		BresenhamDrawLine(v1.posH.x, v1.posH.y, v2.posH.x, v2.posH.y);
		BresenhamDrawLine(v1.posH.x, v1.posH.y, v3.posH.x, v3.posH.y);
		BresenhamDrawLine(v2.posH.x, v2.posH.y, v3.posH.x, v3.posH.y);
	}
	else if (m_renderMode == TINY3D_FILL_SOLIDE)
	{
		TriangleRasterization(v1, v2, v3);
	}

}

//bresenham画线
void Tiny3DDeviceContext::BresenhamDrawLine(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int stepx = 1;
	int stepy = 1;

	if (dx >= 0)
	{
		stepx = 1;
	}
	else
	{
		stepx = -1;
		dx = abs(dx);
	}

	if (dy >= 0)
	{
		stepy = 1;
	}
	else
	{
		stepy = -1;
		dy = abs(dy);
	}

	int deltaX = 2 * dx;
	int deltaY = 2 * dy;
	if (dx > dy)
	{
		int error = deltaY - dx;
		for (int i = 0; i <= dx; ++i)
		{
			if(x1 >= 0 && x1 < m_pDevice->GetClientWidth() && y1 >= 0 && y1 < m_pDevice->getClientHeight())
				m_pDevice->DrawPixel(x1, y1, ZCVector(0.f, 0.f, 0.f,1.f));
			if (error >= 0)
			{
				error -= deltaX;
				y1 += stepy;
			}
			error += deltaY;
			x1 += stepx;
		}
	}
	else
	{
		int error = deltaX - dy;
		for (int i = 0; i <= dy; i++)
		{
			if (x1 >= 0 && x1 < m_pDevice->GetClientWidth() && y1 >= 0 && y1 < m_pDevice->getClientHeight())
				m_pDevice->DrawPixel(x1, y1, ZCVector(0.f, 0.f, 0.f,1.f));
			if (error >= 0)
			{
				error -= deltaY;
				x1 += stepx;
			}
			error += deltaX;
			y1 += stepy;
		}
	}
}

//扫描线填充
//left 左端点  right 右端点
void Tiny3DDeviceContext::ScanlineFill(const VertexOut& left, const VertexOut& right,  int yIndex)
{
	float dx = right.posH.x - left.posH.x;

	for (float x = left.posH.x; x <= right.posH.x; x += 1.f)
	{
		//四舍五入
		int xIndex = static_cast<int>(x + .5f);
		
		if(xIndex >= 0 && xIndex < m_pDevice->GetClientWidth())
		{
			//插值系数
			float lerpFactor = 0;
			if (dx != 0)
			{
				lerpFactor = (x - left.posH.x) / dx;
			}

			//深度测试
			//1/z’与x’和y'是线性关系的
			float oneDivZ = MathUtil::Lerp(left.oneDivZ, right.oneDivZ, lerpFactor);
			if (oneDivZ >= m_pDevice->GetZ(xIndex,yIndex))
			{
				m_pDevice->SetZ(xIndex, yIndex, oneDivZ);

				float w = 1 / oneDivZ;
				//插值顶点 原先需要插值的信息均乘以oneDivZ
				//现在得到插值后的信息需要除以oneDivZ得到真实值
				VertexOut out = MathUtil::Lerp(left, right, lerpFactor);
				out.posH.y = yIndex;
				out.tex.u *= w;
				out.tex.v *= w;
				out.normal.x *= w;
				out.normal.y *= w;
				out.normal.z *= w;
				out.color.x *= w;
				out.color.y *= w;
				out.color.z *= w;
				//画像素点颜色
				m_pDevice->DrawPixel(xIndex, yIndex, m_pShader->PS(out));
			}			
		}	
	}
}

//画平顶三角形 v3为下顶点
//y方向每次增加一个像素 根据y插值顶点

void Tiny3DDeviceContext::DrawTriangleTop(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	float dy = 0;//每次y增加一个像素
	for (float y = v1.posH.y; y <= v3.posH.y; y += 1.f)
	{
		//四舍五入
		int yIndex = static_cast<int>(y + 0.5f);
		if (yIndex >= 0 && yIndex < m_pDevice->getClientHeight())
		{
			float t = dy / (v3.posH.y - v1.posH.y);

			//插值生成左右顶点
			VertexOut new1 = MathUtil::Lerp(v1, v3, t);
			VertexOut new2 = MathUtil::Lerp(v2, v3, t);
			dy += 1.f;
			//扫描线填充
			if (new1.posH.x < new2.posH.x)
			{
				ScanlineFill(new1, new2, yIndex);
			}
			else
			{
				ScanlineFill(new2, new1, yIndex);
			}
		}
		
	}
}

//画平底三角形 v1为上顶点
void Tiny3DDeviceContext::DrawTriangleBottom(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	float dy = 0;//每次y增加一个像素
	for (float y = v1.posH.y; y <= v2.posH.y; y += 1.f)
	{
		//四舍五入
		int yIndex = static_cast<int>(y + 0.5f);

		if (yIndex >= 0 && yIndex < m_pDevice->getClientHeight())
		{
			float t = dy / (v2.posH.y - v1.posH.y);

			//插值左右顶点
			VertexOut new1 = MathUtil::Lerp(v1, v2, t);
			VertexOut new2 = MathUtil::Lerp(v1, v3, t);
			dy += 1.f;

			//扫描线填充
			if (new1.posH.x < new2.posH.x)
			{
				ScanlineFill(new1, new2, yIndex);
			}
			else
			{
				ScanlineFill(new2, new1, yIndex);
			}
		}
	}
}

//光栅化三角形
void Tiny3DDeviceContext::TriangleRasterization(const VertexOut& v1, const VertexOut& v2, const VertexOut& v3)
{
	//判断是否是平底或者平顶三角形
	if (v1.posH.y == v2.posH.y)
	{	
		if (v1.posH.y < v3.posH.y)
		{//平顶
			DrawTriangleTop(v1, v2, v3);
		}
		else
		{//平底
			DrawTriangleBottom(v3, v1, v2);
		}
	}
	else if (v1.posH.y == v3.posH.y)
	{
		if (v1.posH.y < v2.posH.y)
		{//平顶
			DrawTriangleTop(v1, v3, v2);
		}
		else
		{//平底
			DrawTriangleBottom(v2, v1, v3);
		}
	}
	else if (v2.posH.y == v3.posH.y)
	{
		if (v2.posH.y < v1.posH.y)
		{//平顶
			DrawTriangleTop(v2, v3, v1);
		}
		else
		{//平底
			DrawTriangleBottom(v1, v2, v3);
		}
	}
	//一般三角形 将其分割成平底三角形和平顶三角形
	else
	{
		//根据y值将三个顶点排序
		std::vector<VertexOut> vertices{v1,v2,v3};
		std::sort(vertices.begin(), vertices.end(), [](VertexOut v1,VertexOut v2) {
			return v1.posH.y < v2.posH.y;});
		VertexOut top = vertices[0];
		VertexOut middle = vertices[1];
		VertexOut bottom = vertices[2];

		//插值求中间点
		float middleX = (middle.posH.y - top.posH.y) * (bottom.posH.x - top.posH.x) /
			(bottom.posH.y - top.posH.y) + top.posH.x;
		float dy = middle.posH.y - top.posH.y;
		float t = dy / (bottom.posH.y - top.posH.y);
		
		VertexOut newMiddle = MathUtil::Lerp(top, bottom, t);
		newMiddle.posH.x = middleX;
		newMiddle.posH.y = middle.posH.y;

		//平顶
		DrawTriangleTop(middle, newMiddle, bottom);
		//平底
		DrawTriangleBottom(top, middle, newMiddle);
	}
}

