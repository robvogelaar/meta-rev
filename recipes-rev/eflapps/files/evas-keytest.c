#include <Ecore_Evas.h>
#include <Ecore.h>
#include <stdio.h>

#define WIDTH 100
#define HEIGHT 100

Ecore_Evas  *   ee;
Evas        *   evas;
Evas_Object *   base_rect;

static int main_signal_exit(void *data, int ev_type, void *ev)
{
        fprintf(stderr, "main_signal_exit\n");
        ecore_main_loop_quit();
        return 1;
}

void key_down(void *data, Evas *e, Evas_Object *obj, void *event_info) 
{
        fprintf(stderr, "key_down\n");
        Evas_Event_Key_Down *ev;

        ev = (Evas_Event_Key_Down *)event_info;
        printf("You hit key: %s\n", ev->keyname);
}

int main()
{
        ecore_init();
	ecore_evas_init();

        ecore_event_handler_add(ECORE_EVENT_SIGNAL_EXIT, 
			main_signal_exit, NULL);

        //ee = ecore_evas_software_x11_new(NULL, 0,  0, 0, WIDTH, HEIGHT);
        ee = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);
        if (!ee)
                goto panic;

        ecore_evas_title_set(ee, "EVAS KeyBind Example");
        ecore_evas_borderless_set(ee, 0);
        ecore_evas_show(ee);

        evas = ecore_evas_get(ee);

        base_rect = evas_object_rectangle_add(evas);
        evas_object_resize(base_rect, WIDTH, HEIGHT);
        evas_object_color_set(base_rect, 0, 0, 0, 255);
        evas_object_focus_set(base_rect, 1);
        evas_object_show(base_rect);

        evas_object_event_callback_add(base_rect, 
			EVAS_CALLBACK_KEY_DOWN, key_down, NULL);      

        ecore_main_loop_begin();
        
        ecore_evas_shutdown();
        ecore_shutdown();

        return 0;
panic:
        fprintf(stderr, "You got to have at least one evas engine built and linked"
                   " up to ecore-evas for this example to run properly.\n");
        return -2;
}
