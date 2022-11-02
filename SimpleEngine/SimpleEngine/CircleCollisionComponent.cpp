#include "CircleCollisionComponent.h"
#include "Actor.h"

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

	//si la collision a un rectangle en dessous de lui ou au dessus
	// TODO : left and right
	// 
	//first on calcul la distance entre les deux centres Y
	float aby = bCenter.y - aCenter.y;
	float distSq = aby * aby;

	//puis somme des hitbox
	float sumOfRadius = a.getRadius() + ((b.getHitbox()->height - b.getHitbox()->y) / 2);
	return distSq <= sumOfRadius * sumOfRadius;

}