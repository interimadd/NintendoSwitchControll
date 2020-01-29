/**
  乱数消費し続けるスケッチ

  初期条件は以下の通り
* 1.ランクマバグを使用し、使える状態であること
* 2.31日まである月の1日からスタートすること
* 3.ポケセン内でゲーム画面のままUSBを挿すこと
*/
#include <auto_command_util.h>
#include <avr/sleep.h>
int day_count = 0;
#define GOAL 100 //消費する日数を入力
void setup()
{
  pushButton(Button::B, 100, 10);
  // ホーム画面 > 設定
  pushButton(Button::HOME, 500);
  pushHatButton(Hat::DOWN, 40);
  pushHatButton(Hat::RIGHT, 20, 4);
  pushButton(Button::A, 300);
  // 設定 > 本体 > 日付と時刻
  pushHatButtonContinuous(Hat::DOWN, 2000);
  pushHatButton(Hat::RIGHT, 100);
  pushHatButton(Hat::DOWN, 100, 4);
  pushButton(Button::A, 100);
  // 日付と時刻 > 現在の日付と時刻
  pushHatButton(Hat::DOWN, 20, 2);
  pushButton(Button::A, 100);
  pushHatButton(Hat::RIGHT, 20, 2);
  pushHatButton(Hat::UP, 20);
  pushHatButton(Hat::RIGHT, 20,3);
  pushButton(Button::A, 20);
  day_count++;
}
void day1day30()
{
  pushButton(Button::A, 30);
  pushHatButton(Hat::LEFT, 30, 3);
  pushHatButton(Hat::UP, 30);
  pushHatButton(Hat::RIGHT, 30,3);
  pushButton(Button::A, 30);
}
void day31day1()
{
  day1day30();
  day1day30();
}
void sleepNow()
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_mode();
}
void branches()
{
  if (day_count % 31 == 0) {
    day31day1();
    day_count++;
  }
  else {
    day1day30();
    day_count++;
  }
}
void loop()
{
  if (day_count >= GOAL) {
    sleepNow();
  }
  else {
    branches();
  }
}
