#pragma once

#include <windows.h>
#include <algorithm>
#include "ZCMath.h"

namespace Lights {
	//平行光
	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(this)); }

		ZCVector ambient;	//环境光
		ZCVector diffuse;	//漫反射光
		ZCVector specular;	//高光
		ZCVector direction;	//光照方向
	};
	/*
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
	*/
	//材质
	struct Material
	{
		Material() { ZeroMemory(this, sizeof(this)); }

		ZCVector ambient;
		ZCVector diffuse;
		ZCVector specular;//w表示高光强度
		ZCVector reflect;
	};

	//计算平行光
	inline void ComputeDirectionalLight(
		const Material& mat,				//材质
		const DirectionalLight& L,		//平行光
		ZCVector normal,					//顶点法线
		ZCVector toEye,					//顶点到眼睛的向量
		ZCVector& ambient,				//计算结果:环境光
		ZCVector& diffuse,				//计算结果:漫反射光
		ZCVector& spec)					//计算结果:高光
	{
		// 结果初始化为0
		ambient = ZCVector( 0.0f, 0.0f, 0.0f, 0.0f );
		diffuse = ZCVector(0.0f, 0.0f, 0.0f, 0.0f);
		spec = ZCVector(0.0f, 0.0f, 0.0f, 0.0f);

		// 光线方向
		ZCVector lightVec = -L.direction;
		// 环境光直接计算
		ambient = mat.ambient * L.ambient;

		// 计算漫反射系数
		//光线、法线方向归一化
		lightVec.Normalize();
		float diffuseFactor = lightVec.Dot(normal);
		// 顶点背向光源不再计算

		if (diffuseFactor > 0.0f)
		{
			//入射光线关于法线的反射向量
			ZCVector v = MathUtil::Reflect(-lightVec, normal);

			float specFactor = pow(max(v.Dot(toEye), 0.0f), mat.specular.w);

			//计算漫反射光
			diffuse = mat.diffuse * L.diffuse * diffuseFactor;
			//计算高光
			spec = mat.specular * L.specular * specFactor;
		}
	}
}


