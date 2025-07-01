#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "canvas.h"


//Create a new canvas with given width and height
canvas_t *create_canvas(int width,int height){
    canvas_t *canvas=malloc(sizeof *canvas);//Allocate memory for canvas struct
    if (!canvas){
        perror("malloc(canvas)");
        return NULL;
    }
    canvas->width=width;
    canvas->height=height;
    canvas->pixels=malloc(height *sizeof *canvas->pixels);//Allocate memory for rows
    if (!canvas->pixels){
        perror("malloc(pixels)");
        free(canvas);
        return NULL;
    }
    //Allocate memory for each row and initialize to zero
    for (int y=0;y<height;++y){
        canvas->pixels[y]=calloc(width,sizeof **canvas->pixels);
        if (!canvas->pixels[y]) { //Roll back on failure
            perror("calloc(row)");
            for (int j=0;j<y;++j)
                free(canvas->pixels[j]);
            free(canvas->pixels);
            free(canvas);
            return NULL;
        }
    }
    return canvas;
}
//Free all memory associated with a canvas
void remove_canvas(canvas_t *canvas)
{
    if (!canvas) return;
    for (int y=0;y<canvas->height;++y)
        free(canvas->pixels[y]);
    free(canvas->pixels);
    free(canvas);
}


//Get the value of a pixel at (x, y); returns 0.0f if out of bounds
float get_pixel(canvas_t *c,int x,int y)
{
    if (!c||x<0||x>=c->width||y<0||y>=c->height) return 0.0f;
    return c->pixels[y][x];
}

//Set the value of a pixel at (x, y); clamps value to [0,1]
void set_pixel(canvas_t *c,int x,int y,float v)
{
    if (!c||x<0||x>=c->width||y<0||y>=c->height) return;
    if (v<0.0f)v=0.0f;
    if (v>1.0f)v=1.0f;
    c->pixels[y][x]=v;
}

//Set pixel with bilinear interpolation at floating-point coordinates (x, y)
void set_pixel_f(canvas_t *c,float x,float y,float intensity)
{
    int x0=(int)floorf(x);
    int y0=(int)floorf(y);
    float dx=x-x0;
    float dy=y-y0;
    //Update the 2x2 neighborhood around (x, y)
    for (int j=0;j<=1;++j)
        for (int i=0;i<=1;++i){
            int xi=x0+i,yj=y0+j;
            if (xi<0||xi>= c->width||yj<0||yj>=c->height) continue;
            float w=(1.0f-fabsf(i-dx))*(1.0f-fabsf(j - dy));
            float v=c->pixels[yj][xi]+intensity *w;
            if (v>1.0f)v=1.0f;
            c->pixels[yj][xi] = v;
        }
}
// Draw an anti-aliased line from (x0, y0) to (x1, y1) with given thickness
void draw_line_f(canvas_t *c,float x0,float y0,float x1,float y1,float thickness)
{
    float dx=x1-x0;
    float dy=y1-y0;
    float len=hypotf(dx, dy);
    if (len==0.0f){ //Degenerate: just a point
        set_pixel_f(c,x0,y0,1.0f);
        return;
    }
    const float step=0.5f;// Sampling every 0.5 px
    int steps=(int)ceilf(len/step);
    for (int n=0;n<=steps;++n){
        float t=(float)n/steps;
        float px=x0+t*dx;
        float py=y0+t*dy;
        //Draw a filled circle at each step for thickness
        for (float ky=-thickness/2;ky<=thickness/2;ky+=0.5f)
            for (float kx=-thickness/2;kx<=thickness/2;kx+=0.5f)
                if (kx*kx+ky*ky<=(thickness*thickness)/4.0f)
                    set_pixel_f(c,px+kx,py+ky,1.0f);
    }
}
//Save the canvas to a file in PGM (P2) format
void save_canvas(canvas_t *c,const char *filename)
{
    FILE *fp=fopen(filename,"w");
    if (!fp){
        perror("fopen");
        return;
    }
    fprintf(fp,"P2\n%d %d\n255\n",c->width,c->height);
    for (int y=0;y<c->height;++y){
        for (int x=0;x<c->width;++x){
            int v=(int)(c->pixels[y][x]*255.0f+0.5f);
            fprintf(fp,"%d ",v);
        }
        fputc('\n',fp);
    }
    fclose(fp);
}
