#pragma once
#include "Component.h"
#include "Rectangle.h"
#include "Vector2.h"

class RectangleCollisionComponent : public Component
{
public:
	RectangleCollisionComponent(Actor* owner);
	RectangleCollisionComponent() = delete;
	RectangleCollisionComponent(const RectangleCollisionComponent&) = delete;
	RectangleCollisionComponent& operator=(const RectangleCollisionComponent&) = delete;

	Rectangle* getHitbox() const { return hitbox; };
	void setHitbox(float x, float y, float width, float height);

	const Vector2 getCenter() const;

private:
	Rectangle* hitbox;
};

bool AABBCollision(const Rectangle& rectA, const Rectangle& rectB);

