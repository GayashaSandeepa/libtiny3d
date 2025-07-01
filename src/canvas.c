#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "canvas.h"

// Function Variables
set_pixel_f(canvas, x, y, intensity);
draw_line_f(canvas, x0, y0, x1, y1, thickness);
// Function Prototypes
void set_pixel_f(canvas_t *canvas, float x, float y, float intensity);
void draw_line_f(canvas_t *canvas, float x0, float y0, float x1, float y1, float thickness);

//Allocate and initialize a canvas
canvas_t *create_canvas(int width,int height){
    canvas_t *canvas=(canvas_t *)malloc(sizeof(canvas_t));
    if (!canvas){
        fprintf(stderr,"Memory allocation failed for canvas :(\n");
        return NULL;
    }
    canvas->width=width;
    canvas->height=height;
    canvas->pixels=malloc(height *sizeof(float *));

    if (!canvas->pixels){
        fprintf(stderr,"Memory allocation failed for pixels :\n");
        free(canvas);
        return NULL;
    }
    for (int i=0;i<height;i++){
        canvas->pixels[i]=calloc(width,sizeof(float));//initialize pixels to 0.0
    }
    return canvas;
}
void remove_canvas(canvas_t *canvas){  //free memory allocated for canvas
    if (canvas){
        for (int i=0;i<canvas->height;i++){
            free(canvas->pixels[i]);
        }
        free(canvas->pixels);
        free(canvas);
    }
}
void set_pixel_f(canvas_t *canvas,float x,float y,float intensity){  //set a pixel using bilinear filtering
    int xo=floorf(x);
    int yo=floorf(y);
    float dx=x-xo;
    float dy=y-yo;

    for (int i=0;i<=1;i++){ // Loop through the surrounding pixels
        for (int j=0;j<=1;j++){
            int xi=xo+i;
            int yj=yo+j;
            if (xi>=0 && xi<canvas->width && yj>=0 && yj<canvas->height){
                float weight=(1-fabsf(i-dx))*(1-fabsf(j-dy));
                canvas->pixels[yj][xi]+=intensity*weight;
                if (canvas->pixels[yj][xi]>1.0f){
                    canvas->pixels[yj][xi]=1.0f; //Clamp to maximum intensity
                }
            }
        }
    }
}

void draw_line_f(canvas_t *canvas,float x0,float y0,float x1,float y1,float thickness){ //draw a smooth aliased line using DDA algorithm
    float dx=x1-x0;
    float dy=y1-y0;
    float length=sqrtf(dx*dx+dy*dy);
    float step=0.5f;   //Step size for drawing the line
    float steps = length / step;

    float norm_x=dx/length;
    float norm_y=dy/length;

    for(int i=0;i<=steps;i++){
        float t=i/steps;
        float px=x0+t*dx;
        float py=y0+t*dy;
         //Draw thickness as a circle around the line
        for (float k=-thickness/2;k<=thickness/2;k+=0.5f){
            for(float l=-thickness/2;l<=thickness/2;l+=0.5f){
                if (k*k+l*l<=(thickness*thickness/4.0f)){
                    set_pixel_f(canvas,px+k,py+l,1.0f); //Set pixel with intensity 1.0
                }
            }
        }
    }
}
//save a canvas to a PGM grayscale image file
void save_canvas(canvas_t *canvas,const char *filename){
    FILE *file=fopen(filename,"w");
    fprintf(file,"P2\n%d %d\n255\n",canvas->width,canvas->height);
    for (int y=0;y<canvas->height;y++){
        for (int x=0;x<canvas->width;x++){
            int intensity=(int)(canvas->pixels[y][x]*255);
            fprintf(file,"%d ",intensity);
        }
        fprintf(file,"\n");
    }
    fclose(file);
}