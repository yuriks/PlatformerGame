#pragma once
#include "Position.hpp"
#include "vec2.hpp"

struct SpriteBuffer;
struct Camera;

struct Bullet {
	Position pos;
	float angle;
	vec2 vel;

	void draw(SpriteBuffer& sprite_buffer, const Camera& camera) const;
	void update();
};
