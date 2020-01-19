/**
* 1ボックス分のポケモンを全て逃がす
* 
* 初期条件は以下の通り
* 1.メニューを開いていないこと
* 2.Xボタンを押したときに「ポケモン」が左上から1つ右の場所にあること
*/
#include <auto_command_util.h>

// ボックスを開く
void open_box(){
    pushButton(Button::X, 1000);
    pushHatButtonContinuous(Hat::LEFT_UP, 1000);
    pushHatButton(Hat::RIGHT, 500);
    pushButton(Button::A, 2000);
    pushButton(Button::R, 2000);
}

// ボックス内の今いるカーソルにいるポケモンを逃がす
void release_pokemon(){
    pushButton(Button::A, 500);
    pushHatButton(Hat::UP, 500, 2);
    pushButton(Button::A, 1000);
    pushHatButton(Hat::UP, 500);
    pushButton(Button::A, 1000);
    pushButton(Button::A, 300, 4);
}

void setup(){
    pushButton(Button::B, 500, 5);
    open_box();
    for(int release_poke_num = 0; release_poke_num < 30; release_poke_num++){
        // ポケモンを逃がす
        release_pokemon();
        // カーソルを次のポケモンの場所に移動させる
        pushHatButton(Hat::RIGHT, 500);
        if(release_poke_num%6 == 5){
            pushHatButton(Hat::DOWN, 500);
            pushHatButton(Hat::RIGHT, 500);
        }
    }
}

void loop(){
}
