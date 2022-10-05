#include "ConvexShape.h"

ConvexShape::ConvexShape(std::vector<Vector2D> points) : points_(std::move(points))
{
	ConvertToConvex();

	//Make sure our center corresponds with the center of the rigibody.
	RepositionCenter();
}

Vector2D ConvexShape::GetFurthestPoint(Vector2D dir) const
{
	dir = dir.Normalize();

	float bestDot = 0.0;
	int bestId = 0;

	int curId = 0;
	for (auto& point : points_)
	{
		if (const float curDot = Vector2D::DotProduct(dir, point); curDot > bestDot)
		{
			bestDot = curDot;
			bestId = curId;
		}

		curId++;
	}

	return points_[bestId];
}

void ConvexShape::InsertPoint(const Vector2D point, const int id)
{
	points_.insert(points_.begin() + id, point);

	ConvertToConvex();

	RepositionCenter();
}

void ConvexShape::ConvertToConvex()
{
	auto newPointsSet = std::vector<Vector2D>();

	//Find left-most point (since it's going to be necesseraly a part of our new shape as it's on the very edge)
	float bestX = INFINITY;
	int firstPivotId = 0;
	int curId = 0;
	for (const auto& point : points_)
	{
		if (point.X < bestX)
		{
			firstPivotId = curId;
			bestX = point.X;
		}

		curId++;
	}

	//Select the first point that we would find if we were drawing an infinite segment from our pivot
	//Rotating clockwise, the next pivot is the one with the smallest angle to our initial direction
	//We add each time the pivots to the list of points that constitute our convex shape as they lay on the outer edge.
	//We repeat this process until we're back at our initial point which closes our shape.
	//i.e we've made a complete loop with our direction vector
	int curPivotId = firstPivotId;
	int nextPivotId = 0;
	Vector2D curDirection(-1.0, 0.0);
	int it = 0;
	do
	{
		if (it++ > 5000)
			std::cout << "wat";
		//Compare every point and find next pivot
		float smallestAngle = INFINITY;
		
		for (int id = 0; id < static_cast<int>(points_.size()); id++)
		{
			if (id == curPivotId)
				continue;

			if (points_[id] == points_[curPivotId])
				continue;

			const Vector2D v1 = curDirection;
			const Vector2D v2 = points_[id] - points_[curPivotId];

			if (const float angle = v1.AngleClockwiseWith(v2); angle < smallestAngle)
			{
				nextPivotId = id;
				smallestAngle = angle;
			}
		}

		//Add next pivot to our list
		newPointsSet.emplace_back(points_[nextPivotId]);

		//Change pivot
		curDirection = points_[nextPivotId] - points_[curPivotId];
		curPivotId = nextPivotId;
	} while (nextPivotId != firstPivotId); //Check if we've finished finding points 

	points_ = newPointsSet;
}

void ConvexShape::RepositionCenter()
{
	//Calculate the current center of the shape
	Vector2D center;
	for (const auto& point : points_)
	{
		center += point;
	}

	center /= points_.size();

	//Repostion each point so that the center of the shape lies at 0;0
	for (auto& point : points_)
	{
		point -= center;
	}

	//Recalculate the boundingCircle
	float furthest = 0.0;
	for (auto element : points_)
	{
		if (const float distance = element.Magnitude(); distance > furthest)
			furthest = distance;
	}
	boundingCircleRadius_ = furthest;
}
