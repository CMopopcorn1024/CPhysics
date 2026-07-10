#pragma once
#include "Vector2.h"
#include "Segment.h"
#include <cmath>
#include <array>

namespace CPhysics
{
	class CollisionObject;

	class Rectangle 
	{
	public:
		Vector2 topLeft, topRight, bottomLeft, bottomRight;
		
		Segment top, bottom, left, right;	

		float rotation = 0;

		std::array<Vector2, 4> getVertices() const;

		std::array<Segment, 4> getSegments() const;

		Rectangle() {};

		Rectangle(float x, float y, float width, float height, float rot = 0);

		Rectangle(Vector2 position, Vector2 size, float rotation = 0);

		void changePosition(Vector2 delta);

		void getMinMaxOnProjectionAxis(Vector2 axis, float& min, float& max) const;


		Vector2 getClosestPoint(Vector2 point)  const;

		Vector2 getPosition() const;

		Vector2 getSize() const { return size; }

		void setParent(CollisionObject* p) { parent = p; calculate(); }

		void calculate();


	private:

		CollisionObject* parent = nullptr;

		Vector2 origin, size;

	};
}
