# NintendoSwitchController

Nintendo SWitchをArduino Leonardoを使って制御するArduinoのライブラリーです。  
ライブラリー内の関数を組み合わせるだけで、様々な作業を自動化するArduinoのスケッチを作成することができます。  
Leonardoだけで完結しているため、追加の電子部品やはんだ付け等が不要で、Switchに接続するだけで実行することができるため、短時間で導入することができます。  
サンプルとしてライブラリ内にポケモンの孵化やワット稼ぎを自動化するスケッチを含んでいます。

## 必要なもの
**ハードウェア**
- Arduino Leonardo
- Arduino LeonardoとSwicthを接続するUSBケーブル

**ソフトウェア**
- Arduino IDE

## 使い方
### 環境設定
**ライブラリーのインストール**  
Arduinoのライブラリのあるディレクトリ(/Users/{username}/Documents/Arduino/libraries/ など)に、このレポジトリをcloneする/ダウンロードして展開する。

**Arduino LeonardoのデバイスIDを書き換える**  
hardware/arduino/avr/boards.txt内のleonardoのvidとpidを設定している個所を書き換える。
~~~
leonardo.vid=0x0f0d
leonardo.pid=0x0092
~~~
※ 複数ある場合は相当する箇所を全て書き換える  
※ 見つからない場合はArduino IDEのファイル>スケッチ例>SPIから適当なスケッチを開き、スケッチ>スケッチの場所を開くで開いたディレクトリから遡っていくと、boards.txtがある

### 入力
**サンプルスケッチを書き込む**  
サンプルスケッチを開き、ArduinoをPCに繋いで、Arduino IDE経由で書き込む

**Switchに接続する**  
SwicthのUSBポートにUSBケーブルを使ってLeonardoを接続する。  
接続して数回の入力の後、入力を受け付け始める。  
Switchをドックに刺した状態で、ドックのUSBポートにLeonardoを接続する方法でも動かすことができる。

## サンプルスケッチの説明

### 自動孵化(auto_hatching.ino)
育て屋から卵を回収→孵化→ボックスに預ける→ボックスを移動する、を繰り返すスケッチ  
ボックスに空きがある限り、ポケモンを孵化し続ける

初期条件は以下の通り
1. ハシノマはらっぱにいること
2. 自転車に乗っていること
3. 手持ちが1体のみのこと
4. Xボタンを押したときに「タウンマップ」が左上にあること
5. ボックスが空のこと
6. 育て屋にポケモンを預けていること

### 自動ワット稼ぎ(auto_gain_watt.ino)
巣穴からワットを回収し続けるスケッチ

初期条件は以下の通り
1. 願いのかたまりを投げ入れた巣穴の前にいること
2. 巣穴のワットは回収済みであること

## 参考
[【ポケモン剣盾】全自動で卵を孵化させる装置](https://www.youtube.com/watch?v=oXnQt_Mbyzk)  
[Arduinoでポケモン剣盾自動化してみた ~自動ワット稼ぎ編~](https://qiita.com/sobassy/items/cb707e50f2f27a851886)