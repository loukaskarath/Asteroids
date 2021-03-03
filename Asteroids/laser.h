#pragma once
#include "gameobject.h"
#include "config.h"
#include "scancodes.h"
#include "spaceship.h"

class Laser : public GameObject, public Collidable
{
private:
	float speed = 3.0f;
	float pos_x = (CANVAS_WIDTH / 2) + 50, pos_y = (CANVAS_HEIGHT / 2);
	bool laser_active = false;
public:
	void update() override;
	void draw() override;
	void init()	override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	Laser(const class Game& mygame);
	~Laser();
	bool isLaserActive() { return laser_active; }
	Disk getCollisionHull() const override;
};