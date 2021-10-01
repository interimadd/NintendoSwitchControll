/**
* 巣穴からワットを回収し続けるスケッチ
*
* 初期条件は以下の通り
* 1. 願いのかたまりを投げ入れた巣穴の前にいること
* 2. 巣穴のワットは回収済みであること
* 3. Switchの本体設定で「インターネットで時間をあわせる」がOFFになっていること
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

// ワットを回収するシーケンス
void execWattGainSequence()
{
    // 募集開始
    pushButton(Button::A, 3000);
    // 日付変更
    changeDateSequence();
    // レイド募集中止
    pushButton(Button::B, 1000);
    pushButton(Button::A, 4000);
    // ワット回収
    pushButton(Button::A, 1000);
    pushButton(Button::B, 1000);
    pushButton(Button::A, 1000);
}

// ワット回収済みのねがいのかたまりを投げ入れた巣穴の前からスタート
void setup(){
    pushButton(Button::B, 500, 4);  // 最初の数回の入力はswitchが認識しない場合があるので、無駄打ちをしておく
    pushButton(Button::A, 1000);
}

void loop(){
    execWattGainSequence();
}
