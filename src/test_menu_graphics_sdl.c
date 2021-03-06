#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graphics_minimalist_sdl.h"
#include "menu_test.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <font file>\n", argv[0]);
        return 1;
    }

    char *font_filename = argv[1];

    graphics_minimalist_sdl_t *graphics = graphics_minimalist_sdl_init(font_filename);

    char err_msg[MENU_TEST_ERR_MSG_SIZE] = "";

    if (graphics == NULL) {
        fprintf(stderr, "Could not initialize sdl");
        return 2;
    }

    bool success = test_menu(graphics, graphics_minimalist_sdl_callbacks, err_msg);
    graphics_minimalist_sdl_quit(graphics);
    if (!success) {
        puts(err_msg);
    }

    return 0;
}
