#include "scene.h"
#include "charater.h"

ALLEGRO_FONT *font = NULL;

typedef struct bgd
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *bg_move[2];
    int background; // counting the time of background
    int background_time; // indicate how long the background

}Background;

Background bg;

// function of menu
void menu_init(){
    font = al_load_ttf_font("./font/pirulen.ttf",12,0);
}

void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP )
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER )
            judge_next_window = true;
}
void menu_draw(){
    al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(255, 255, 255), 0);
}
void menu_destroy(){
    al_destroy_font(font);
}

// function of game_scene
void game_scene_init(){

    character_init();
    background_init();

}


void background_init(){

    // load road images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/road%d.png", i );
        bg.bg_move[i-1] = al_load_bitmap(temp);
    }

    // initial the geometric information of BG
    bg.width = al_get_bitmap_width(bg.bg_move[0]);
    bg.height = al_get_bitmap_height(bg.bg_move[0]);

    // initial the BG component
    bg.background = 0;
    bg.background_time = 60;

}

//移動的背景
void background_process(ALLEGRO_EVENT event){

        // process the background
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            bg.background++;
            bg.background %= bg.background_time;
        }
    }
}


void background_draw(){

        if( bg.background < bg.background_time/2 ){

            al_draw_bitmap(bg.bg_move[0], 0, 0, 0);
        }
        else{
            al_draw_bitmap(bg.bg_move[1], 0, 0, 0);
        }

}


void game_scene_draw(){

    background_draw();
    character_draw();
    al_flip_display();
}

void game_scene_destroy(){

    al_destroy_bitmap(bg.bg_move[0]);
    al_destroy_bitmap(bg.bg_move[1]);
    character_destory();
}
