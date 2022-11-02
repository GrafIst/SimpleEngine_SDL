#include "CircleCollisionComponent.h"
#include "Actor.h"
#include "Log.h"

CircleCollisionComponent::CircleCollisionComponent(Actor* owner) :
	Component(owner), radius(1.0f)
{

}

float CircleCollisionComponent::getRadius() const
{
	return owner.getScale() * radius;
}

void CircleCollisionComponent::setRadius(float radiusP)
{
	radius = radiusP;
}

const Vector2 CircleCollisionComponent::getCenter() const
{
	return owner.getPosition();
}

bool Interesct(const CircleCollisionComponent& a, const CircleCollisionComponent& b)
{
	Vector2 aCenter = a.getCenter();
	Vector2 bCenter = b.getCenter();
	Vector2 ab = bCenter - aCenter;
	float distSq = ab.lengthSq();
	float sumOfRadius = a.getRadius() + b.getRadius();
	return distSq <= sumOfRadius * sumOfRadius;
}

bool IntersectWithRectangle(const CircleCollisionComponent& a, const RectangleCollisionComponent& b) {
	Vector2 aCenter = a.getCenter();
	Vector2 bCenter = b.getCenter();

	Vector2 ab = b.getCenter() - a.getCenter();

	float dotAB = Vector2::dot(ab, Vector2::unitY);

	float distSq = 0.0f;
	float sumOfRadius = 0.0f;


	if (fabs(dotAB) <= 0.5) // horizontal facing
	{
		float abx = bCenter.x - aCenter.x;
		distSq = abx * abx;
		sumOfRadius = a.getRadius() + ((b.getHitbox()->width - b.getHitbox()->x) / 2);

	}
	else if(fabs(dotAB) > 0.5) { // vertical facing
		//first on calcul la distance entre les deux centres Y
		float aby = bCenter.y - aCenter.y;
		distSq = aby * aby;
		//puis somme des hitbox
		sumOfRadius = a.getRadius() + ((b.getHitbox()->height - b.getHitbox()->y) / 2);
	}
	return distSq <= sumOfRadius * sumOfRadius;
	
}