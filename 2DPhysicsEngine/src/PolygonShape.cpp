#include "PolygonShape.h"

PolygonShape::PolygonShape(std::vector<Vector2D> points) : points_(std::move(points))
{
	RepositionCenter();
}

Vector2D PolygonShape::GetFurthestPoint(const Vector2D dir) const
{
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
