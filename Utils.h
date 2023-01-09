#pragma once
#include <iostream>
class Pathfinding;

namespace Utils
{
	struct Vector2 {
		float x{};
		float y{};

		Vector2() = default;
		Vector2(float _x, float _y) : x(_x), y(_y) {};

		Vector2& operator=(const Vector2& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		Vector2& operator-(const Vector2& other)
		{
			Vector2 newVector{};
			newVector.x = x - other.x;
			newVector.y = y - other.y;
			return newVector;
		}

		bool operator!=(const Vector2 other) const
		{
			if (x == other.x && y == other.y)
				return false;
			else return true;
		}

		bool operator==(const Vector2& other) const
		{
			return x == other.x && y == other.y;
		}

		Vector2& Normalize()
		{
			float length{ Length() };

			x /= length;
			y /= length;

			return *this;
		}

		float Length()
		{
			const float length{ std::sqrt((x * x) + (y * y)) };
			return length;		
		}
	};

	struct Rect {
		Vector2 startPos{};
		float width{};
		float height{};

		Rect() = default;
		Rect(Vector2 _startPos, float _width, float _height) : width(_width), height(_height), startPos(_startPos) {};

		Rect& operator=(const Rect& other)
		{
			startPos = other.startPos;
			width = other.width;
			height = other.height;
			return *this;
		}
	};

}

namespace Functions
{
	static bool IsPointInRect(Utils::Vector2 point, Utils::Rect rect)
	{
		if (point.x > rect.startPos.x && point.x < rect.startPos.x + rect.width)
		{
			if (point.y > rect.startPos.y && point.y < rect.startPos.y + rect.height)
			{
				return true;
			}
		}

		return false;
	};

}