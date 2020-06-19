/**
* 育て屋から卵を回収→孵化→ボックスに預けるを繰り返すスケッチ
* ボックスに空きがある限り、ポケモンを孵化し続ける
*
* 初期条件は以下の通り
* 1.ハシノマはらっぱにいること
* 2.自転車に乗っていること
* 3.手持ちが1体のみのこと
* 4.Xボタンを押したときに「タウンマップ」が左上、「ポケモン」がその右にあること
* 5.ボックスが空のこと
*/
#include <auto_command_util.h>

const int TIME_TO_HATCHING_SEC = 120;

// 空飛ぶタクシーでハシノマはらっぱに移動
void moveToInitialPlayerPosition(){
    pushButton(Button::X, 1000);
    pushHatButtonContinuous(Hat::LEFT_UP, 1000);
    pushButton(Button::A, 2500);
    pushButton(Button::A, 1500, 2);
    delay(2000);
}

// 初期位置から育て屋さんに移動し卵を受け取る
void getEggFromBreeder(){
    // 初期位置(ハシノマはらっぱ)から育て屋さんのところまで移動
    pushButton(Button::PLUS, 1000);
    tiltJoystick(0, 0, 100, 0, 2000);
    tiltJoystick(30, -100, 0, 0, 2000);
    // 育て屋さんから卵をもらう
    pushButton(Button::A, 1000, 4);
    pushButton(Button::B, 500, 10);
    pushButton(Button::PLUS, 1000);
}

// 初期位置(ハシノマはらっぱ)からぐるぐる走り回る
void runAround(int run_time_sec){
    // 野生ポケモンとのエンカウントを避けるため初期位置から少し移動する
    tiltJoystick(100, 0, 0, 0, 600);
    // delayの秒数がintの最大値を越えないように30秒ごとに実行する
    for(int i=0; i<run_time_sec/30; i++){
        tiltJoystick(100, 100, -100, -100, 30000);
    }
    tiltJoystick(100, 100, -100, -100, (run_time_sec%30)*1000);
}

// 卵が孵化するのを待つ
void waitEggHatching(){
    pushButton(Button::B, 500, 40);
}

// 孵化した手持ちのポケモンをボックスに預ける
// box_line : 何列目にポケモンを預けるか
void sendHatchedPoemonToBox(int box_line){
    // ボックスを開く
    pushButton(Button::X, 1000);
    pushHatButtonContinuous(Hat::LEFT_UP, 1000);
    pushHatButton(Hat::RIGHT, 500);
    pushButton(Button::A, 2000);
    pushButton(Button::R, 2000);
    // 手持ちの孵化したポケモンを範囲選択
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

// 手持ちが1体の状態から、卵受け取り→孵化を繰り返す
void reciveAndHatchEggs(){
    for(int egg_num=0; egg_num<5; egg_num++){
        moveToInitialPlayerPosition();
        getEggFromBreeder();
        moveToInitialPlayerPosition();
        runAround(TIME_TO_HATCHING_SEC);
        waitEggHatching();
    }
}

// 孵化シーケンスを実行
void execHatchingSequence(){
    for(int box_line=0; box_line<6; box_line++){
        reciveAndHatchEggs();
        sendHatchedPoemonToBox(box_line);
    }
    moveToNextBox();
}

void setup(){
    pushButton(Button::B, 500, 5);
    // 初めの卵が出現するまで走り回る
    moveToInitialPlayerPosition();
    runAround(20);
}

void loop(){
    execHatchingSequence();
}
