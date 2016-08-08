#include "stdafx.h"
#include "ZCVector.h"
#include "ZCMatrix.h"
#include "MathUtil.h"
#include <cmath>

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

using namespace System::Diagnostics;

using namespace MathUtil;
const float PI = 3.1415926f;

namespace UnitTest
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///获取或设置测试上下文，该上下文提供
		///有关当前测试运行及其功能的信息。
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		// 编写测试时，可以使用以下附加特性: 
		//
		// 在运行类中的第一个测试之前使用 ClassInitialize 运行代码
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		// 在类中的所有测试都已运行之后使用 ClassCleanup 运行代码
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//在运行每个测试之前，使用 TestInitialize 来运行代码
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//在每个测试运行完之后，使用 TestCleanup 来运行代码
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 
		
		[TestMethod]
		void V_CopyTest()
		{
			ZCVector v1(1, 2, 1);
			ZCVector v2(v1);
			ZCVector v3 = v1;
			Assert::IsTrue(v1 == v2 && v1 == v3);
		};

		[TestMethod]
		void V_DotTest()
		{
			ZCVector v1(1, 2, 1);
			ZCVector v2(2, 3, 0);
			float r1 = v1.Dot(v2);
			float espect = 8.0f;
			Assert::AreEqual(r1, espect);
		};

		[TestMethod]
		void V_CrossTest()
		{
			ZCVector v1(1, 2, 1);
			ZCVector v2(2, 3, 0);
			ZCVector v3 = v1.Cross(v2);
			ZCVector espect = ZCVector(-3, 2, -1);
			Assert::IsTrue(v3 == espect);
		};

		[TestMethod]
		void V_AddTest()
		{
			ZCVector v1(1, 2, 1);
			ZCVector v2(2, 3, 0);
			ZCVector v3 = v1 + v2;
			ZCVector espect = ZCVector(3, 5, 1);
			Assert::IsTrue(v3 == espect);
		};

		[TestMethod]
		void V_SubTest()
		{
			ZCVector v1(1, 2, 1);
			ZCVector v2(2, 2, 3);
			ZCVector v3 = v1 - v2;
			ZCVector espect = ZCVector(-1, 0, -2);
			Assert::IsTrue(v3 == espect);
		};

		[TestMethod]
		void V_ProductWithMTest()
		{
			ZCVector v1(3, 4, 0, 1);
			ZCMatrix m(1, 0, 1, 0,
					   0, 1, 0, 0,
					   0, 0, 1, 0,
					   0, 0, 2, 1);
			ZCVector r = v1 * m;
			ZCVector espect(3, 4, 5, 1);
			
			Assert::IsTrue(r == espect);
		};

		[TestMethod]
		void V_LengthTest()
		{
			ZCVector v1(1, 2, 1);
			float espect = sqrt(6);
			Assert::AreEqual(v1.Length(),espect);
		};

		[TestMethod]
		void V_NormalizeTest()
		{
			ZCVector v1(3, 4, 0.f);
			ZCVector i(0.6f, 0.8f, 0.f);
			Assert::IsTrue(v1.Normalize() == i);
		};

		// m1 === m2
		[TestMethod]
		void M_EqualTest()
		{
			ZCMatrix m1(1, 0, 1, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 2, 1);
			ZCMatrix m2(2, 1, 3, 0,
				1, 2, 0, 0,
				2, 1, 0, 1,
				0, 0, 0, 1);
			ZCMatrix m3(1, 0, 1, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 2, 1);
			Assert::IsTrue(m1 == m3);
			Assert::IsFalse(m1 == m2);
		};

		[TestMethod]
		void M_AddTest()
		{
			ZCMatrix m1(1, 0, 1, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 2, 1);
			ZCMatrix m2(2, 1, 3, 0,
				1, 2, 0, 0,
				2, 1, 0, 1,
				0, 0, 0, 1);
			ZCMatrix m3 = m1 + m2;
			ZCMatrix espect(3, 1, 4, 0,
				1, 3, 0, 0,
				2, 1, 1, 1,
				0, 0, 2, 2);
			Assert::IsTrue(m3 == espect);
		};

		//m1 = m2 - m3
		[TestMethod]
		void M_SubTest()
		{
			ZCMatrix m1(1, 0, 1, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 2, 1);
			ZCMatrix m2(2, 1, 3, 0,
				1, 2, 0, 0,
				2, 1, 0, 1,
				0, 0, 0, 1);
			ZCMatrix m3 = m1 - m2;
			ZCMatrix espect(-1, -1, -2, 0,
				-1, -1, 0, 0,
				-2, -1, 1, -1,
				0, 0, 2, 0);
			Assert::IsTrue(m3 == espect);
		};

		//m1 = m2 * m3
		[TestMethod]
		void M_ProductTest()
		{
			ZCMatrix m1(1, 0, 1, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 2, 1);
			ZCMatrix m2(2, 1, 3, 0,
				1, 2, 0, 0,
				2, 1, 0, 1,
				0, 0, 0, 1);
			ZCMatrix m3 = m1 * m2;
			ZCMatrix espect(4, 2, 3, 1,
				1, 2, 0, 0,
				2, 1, 0, 1,
				4, 2, 0, 3);
			Assert::IsTrue(m3 == espect);
		};

		//矩阵的行列式
		[TestMethod]
		void Math_DetTest()
		{
			ZCMatrix m1(1, 0, 0, 0,
				0, 2, 0, 0,
				0, 0, 4, 0,
				1, 2, 3, 1);
			float espect = 8.f;
			Assert::AreEqual(ZCMatrixDet(m1), espect);
		};

		//3*3矩阵的行列式
		[TestMethod]
		void Math_AdjElemTest()
		{
			float result = ZCMatrixAdjElem(
				5, 1, 4,
				3, 2, -1,
				-2, 0, 2
			);
			float espect = 32.f;
			Assert::AreEqual(result, espect);
		};

		//矩阵的逆
		[TestMethod]
		void Math_InverseTest()
		{
			ZCMatrix m1(1, 0, 0, 0,
				0, 2, 0, 0,
				0, 0, 4, 0,
				1, 2, 3, 1);
			ZCMatrix espect(
				1, 0, 0, 0,
				0, 0.5, 0, 0,
				0, 0, 0.25, 0,
				-1, -1, -0.75, 1
				);
			
			Assert::IsTrue(ZCMatrixInverse(m1) == espect);
		};

		//矩阵的平移缩放
		[TestMethod]
		void Math_ScalTranslateTest()
		{
			ZCVector point(0, 1, 0, 1);
			ZCVector vScale = point*ZCMatrixScaling(2, 2, 2);
			ZCVector result1(0, 2, 0, 1);
			Assert::IsTrue(vScale == result1);
			ZCVector vTrans = point*ZCMatrixTranslate(3, 4, 2);
			ZCVector result2(3, 5, 2, 1);
			Assert::IsTrue(vTrans == result2);
		};

		//旋转矩阵
		[TestMethod]
		void Math_RotateTest()
		{
			ZCVector point(1, 0, 1, 1);
			ZCVector espectRX(1, -1, 0, 1);
			ZCVector espectRY(1, 0, -1, 1);
			ZCVector espectRZ(0, 1, 1, 1);
			Assert::IsTrue(point*ZCMatrixRotationX(::PI / 2) == espectRX);
			Assert::IsTrue(point*ZCMatrixRotationY(::PI / 2) == espectRY);
			Assert::IsTrue(point*ZCMatrixRotationZ(::PI / 2) == espectRZ);
		};
		
		//ZCFLOAT3转UINT
		[TestMethod]
		void Math_ColorToUINTTest()
		{
			ZCVector color(1.f, 1.f, 0.f,1.f);
			UINT result = ColorToUINT(color);
			UINT espect = 16776960;
			Assert::AreEqual(result, espect);
			color = { 1.f, 1.f, 1.f };
			result = ColorToUINT(color);
			espect = 16777215;
			Assert::AreEqual(result, espect);
		};
	};
}
