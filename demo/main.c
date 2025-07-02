#include "canvas.h"
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define WIDTH 500
#define HEIGHT 500 

//Demonstration of the lines from center at 15 degree  increments like a clock
int main(void){
    canvas_t *canvas=create_canvas(WIDTH,HEIGHT);
    if (!canvas){
        return 1;
    }

    const float c_x=WIDTH/2.0f;
    const float c_y=HEIGHT/2.0f;

    for (int angle=0;angle<360;angle+=15){
        float rad=angle *M_PI/180.0f; //Convert degrees to radians
        float x=c_x+200.0f*cos(rad); //Calculate x coordinate
        float y=c_y+200.0f*sin(rad); //Calculate y coordinate
        draw_line_f(canvas,c_x,c_y,x,y,1.5f); //Draw line from center to calculated point
    }

    save_canvas(canvas,"clock_lines.pgm"); //Save the canvas to a file
    remove_canvas(canvas); //Free the allocated memory for the canvas
    return 0;

}
