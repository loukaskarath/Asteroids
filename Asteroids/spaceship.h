#pragma once
#include "gameobject.h"
#include "config.h"
#include "laser.h"

class Spaceship : public GameObject, public Collidable
{
	float speed = 3.0f;
	float pos_x = CANVAS_WIDTH / 2;
	float pos_y = CANVAS_HEIGHT / 2;
	float height = 1.0f;
	float life = 1.0f;
public:
	Spaceship(const class Game& mygame);
	void update() override;
	void draw();
	void init();
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	Disk getCollisionHull() const override;
	float getRemainingLife() const { return life; }
	void drainLife(float amount) { life = std::max<float>(0.0f, life - amount); }
};