#include "scene.h"
#include "charater.h"
#include "object.h"
#include "background.h"

ALLEGRO_FONT *font = NULL;

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

    background_init();
    character_init();
    cone_init();
}

void game_scene_draw(){

    background_draw();
    character_draw();
    cone_draw();
    al_flip_display();
}

void game_scene_destroy(){

    cone_destory();
    background_destroy();
    character_destory();
}
