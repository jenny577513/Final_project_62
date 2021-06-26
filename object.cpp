#include "object.h"

enum {STOP = 0, MOVE, ATK};
typedef struct object
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int state; // the state of character
    ALLEGRO_BITMAP *img;
    int cnt; // counting the time of cbject
    int cnt_time; // indicate how long the object
}Object;

Object cone;

void cone_init(){
    // load cone images
    cone.img = al_load_bitmap("./image/cone.png");
    cone.cnt = 0;
    cone.cnt_time = 30;

    cone.state = STOP;
    //cone初始位置
    cone.x = 1000;
    cone.y = HEIGHT/3;

}

void cone_process(ALLEGRO_EVENT event){
    // process the cone
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            cone.cnt++;
            cone.cnt %= cone.cnt_time;
        }
    }
}

//待完成: Cone move的細節
void cone_draw(){
    // with the state, draw corresponding image
    if( cone.state == STOP ){

            al_draw_bitmap(cone.img, cone.x, cone.y, 0);

    }else if( cone.state == MOVE ){

         al_draw_bitmap(cone.img, cone.x, cone.y, 0);
         cone.x -= 15;
    }

}
void cone_destory(){
    al_destroy_bitmap(cone.img);

}
