#include "RectangleCollisionComponent.h"
#include "Actor.h"

RectangleCollisionComponent::RectangleCollisionComponent(Actor* owner) : 
	Component(owner), 
	hitbox(new Rectangle{0,0,0,0})
{
	
}

void RectangleCollisionComponent::setHitbox(float xP, float yP, float widthP, float heightP)
{
	hitbox->x = xP;
	hitbox->y = yP;
	hitbox->width = widthP;
	hitbox->height = heightP;
}

const Vector2 RectangleCollisionComponent::getCenter() const
{
	return owner.getPosition();
}

bool AABBCollision(const Rectangle& rectA, const Rectangle& rectB) {
	int xMinA = rectA.x;
	int xMaxA = rectA.x + rectA.width;
	int yMinA = rectA.y;
	int yMaxA = rectA.y + rectA.height;
	int xMinB = rectB.x;
	int xMaxB = rectB.x + rectB.width;
	int yMinB = rectB.y;
	int yMaxB = rectB.y + rectB.height;
	bool isOutside = xMinA > xMaxB || xMaxA < xMinB || yMinA > yMaxB || yMaxA < yMinB;
	return !isOutside;
}

