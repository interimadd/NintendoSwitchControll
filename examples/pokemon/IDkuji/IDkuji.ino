/**
* IDくじを引き続けるスケッチ
*
* 初期条件は以下の通り
* 1.ランクマバグを使用し、使える状態であること
* 2.ポケセンのロトミの前でゲーム画面のままUSBを挿すこと
*/
#include <auto_command_util.h>

void changeDateSequence()
{
    // ホーム画面 > 設定
    pushButton(Button::HOME, 500);
    pushHatButton(Hat::DOWN, 40);
    pushHatButton(Hat::RIGHT, 30, 5);
    pushButton(Button::A, 300);
    // 設定 > 本体 > 日付と時刻
    pushHatButtonContinuous(Hat::DOWN, 2000);
    pushHatButton(Hat::RIGHT, 500);
    pushHatButtonContinuous(Hat::DOWN, 700);
    pushButton(Button::A, 500);
    // 日付と時刻 > 現在の日付と時刻
    pushHatButton(Hat::DOWN, 20, 2);
    pushButton(Button::A, 500);
    // 日付更新
    pushHatButton(Hat::RIGHT, 100, 2);
    pushHatButton(Hat::UP, 100);
    pushHatButtonContinuous(Hat::RIGHT, 1000);
    pushButton(Button::A, 500);
    // ホーム画面 > ゲーム画面
    pushButton(Button::HOME, 1000);
    pushButton(Button::A, 500);
}

void drawIDkuji()
{
  //ロトミ起動 > IDくじ
  pushButton(Button::A, 1000, 2);
  pushHatButton(Hat::DOWN, 150);
  pushButton(Button::A, 100, 20);
  pushButton(Button::B, 250, 60);
}

void setup()
{
  pushButton(Button::B, 100, 10);
}

void loop() {
  drawIDkuji();
  changeDateSequence();
}
