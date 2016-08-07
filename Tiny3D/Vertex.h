#pragma once
#include "ZCVector.h"


//顶点信息 包括坐标，颜色，纹理坐标，法线等等
class VertexIn
{
public:
	//顶点位置
	ZCVector pos;
	//顶点颜色
	ZCVector color;
	//纹理坐标
	ZCFLOAT2 tex;
	//法线
	ZCVector normal;

	VertexIn() = default;
	VertexIn(ZCVector pos, ZCVector color, ZCFLOAT2 tex, ZCVector normal)
		:pos(pos), color(color), tex(tex), normal(normal) {}

	VertexIn(const VertexIn& rhs):pos(rhs.pos),color(rhs.color),tex(rhs.tex),normal(rhs.normal){}
};

//经过顶点着色器输出的结构
class VertexOut
{
public:
	//世界变换后的坐标
	ZCVector posTrans;
	//投影变换后的坐标
	ZCVector posH;
	//纹理坐标
	ZCFLOAT2 tex;
	//法线
	ZCVector normal;
	//颜色
	ZCVector color;
	//1/z用于深度测试
	float oneDivZ;

	VertexOut() = default;
	VertexOut(ZCVector posT, ZCVector posH, ZCFLOAT2 tex, ZCVector normal, ZCVector color, float oneDivZ)
		:posTrans(posT), posH(posH), tex(tex), normal(normal), color(color), oneDivZ(oneDivZ) {}

	VertexOut(const VertexOut& rhs) :posTrans(rhs.posTrans), posH(rhs.posH), tex(rhs.tex), normal(rhs.normal),
	color(rhs.color),oneDivZ(rhs.oneDivZ){}

	VertexOut& operator= (const VertexOut& rhs)
	{
		if (this == &rhs)
			return *this;
		this->normal = rhs.normal;
		this->posH = rhs.posH;
		this->posTrans = rhs.posTrans;
		this->tex = rhs.tex;
		this->color = rhs.color;
		this->oneDivZ = rhs.oneDivZ;
		return *this;
	}
};

