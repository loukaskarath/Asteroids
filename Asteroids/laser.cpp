#include "laser.h"
#include "game.h"
#include "graphics.h"

Laser::Laser(const Game& mygame)
	:GameObject(mygame)
{
}

void Laser::update()
{

	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		pos_x -= speed * graphics::getDeltaTime() / 20.0f;

	}
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		pos_x += speed * graphics::getDeltaTime() / 20.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		pos_y -= speed * graphics::getDeltaTime() / 20.0f;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		pos_y += speed * graphics::getDeltaTime() / 20.0f;
	}

	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		pos_x += speed * graphics::getDeltaTime() * 2.0f;
	}



	if (pos_x < 0) pos_x = 0;
	if (pos_y < 0) pos_y = 0;

}

void Laser::draw()
{
	graphics::Brush b;

	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime());
	b.texture = "";
	b.fill_color[0] = 1.0f;
	b.fill_color[1] = 0.5f + glow * 0.5f;
	b.fill_color[2] = 0.0f;
	b.outline_opacity = 0.0f;

	//secondary color
	b.fill_secondary_color[0] = 0.3f;
	b.fill_secondary_color[1] = 0.1f;
	b.fill_secondary_color[2] = 0.0f;

	//opacity
	b.fill_opacity = 3.0f;
	b.fill_secondary_opacity = 0.0f;
	b.gradient = true;


	graphics::drawDisk(pos_x, pos_y, 20, b); //laser beam
	graphics::resetPose();
}

void Laser::init()
{
	
}

Laser::~Laser()
{

}

Disk Laser::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}
