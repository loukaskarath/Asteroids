#pragma once
#include "gameobject.h"
#include "graphics.h"

class Meteorite : public GameObject
{
private:
	float pos_x, pos_y;
	float speed, size, rotation;
	class graphics::Brush brush;
	bool active = true;
public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Meteorite(const class Game& mygame);
	~Meteorite();
	Disk getCollisionHull() const;
};
