#pragma once

#include <windows.h>
#include "ZCVector.h"

namespace Lights {
	//平行光
	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(this)); }

		ZCVector ambient;	//环境光
		ZCVector diffuse;	//漫反射光
		ZCVector specular;	//高光
		ZCFLOAT3 direction;	//光照方向
		float pad;			//用于与HLSL中“4D向量”对齐规则匹配
	};
	//点光源
	struct PointLight
	{
		PointLight() { ZeroMemory(this, sizeof(this)); }

		ZCVector ambient;
		ZCVector diffuse;
		ZCVector specular;

		// Packed into 4D vector: (Position, Range)
		ZCFLOAT3 position;//光源位置
		float range;      //光照范围

						  // Packed into 4D vector: (A0, A1, A2, Pad)
		ZCFLOAT3 att;     //衰减系数
		float pad; // Pad the last float so we can set an array of lights if we wanted.
	};
	//聚光灯
	struct SpotLight
	{
		SpotLight() { ZeroMemory(this, sizeof(this)); }

		ZCVector ambient;
		ZCVector diffuse;
		ZCVector specular;

		// Packed into 4D vector: (Position, Range)
		ZCFLOAT3 position;//光照位置
		float range;      //光照范围

						  // Packed into 4D vector: (Direction, Spot)
		ZCFLOAT3 direction;//光照方向
		float spot;        //光照强度系数   

						   // Packed into 4D vector: (Att, Pad)
		ZCFLOAT3 att;      //衰减系数
		float pad; // Pad the last float so we can set an array of lights if we wanted.
	};
	//材质
	struct Material
	{
		Material() { ZeroMemory(this, sizeof(this)); }

		ZCVector ambient;
		ZCVector diffuse;
		ZCVector specular;//w表示高光强度
		ZCVector reflect;
	};

}


