/**
* レイドバトル→ポケモンを捕獲→ボックスに預ける→願いの塊を投げ入れるを繰り返すスケッチ
* ボックスに空きがある限り、レイドバトルを続ける
*
* 初期条件は以下の通り
* 1. 願いの塊を投げ入れた巣穴の前にいること
* 2. 手持ちが1体のみのこと
* 3. Aボタン連打でレイドバトルで勝てるようにすること
* 4. Xボタンを押したときに「ポケモン」が左上の一つ右の場所にあること
* 5. ボックスが空のこと
* 6. 願いの塊を大量に持っていること
*/
#include <auto_command_util.h>

// レイドバトルが終わるまでの時間
const int BATTLE_FINISH_SEC = 200;

// 巣穴の前からひとりレイドを始め、レイドポケモンを倒し、捕まえる
void startRaidBattle(){
    // ひとりではじめる
    pushButton(Button::A, 1500);
    pushHatButton(Hat::DOWN, 500);
    // レイドバトル中はA連打
    for(int i=0; i<BATTLE_FINISH_SEC; i++){
        pushButton(Button::A, 500, 2);
    }
}

// レイドバトル後もしばらく続くAボタン連打の後の画面から、
// 巣穴の前の最初のポジションに戻す
void resetState(){
    tiltJoystick(0,0,0,0,100);
    pushButton(Button::B, 1000, 4);
    delay(1000);
    pushButton(Button::A, 1000, 2);
    pushButton(Button::B, 1000, 3);
}

// 捕獲した手持ちのポケモンをボックスに預ける
// box_line : 何列目にポケモンを預けるか
void sendCapturePokemonToBox(int box_line){
    // ボックスを開く
    pushButton(Button::X, 1000);
    pushHatButtonContinuous(Hat::LEFT_UP, 1000);
    pushHatButton(Hat::RIGHT, 500);
    pushButton(Button::A, 2000);
    pushButton(Button::R, 2000);
    // 手持ちの捕獲したポケモンを範囲選択
    pushHatButton(Hat::LEFT, 500);
    pushHatButton(Hat::DOWN, 500);
    pushButton(Button::Y, 500, 2);
    pushButton(Button::A, 500);
    pushHatButtonContinuous(Hat::DOWN, 2000);
    pushButton(Button::A, 500);
    // ボックスに移動させる
    pushHatButton(Hat::RIGHT, 500, box_line+1);
    pushHatButton(Hat::UP, 500);
    pushButton(Button::A, 500);
    // ボックスを閉じる
    pushButton(Button::B, 1500, 3);
}

// ボックスを次のボックスに移動させる
void moveToNextBox(){
    // ボックスを開く
    pushButton(Button::X, 1000);
    pushHatButtonContinuous(Hat::LEFT_UP, 1000);
    pushHatButton(Hat::RIGHT, 500);
    pushButton(Button::A, 2000);
    pushButton(Button::R, 2000);
    // ボックスを移動
    pushHatButton(Hat::UP, 500);
    pushHatButton(Hat::RIGHT, 500);
    // ボックスを閉じる
    pushButton(Button::B, 1500, 3);
}

// レイドバトルをし、ポケモンを捕まえ、ボックスに預けるを繰り返し、
// ボックスが一杯になったら次のボックスへ移動する
void execRaidBattleSequence(){
    for(int send_line=0; send_line<6; send_line++){
        // 手持ちが一杯になるまでレイドバトルを行う
        for(int i=0; i<5; i++){
            startRaidBattle();
            resetState();
        }
        // 捕まえたポケモンを全て預ける
        sendCapturePokemonToBox(send_line);
    }
    // ボックスが一杯になったところでボックスを移動する
    moveToNextBox();
}

void setup(){
    pushButton(Button::B, 500, 5);
}

void loop(){
    execRaidBattleSequence();
}

