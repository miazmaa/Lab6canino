#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_font.h>
#include "arrow.h";
#include "bullet.h"

int main(void)
{
	arrowClass arrow;
	int score = 0;
	bool redraw = true;
	const int FPS = 60;
	int timeLeft = 30;
	//variables
	int width = 640;
	int height = 520;
	bool done = false;
	int gameHeight = 480; //keeps gameplay inside the 480 display 

	//allegro variable
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_TIMER* game_timer = NULL;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);	//create our display object
	bullet mybullet[10];
	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	arrow.create_arrow_bitmap(display);
	ALLEGRO_FONT* boldFont = al_load_font("bold.ttf", 24, 0);

	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	game_timer = al_create_timer(1.0);
	al_register_event_source(event_queue, al_get_timer_event_source(game_timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	arrow.drawArrow();
	al_flip_display();
	al_start_timer(timer);
	al_start_timer(game_timer);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (ev.any.source == al_get_timer_event_source(game_timer))
			{
				timeLeft--;
				if (timeLeft <= 0)
				{
					done = true;
				}
			}
			else if (ev.any.source == al_get_timer_event_source(timer))
			{
				redraw = true;
				for (int i = 0; i < 10; i++)
				{
					if (!mybullet[i].getStatus()) {
						mybullet[i].fire();
					}
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_UP:
				arrow.up();
				break;
			case ALLEGRO_KEY_DOWN:
				arrow.down();
				break;
			case ALLEGRO_KEY_LEFT:
				arrow.left();
				break;
			case ALLEGRO_KEY_RIGHT:
				arrow.right();
				break;
			}
		}
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			if (arrow.getSpeed() != 0) {
				arrow.erase_arrow();
				arrow.move_arrow(width, gameHeight);
			}
			arrow.drawArrow();
			for (int i = 0;i < 10;i++)
			{
				if (mybullet[i].getStatus()) {
					score += mybullet[i].move_bullet(arrow.getX(), arrow.getY(), 32, 32, gameHeight);
				}
			}
		}
		al_draw_textf(boldFont, al_map_rgb(255, 255, 255), 0, 490, ALLEGRO_ALIGN_LEFT, "Score: %d", score);
		al_draw_textf(boldFont, al_map_rgb(255, 255, 255), width - 10, height - 30, ALLEGRO_ALIGN_RIGHT, "Time: %d", timeLeft);
		al_flip_display();
	}
	if (boldFont) {
		al_destroy_font(boldFont);
	}
	al_destroy_event_queue(event_queue);
	al_destroy_timer(game_timer);
	al_destroy_timer(timer);
	al_destroy_display(display);						//destroy our display object
	system("pause");
	return 0;
}