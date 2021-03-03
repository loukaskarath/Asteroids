#include "spaceship.h"
#include "game.h"
#include "graphics.h"

Spaceship::Spaceship(const Game& mygame)
	:GameObject(mygame)
{
}

void Spaceship::update()
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

	//do not travel off screen
	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;

}

void Spaceship::draw()
{

	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "spaceship_2.png";
	br.outline_opacity = 0.0f;

	graphics::setScale(height, height);
	graphics::drawRect(pos_x, pos_y, 100, 100, br);

	graphics::resetPose();

	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime());
	br.texture = "";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow * 0.5f;
	br.fill_color[2] = 0.0f;
	br.outline_opacity = 0.0f;

	//secondary color
	br.fill_secondary_color[0] = 0.3f;
	br.fill_secondary_color[1] = 0.1f;
	br.fill_secondary_color[2] = 0.0f;

	//opacity
	br.fill_opacity = 3.0f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;


	graphics::drawDisk(pos_x + 50, pos_y, 20, br); //laser beam
	graphics::resetPose();



	if (game.getDebugMode())
	{
		br.outline_opacity = 1.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, br);

	}

}

void Spaceship::init()
{
}

Disk Spaceship::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}
