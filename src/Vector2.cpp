#include <CPhysics/Vector2.h>

namespace CPhysics
{
		Vector2::Vector2() : x(0), y(0) {}
		Vector2::Vector2(float x, float y) : x(x), y(y) {}
	

		float Vector2::length() const
		{
			return hypot(x, y);
		}

		Vector2 Vector2::Normalized() const
		{
			float len = length();
			if (len == 0) return Vector2(0, 0);
			return  Vector2(x/len , y/len);
		}

#pragma region Opertors
		Vector2 Vector2::operator+ (const Vector2& other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 Vector2::operator- (const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 Vector2::operator* (const float scaler) const
		{
			return Vector2(x * scaler, y * scaler);
		}

		Vector2 Vector2::operator/ (const float diviser) const
		{
			return Vector2(x / diviser, y / diviser);
		}

		void Vector2::operator+= (const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}

		void Vector2::operator-= (const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}

		void Vector2::operator*= (const float scaler)
		{
			x *= scaler;
			y *= scaler;
		}

		void Vector2::operator/= (const float diviser)
		{
			x /= diviser;
			y /= diviser;
		}
#pragma endregion

#pragma region staticMathMethods

		const float Vector2::Dot(const Vector2& a, const Vector2& b)
		{
			return a.x * b.x + a.y * b.y;
		}

		const float Vector2::Distance(const Vector2& a, const Vector2& b) 
		{
			return (a - b).length();
		}

		const Vector2 Vector2::RotateAboutPoint(const Vector2& point, const Vector2& pivot, float angle) 
		{
			angle = angle * 3.14159265f / 180.0f; 
			float s = sin(angle);
			float c = cos(angle);
			Vector2 translated = point - pivot;
			float xnew = translated.x * c - translated.y * s;
			float ynew = translated.x * s + translated.y * c;
			return Vector2(xnew, ynew) + pivot;
		}

		const Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
		{
			return a + (b - a) * t;
		}




#pragma endregion


	

}