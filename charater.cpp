#include "charater.h"

// the state of character
enum {STOP = 0, MOVE, ATK};
typedef struct character
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    //bool dir; // left: false, right: true
    int state; // the state of character
    ALLEGRO_BITMAP *img_move[2];
    ALLEGRO_BITMAP *img_atk[2];
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
}Character;

Character chara;
ALLEGRO_SAMPLE *sample = NULL;

//修改貓跑步的動作

void character_init(){
    // load character images
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/cat_run%d.png", i );
        chara.img_move[i-1] = al_load_bitmap(temp);
    }
    for(int i = 1 ; i <= 2 ; i++){
        char temp[50];
        sprintf( temp, "./image/cat_run%d.png", i );
        chara.img_atk[i-1] = al_load_bitmap(temp);
    }
    // load effective sound
    //先隨便抓了一個jump的音效下來用
    sample = al_load_sample("./sound/jump.mp3");
    chara.atk_Sound  = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(chara.atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(chara.atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    chara.width = al_get_bitmap_width(chara.img_move[0]);
    chara.height = al_get_bitmap_height(chara.img_move[0]);

    //改了一下初始位置
    chara.x = 50;
    chara.y = HEIGHT/2;
    //chara.dir = false;

    // initial the animation component
    chara.state = STOP;
    chara.anime = 0;
    chara.anime_time = 30;

}

void charater_process(ALLEGRO_EVENT event){
    // process the animation
    if( event.type == ALLEGRO_EVENT_TIMER ){
        if( event.timer.source == fps ){
            chara.anime++;
            chara.anime %= chara.anime_time;
        }
    // process the keyboard event
    }else if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;
        chara.anime = 0;
    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}

//鍵盤控制: 只保留W和S(上下)，把位移加大(10)
//我先直接把ATK的變數當成Jump
void charater_update(){
    // use the idea of finite state machine to deal with different state
    if( key_state[ALLEGRO_KEY_W] ){
        chara.y -= 10;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_S] ){
        chara.y += 10;
        chara.state = MOVE;
    }else if( key_state[ALLEGRO_KEY_SPACE] ){
        chara.state = ATK;
    }else if( chara.anime == chara.anime_time-1 ){
        chara.anime = 0;
        chara.state = STOP;
    }else if ( chara.anime == 0 ){
        chara.state = STOP;
    }
}

//因為沒有左右轉向的部分，把多餘的地方刪掉了
void character_draw(){
    // with the state, draw corresponding image
    if( chara.state == STOP ){

            al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);

    }else if( chara.state == MOVE ){

            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_move[0], chara.x, chara.y, 0);
            }else{
                al_draw_bitmap(chara.img_move[1], chara.x, chara.y, 0);
            }

    }else if( chara.state == ATK ){

            if( chara.anime < chara.anime_time/2 ){
                al_draw_bitmap(chara.img_atk[0], chara.x, chara.y, 0);
                al_play_sample_instance(chara.atk_Sound);
                chara.y -= 15;  //jump (up)

            }else{
                al_draw_bitmap(chara.img_atk[1], chara.x, chara.y, 0);
                chara.y += 15;  //jump(down)
            }

    }
}
void character_destory(){
    al_destroy_bitmap(chara.img_atk[0]);
    al_destroy_bitmap(chara.img_atk[1]);
    al_destroy_bitmap(chara.img_move[0]);
    al_destroy_bitmap(chara.img_move[1]);
    al_destroy_sample_instance(chara.atk_Sound);
}
