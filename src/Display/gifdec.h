#ifndef CIRCUITOS_GIFDEC_H
#define CIRCUITOS_GIFDEC_H
/*
Modified version of the excellent and lightweight gifdec library by Marcel Rodrigues.
(https://github.com/lecram/gifdec)
Library is modified to work with the filesystem File class from ESP's core.
*/
#include <Arduino.h>
#include <FS.h>

typedef struct gd_Palette {
    int size;
    uint8_t colors[0x100 * 3];
} gd_Palette;

typedef struct gd_GCE {
    uint16_t delay;
    uint8_t tindex;
    uint8_t disposal;
    int input;
    int transparency;
} gd_GCE;

typedef struct gd_GIF {
    fs::File* fd;
    off_t anim_start;
    uint16_t width, height;
    uint16_t depth;
    uint16_t loop_count;
    gd_GCE gce;
    gd_Palette *palette;
    gd_Palette lct, gct;
    void (*plain_text)(
        struct gd_GIF *gif, uint16_t tx, uint16_t ty,
        uint16_t tw, uint16_t th, uint8_t cw, uint8_t ch,
        uint8_t fg, uint8_t bg
    );
    void (*comment)(struct gd_GIF *gif);
    void (*application)(struct gd_GIF *gif, char id[8], char auth[3]);
    uint16_t fx, fy, fw, fh;
    uint8_t bgindex;
    uint8_t *canvas, *frame;
} gd_GIF;

gd_GIF *gd_open_gif(fs::File* file);
int gd_get_frame(gd_GIF *gif);
void gd_render_frame(gd_GIF *gif, uint8_t *buffer, bool monochrome = 1);
int gd_is_bgcolor(gd_GIF *gif, uint8_t color[3]);
void gd_rewind(gd_GIF *gif);
void gd_close_gif(gd_GIF *gif);

#endif /* SPENCER_GIFDEC_H */
