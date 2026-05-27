#include "arrow.h"
arrowClass::arrowClass()
{
	speed = 0;
	x = 100;
	y = 100;
	dir = 1;
	score = 0;
	for (int i = 0; i < 4; i++)
	{
		arrow_bmp[i] = NULL;
	}
}
arrowClass::~arrowClass()
{
	for (int i = 0; i < 4; i++)
	{
		al_destroy_bitmap(arrow_bmp[i]);
	}
}
void arrowClass::drawArrow()
{
	al_draw_bitmap(arrow_bmp[getDirection()], getX(), getY(), 0);
}
void arrowClass::create_arrow_bitmap(ALLEGRO_DISPLAY* display)
{
	for (int i = 0;i < 4; i++)
	{
		arrow_bmp[i] = al_create_bitmap(64, 64);
		if (!arrow_bmp[i]) {
			exit(1);
			al_destroy_display(display);

		}

		al_set_target_bitmap(arrow_bmp[i]);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		
		int x = 15;
		int y = 15;
		al_draw_filled_ellipse(32, 32, 22, 16, al_map_rgb(255, 255, 255));
		al_draw_filled_circle(32, 32, 10, al_map_rgb(93, 63, 211));
		al_draw_filled_rectangle(29, 29, 35, 35, al_map_rgb(0, 0, 0));
		switch (i)
		{
		case 0: // Up 
			al_draw_filled_triangle(32, 2, 24, 18, 40, 18, al_map_rgb(0, 0, 255));
			break;
		case 1: // Right
			al_draw_filled_triangle(62, 32, 46, 24, 46, 40, al_map_rgb(0, 0, 255));
			break;
		case 2: // Down 
			al_draw_filled_triangle(32, 62, 24, 46, 40, 46, al_map_rgb(0, 0, 255));
			break;
		case 3: // Left
			al_draw_filled_triangle(2, 32, 18, 24, 18, 40, al_map_rgb(0, 0, 255));
			break;
		}
	}
}
void arrowClass::erase_arrow()
{

	int left = x;
	int top = y;
	int right = x + 64;
	int bottom = y + 64;

	al_draw_filled_rectangle(left, top, right, bottom, al_map_rgb(0, 0, 0));
}

void arrowClass::up()
{
	dir = 0;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;
}

void arrowClass::down()
{
	dir = 2;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}


void arrowClass::left()
{
	dir = 3;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}

void arrowClass::right()
{
	dir = 1;
	speed++;
	if (speed > MAXSPEED)
		speed = MAXSPEED;

}
int arrowClass::getDirection()
{
	return dir;
}
int arrowClass::getSpeed()
{
	return speed;
}
int arrowClass::getX()
{
	return x;
}
int arrowClass::getY()
{
	return y;
}
void arrowClass::move_arrow(int width, int height)
{

	//update arrow position based on direction
	switch (dir)
	{
	case 0:
		y -= speed;
		break;
	case 1:
		x += speed;
		break;
	case 2:
		y += speed;
		break;
	case 3:
		x -= speed;
	}

	//keep arrow inside the screen
	if (x > width - 32)
	{
		x = width - 32;
		speed = 0;
	}
	if (x < 0)
	{
		x = 0;
		speed = 0;
	}
	if (y > height - 64)
	{
		y = height - 64;
		speed = 0;
	}
	if (y < 0)
	{
		y = 0;
		speed = 0;
	}
}