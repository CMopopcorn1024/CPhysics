#pragma once
#include <cmath>

namespace CPhysics
{
	struct Vector2
	{
		Vector2();
		Vector2(float x, float y);
		float x, y;

		float length() const;

		Vector2 Normalized() const;

#pragma region Opertors
		Vector2 operator+ (const Vector2& other) const;

		Vector2 operator- (const Vector2& other) const;

		Vector2 operator* (const float scaler) const;

		Vector2 operator/ (const float diviser) const;

		void operator+= (const Vector2& other);

		void operator-= (const Vector2& other);

		void operator*= (const float scaler);

		void operator/= (const float diviser);
#pragma endregion

#pragma region staticMathMethods

		static const float Dot(const Vector2& a, const Vector2& b);

		static const float Distance(const Vector2& a, const Vector2& b);

		static const Vector2 RotateAboutPoint(const Vector2& point, const Vector2& pivot, float angle);

		static const Vector2 Lerp(const Vector2& a, const Vector2& b, float t);




#pragma endregion


	};

}