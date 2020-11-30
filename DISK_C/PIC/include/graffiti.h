#ifndef GRAFFITI_H
#define GRAFFITI_H

int graffiti(void);
void draw_graffiti_page(void);
void colortable(void);
void shapetable(void);
void color_circle(int x0,int y0,int radius,int color);
void circle(int x0,int y0,int radius,int color,int width, int height);
void rectangle(int x0, int y0,int radius, int color,int width, int height);
void paint(int shape,int radius,int color,int width, int height);
int savepaint(BMPHeader* head,int left,int top,char* save_paint_addr);

#endif
