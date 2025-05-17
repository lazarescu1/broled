#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define SYS_BACKLIGHT_PATH  "/sys/class/backlight/amdgpu_bl1"
#define BRIGHTNESS          "/sys/class/backlight/amdgpu_bl1/brightness"
#define MAX_BRIGHTNESS      "/sys/class/backlight/amdgpu_bl1/max_brightness"

FILE* 
openfile(const char *path, const char *mode) 
{
    FILE *fp = fopen(path, mode);

    if (fp == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE); 
    }

    return (fp);
}

int
main (int argc, char *argv[])
{
    int max_brightness; 
    int brightness = atoi(argv[1]);

    /* Program usage */
    if (argc != 2) {
        fprintf(stderr, "Bad usage!\nUsage: %s <brightness value>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Get the maximum brightness value */
    FILE *f_max_brightenss = openfile(MAX_BRIGHTNESS, "r");

    fscanf(f_max_brightenss, "%d", &max_brightness);
    fclose(f_max_brightenss);

    /* Change the brightness value */
    if (brightness <= 0 || brightness > max_brightness) {
        printf("Brightness value is out of range!\nThe brightness value should be between 1 and %d\n",
                max_brightness);
        exit(EXIT_FAILURE);
    }
    else {
        FILE *f_brightness = openfile(BRIGHTNESS, "w");

        fprintf(f_brightness, "%d", brightness);
        fclose(f_brightness);
    }

    return (0);
}
