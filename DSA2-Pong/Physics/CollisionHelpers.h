#ifndef COLLISIONHELPERS_H
#define COLLISIONHELPERS_H

#include <algorithm>
#include <Math/Point2.h>
#include <Math/Vector2.h>
#include <Physics/Ray.h>


namespace CollisionHelpers
{
	// determine the closest point on the AABB Bounding Shape
	// and clamps it to a point
	inline Point2 closestPointOnAABB(const Point2& point, const AABB& box)
	{
		Point2 closestPoint;

		Point2 min = box.getCenter() - box.getExtents();
		Point2 max = box.getCenter() + box.getExtents();
		
		// Clamp the point to the box
		for (UINT i = 0; i < 2; ++i)
		{
			float v = point.arr[i];
			
			v = Math::clamp(v, min.arr[i], max.arr[i]);
			
			closestPoint.arr[i] = v;
		}

		return closestPoint;
	}

	inline float distanceToAABBSquared(const Point2& point, const AABB& box)
	{
		float distSqr = 0.0f;
		
		Point2 min = box.getCenter() - box.getExtents();
		Point2 max = box.getCenter() + box.getExtents();
		
		// For each axis, accumulate excess distance outside box extents
		for (UINT i = 0; i < 2; ++i)
		{
			float v = point.arr[i];
			if (v < min.arr[i])
				distSqr += (min.arr[i] - v) * (min.arr[i] - v);
			if (v > max.arr[i])
				distSqr += (v - max.arr[i]) * (v - max.arr[i]);
		}

		return distSqr;
	}


	inline float distanceToAABBSquared(Point2& closestPoint, const Point2& point, const AABB& box)
	{
		float distSqr = 0.0f;
		
		Point2 min = box.getCenter() - box.getExtents();
		Point2 max = box.getCenter() + box.getExtents();
		
		closestPoint = closestPointOnAABB(point, box);
		distSqr = point.distanceToSquared(closestPoint);

		return distSqr;
	}

	// determines point based off the normal of the AABB
	inline Vector2 normalToPointOnAABB(const Point2& point, const AABB& box)
	{
		Vector2 normal;

		Point2 center = box.getCenter();
		Vector2 extents = box.getExtents();

		Vector2 hitDir = point - center;
		if (Math::fAbsEquals(hitDir.x, extents.x, 0.001f))
		{
			normal = Vector2(1.0f, 0.0f);
		}
		else if (Math::fAbsEquals(hitDir.x, -extents.x, 0.001f))
		{
			normal = Vector2(-1.0f, 0.0f);
		}
		else if (Math::fAbsEquals(hitDir.y, extents.y, 0.001f))
		{
			normal = Vector2(0.0f, 1.0f);
		}
		else if (Math::fAbsEquals(hitDir.y, -extents.y, 0.001f))
		{
			normal = Vector2(0.0f, -1.0f);
		}

		return normal;
	}

	inline bool intersectRayAABB(Point2& poi, float& t, const Ray& ray, const AABB& aabb)
	{
		t = 0.0f;
		float tMax = std::numeric_limits<float>::max();

		Point2 center = aabb.getCenter();
		Vector2 extents = aabb.getExtents();

		Point2 min = center - extents;
		Point2 max = center + extents;

		// For all sides of the AABB
		for (UINT i = 0; i < 2; ++i)
		{
			float originComp = ray.origin.arr[i];
			float directionComp = ray.direction.arr[i];
			float minComp = min.arr[i];
			float maxComp = max.arr[i];

			if (Math::fAbsEquals(directionComp, 0.0f, 0.005f))
			{
				// Ray is parallel, so there is no hit if the origin is not within the side
				if (originComp < minComp || originComp > maxComp)
				{
					return false;
				}
			}
			else
			{
				// Get the intersection values of the near and far planes of the side
				float inv = 1.0f / directionComp;
				float tNear = (minComp - originComp) * inv;
				float tFar = (maxComp - originComp) * inv;
				if (tNear > tFar)
				{
					std::swap(tNear, tFar);
				}

				// Find the intersection
				t = std::max(t, tNear);
				tMax = std::min(tMax, tFar);

				// No intersection
				if (t > tMax)
				{
					return false;
				}
			}
		}

		// Ray intersects all sides
		poi = ray.getPoint(t);
		return true;
	}
	
	inline bool intersectRayCircle(Point2& poi, float& t, const Ray& ray, const Circle& circle)
	{
		t = 0.0f;

		Vector2 vToOrigin = ray.origin - circle.getCenter();
		float b = 2 * ray.direction * vToOrigin;
		
		if (b >= 0.0f)
		{
			return false;
		}

		float c = vToOrigin * vToOrigin - (circle.getRadius() * circle.getRadius());

		float discriminant = b * b - 4 * c;

		// negative discriminant corresponds to ray missing sphere
		if(discriminant < 0.0f)
			return false;

		// Ray now found to intersect circle, compute smallest t value of intersection
		t = ( -b - sqrt(discriminant) ) * 0.5f;

		// If t is negative, ray started inside circle so clamp t to zero
		if (t < 0.0f)
			t = 0.0f;

		poi = ray.getPoint(t);
		return true;
	}

}; // CollisionHelpers


#endif // COLLISIONHELPERS_H
