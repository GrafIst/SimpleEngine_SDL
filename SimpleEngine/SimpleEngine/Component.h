#pragma once

class Actor;
//Forward declaration of Actor. Because Actor.h will include Compnent.h
//Component.h cannot include Actor.h. So we forward-declare Actor, and
//will include Actor.h in Component.cpp file.

class Component
{
public:
	Component(Actor* ownerP, int updateOrderP = 100);
	Component() = delete; //on delete le constructor par défaut
	virtual ~Component(); //virtual pour gérer l'héritage
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }

	virtual void update(float dt); //virtual pour gérer l'héritage

protected:
	Actor& owner;
	int updateOrder;
};

