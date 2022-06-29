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

	double bestDot = 0.0;
	int bestId = 0;

	int curId = 0;
	for (auto& point : points_)
	{
		if (const double curDot = Vector2D::DotProduct(dir, point); curDot > bestDot)
		{
			bestDot = curDot;
			bestId = curId;
		}

		curId++;
	}

	return points_[bestId];
}

std::vector<Vector2D> ConvexShape::GetEdges(const int pointId)
{
	auto pointsInEdge = std::vector<Vector2D>();

	const int size = static_cast<int>(points_.size());

	pointsInEdge.emplace_back(points_[(pointId - 1 + size) % size]);
	pointsInEdge.emplace_back(points_[pointId]); 
	pointsInEdge.emplace_back(points_[(pointId + 1 + size) % size]);

	return pointsInEdge;
}

std::vector<Vector2D> ConvexShape::GetEdges(const Vector2D point)
{
	return GetEdges(GetPointId(point));
}

int ConvexShape::GetPointId(const Vector2D point) const
{
	int id = 0;

	//Find the point
	for (auto element : points_)
	{
		if (point == element)
		{
			//Stop searching for point
			break;
		}

		//Increment each loop
		id++;
	}

	return id;
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

	//Find left-most point (since it's going to be necessaraly a part of our new shape)
	double bestX = INFINITY;
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

	//rotate around pivot and select the first point when rotating clockwise untile we've made a full loop
	int curPivotId = firstPivotId;
	int nextPivotId = 0;
	Vector2D curDirection(-1.0, 0.0);
	do
	{
		//Compare every point and find next pivot
		double smallestAngle = INFINITY;
		
		for (int id = 0; id < static_cast<int>(points_.size()); id++)
		{
			if (id == curPivotId)
				continue;

			const Vector2D v1 = curDirection;
			const Vector2D v2 = points_[id] - points_[curPivotId];

			if (const double angle = v1.AngleClockwiseWith(v2); angle < smallestAngle)
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
	} while (nextPivotId != firstPivotId);

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
	double furthest = 0.0;
	for (auto element : points_)
	{
		if (const double distance = element.Magnitude(); distance > furthest)
			furthest = distance;
	}
	boundingCircleRadius_ = furthest;
}
