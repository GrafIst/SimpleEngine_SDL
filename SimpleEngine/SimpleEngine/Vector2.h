#pragma once
struct Vector2
{
	float x {0};
	float y {0};

	Vector2() = default;
	Vector2(float xP, float yP) : x(xP), y(yP) {}

	static const Vector2 zero; //si static mais pas constante, je ne peux pas lui donner de valeur
	//si je veux la d�finir et qu'elle est static, je dois l'initaliser dans le cpp

	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	//friend function, can access private member of a class (here it's not useful)
	friend Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x - right.x, left.y - right.y);
	}

	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}
};