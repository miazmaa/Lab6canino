#include "bullet.h"
bullet::bullet()
{
	srand(time(0));
	alive = false;;
	bulletBitmap = al_create_bitmap(16, 16);
	ALLEGRO_BITMAP* storage = al_get_target_bitmap();
	al_set_target_bitmap(bulletBitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_rectangle(2, 2, 14, 14, al_map_rgb(70, 0, 70), 1);
	al_draw_line(0,0,15,15, al_map_rgb(12, 72, 153), 5);
	al_set_target_bitmap(storage);

}
bool bullet::getStatus()
{
	return alive;
}

void bullet::fire()
{
	x = rand() % 615 + 10;
	y = 10;
	alive = true;

}
void bullet::erase_bullet()
{
	al_draw_filled_rectangle(x, y, x + 16, y + 16, al_map_rgb(0, 0, 0)); //black color
}
int bullet::move_bullet(int arrowX, int arrowY, int width, int length, int gameHeight)
{
	y++;

	if (y > gameHeight - 16) {
		erase_bullet();
		alive = false;
		return 0;
	}
	al_draw_bitmap(bulletBitmap, x, y, 0);


	if (x > arrowX && x < arrowX + width && y > arrowY && y < arrowY + length) {
		alive = false;
		return 1;
	}

	return 0;
}