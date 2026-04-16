#pragma once
#include <cmath>

namespace CPhysics
{
	struct Vector2
	{
		float x, y;

		float length() const
		{
			return hypot(x, y);
		}

		Vector2 Normalized() const
		{
			float len = length();
			return  Vector2(x/len , y/len);
		}

		Vector2 Perpendicular() const 
		{
			return Vector2(-y, x);
		}

#pragma region Opertors
		Vector2 operator+ (const Vector2& other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator- (const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator* (const float scaler) const
		{
			return Vector2(x * scaler, y * scaler);
		}

		Vector2 operator/ (const float diviser) const
		{
			return Vector2(x / diviser, y / diviser);
		}

		void operator+= (const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

		void operator-= (const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		void operator*= (const float scaler)
		{
			x *= scaler;
			y *= scaler;
		}

		void operator/= (const float diviser)
		{
			x /= diviser;
			y /= diviser;
		}
#pragma endregion

#pragma region staticMathMethods

		static float Dot(const Vector2& a, const Vector2& b)
		{
			return a.x * b.x + a.y * b.y;
		}

		static float Distance(const Vector2& a, const Vector2& b) 
		{
			return (a - b).length();
		}



#pragma endregion


	};

}