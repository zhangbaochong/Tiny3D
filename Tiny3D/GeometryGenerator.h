#pragma once
#include "ZCMath.h"

class GeometryGenerator
{
private:
	GeometryGenerator() {}

public:
	//单例模式
	static GeometryGenerator* GetInstance()
	{
		static GeometryGenerator instance;
		return &instance;
	}

	//基本网络结构：顶点集合+索引集合
	struct MeshData
	{
		std::vector<VertexIn>	vertices;
		std::vector<UINT>	indices;
	};

	//创建一个立方体：指定宽(X方向)、高(Y方向)、深(Z方向)
	void CreateBox(float width, float height, float depth, MeshData &mesh);
};

