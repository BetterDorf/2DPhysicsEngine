#include "PolygonShape.h"

PolygonShape::PolygonShape(std::vector<Vector2D> points) : points_(std::move(points))
{
	//Make sure our center corresponds with the center of the rigibody.
	RepositionCenter();
}

Vector2D PolygonShape::GetFurthestPoint(Vector2D dir) const
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

std::vector<Vector2D> PolygonShape::GetEdges(const int pointId)
{
	auto pointsInEdge = std::vector<Vector2D>();

	const int size = static_cast<int>(points_.size());

	pointsInEdge.emplace_back(points_[(pointId - 1 + size) % size]);
	pointsInEdge.emplace_back(points_[pointId]); 
	pointsInEdge.emplace_back(points_[(pointId + 1 + size) % size]);

	return pointsInEdge;
}

std::vector<Vector2D> PolygonShape::GetEdges(const Vector2D point)
{
	return GetEdges(GetPointId(point));
}

int PolygonShape::GetPointId(const Vector2D point) const
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

void PolygonShape::InsertPoint(const Vector2D point, const int id)
{
	points_.insert(points_.begin() + id, point);

	RepositionCenter();
}

void PolygonShape::RepositionCenter()
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
}
