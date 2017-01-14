#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define PACKAGE_EXAMPLES_DIR "."
#endif

#include <Ecore.h>
#include <Ecore_Evas.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>

#define WIDTH (1280)
#define HEIGHT (720)

const uint8_t HSVlights[61] = {
    0,   4,   8,   13,  17,  21,  25,  30,  34,  38,  42,  47,  51,
    55,  59,  64,  68,  72,  76,  81,  85,  89,  93,  98,  102, 106,
    110, 115, 119, 123, 127, 132, 136, 140, 144, 149, 153, 157, 161,
    166, 170, 174, 178, 183, 187, 191, 195, 200, 204, 208, 212, 217,
    221, 225, 229, 234, 238, 242, 246, 251, 255};

void trueHSV(int angle, uint8_t *red, uint8_t *green, uint8_t *blue) {
  if (angle < 60) {
    *red = 255;
    *green = HSVlights[angle];
    *blue = 0;
  } else if (angle < 120) {
    *red = HSVlights[120 - angle];
    *green = 255;
    *blue = 0;
  } else if (angle < 180) {
    *red = 0, *green = 255;
    *blue = HSVlights[angle - 120];
  } else if (angle < 240) {
    *red = 0, *green = HSVlights[240 - angle];
    *blue = 255;
  } else if (angle < 300) {
    *red = HSVlights[angle - 240], *green = 0;
    *blue = 255;
  } else {
    *red = 255, *green = 0;
    *blue = HSVlights[360 - angle];
  }
}

static const char *border_img_path = PACKAGE_EXAMPLES_DIR "/red.png";

static Evas_Object *bg, *box, *border;

static void signalHandler(int signum) {
  fprintf(stdout, "signalHandler: signum %d\n", signum);
  ecore_main_loop_quit();
}

static Eina_Bool _animate_scene(void *data) {
  static int angle = 0;
  static int x = 0;
  static int y = 0;
  static int posx = 1;
  static int posy = 1;
  uint8_t red, green, blue;

#define MAXX 1280 / 4
#define MAXY 720 / 4

  trueHSV(angle, &red, &green, &blue);
  evas_object_color_set(box, red, green, blue, 255);
  evas_object_move(box, x + 1280 / 4, y + 720 / 4);

  evas_object_show(box);
  angle = angle + 1;
  angle = angle % 360;

  if (posx) {
    x = x + 1;
  } else {
    x = x - 1;
  }

  if (posy) {
    y = y + 1;
  } else {
    y = y - 1;
  }

  if (x == MAXX) {
    posx = 0;
  }
  if (x == 0) {
    posx = 1;
  }
  if (y == MAXY) {
    posy = 0;
  }
  if (y == 0) {
    posy = 1;
  }

  return EINA_TRUE;
}

int main(void) {
  Ecore_Evas *ee;
  Evas *evas;
  char *data;
  Eina_List *engines, *l;
  int w, h;

  srand(time(NULL));

  if (!ecore_evas_init()) return EXIT_FAILURE;

  engines = ecore_evas_engines_get();
  fprintf(stdout, "Available engines:\n");
  EINA_LIST_FOREACH(engines, l, data)
  fprintf(stdout, "%s\n", data);
  ecore_evas_engines_free(engines);

  /* this will give you a window with an Evas canvas under the first engine
   * available */
  ee = ecore_evas_new(NULL, 0, 0, WIDTH, HEIGHT, NULL);
  if (!ee) goto panic;
  ecore_evas_title_set(ee, "Ecore Evas Minimal Example");
  ecore_evas_show(ee);

  evas = ecore_evas_get(ee);

  ecore_evas_geometry_get(ee, NULL, NULL, &w, &h);
  bg = evas_object_rectangle_add(evas);
  evas_object_color_set(bg, 255, 255, 255, 255 * 90 / 100); /* white bg */
  evas_object_resize(bg, w, h);
  evas_object_show(bg);

  box = evas_object_rectangle_add(evas);
  evas_object_color_set(box, rand() % 256, rand() % 256, rand() % 256, 255);
  evas_object_move(box, (w / 8), (h / 8));
  evas_object_resize(box, (w / 4), (h / 4));
  evas_object_show(box);

  /* this is a border around the box, container of the rectangles we
   * are going to experiment with. this way you can see how the
   * container relates to the children */
  border = evas_object_image_filled_add(evas);
  evas_object_image_file_set(border, border_img_path, NULL);
  evas_object_image_border_set(border, 2, 2, 2, 2);
  evas_object_image_border_center_fill_set(border, EVAS_BORDER_FILL_NONE);
  evas_object_show(border);
  evas_object_move(border, (w / 4) - 2, (h / 4) - 2);
  evas_object_resize(border, (w / 2) + 4, (h / 2) + 4);

  struct sigaction sigint;
  sigint.sa_handler = signalHandler;
  sigemptyset(&sigint.sa_mask);
  sigint.sa_flags = SA_RESETHAND;
  sigaction(SIGINT, &sigint, NULL);

  ecore_timer_add(0.016, _animate_scene, NULL);

  ecore_main_loop_begin();
  ecore_evas_shutdown();
  return 0;

error:
  ecore_evas_shutdown();
  return -1;

panic:
  fprintf(stderr,
          "You got to have at least one evas engine built and linked"
          " up to ecore-evas for this example to run properly.\n");
  return -2;
}
