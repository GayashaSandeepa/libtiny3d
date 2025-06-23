#include "canvas.h"
#include <math.h>

#define WIDTH 256
#define HEIGHT 256

//Demonstration of the lines from center at 15 degree  increments like a clock
int main(){
    canvas_t *canvas=create_canvas(WIDTH, HEIGHT);
    float c_x=WIDTH/2.0f;
    float c_y=HEIGHT/2.0f;

    for (int angle=0;angle<360;angle+=15){
        float rad=angle  *M_PI/180.0f; //Convert degrees to radians
        float x=c_x+100.0f*cos(rad); //Calculate x coordinate
        float y=c_y+100.0f*sin(rad); //Calculate y coordinate
        draw_line(canvas,c_x,c_y,x,y,1.5f); //Draw line from center to calculated point
    }
    save_canvas(canvas,"clock_lines.pgm"); //Save the canvas to a file
    free_canvas(canvas); //Free the allocated memory for the canvas
    return 0;

}