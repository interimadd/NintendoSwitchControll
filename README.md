# NintendoSwitchController

Nintendo SWitchをArduino Leonardoを使って制御するArduinoのライブラリーです。  
ライブラリー内の関数を組み合わせるだけで、様々な作業を自動化するArduinoのスケッチを作成することができます。  
Leonardoだけで完結しているため、追加の電子部品やはんだ付け等が不要で、Switchに接続するだけで実行することができるため、短時間で導入することができます。  
サンプルとしてライブラリ内にポケモンの孵化やワット稼ぎ、レイドバトルを自動化するスケッチを含んでいます。

## 必要なもの
**ハードウェア**
- Arduino Leonardo
    - 出費を抑えるなら互換機の[Arduino Pro Micro](https://amzn.to/3acyrgb)がお勧めです。
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

![vid](https://user-images.githubusercontent.com/14195687/112593510-f4293f00-8e4a-11eb-82e2-ae1317b5a618.jpg)

### 入力
**サンプルスケッチを書き込む**  
1. Arduino IDEを立ち上げる

2. サンプルスケッチを開く
スケッチ例→NintendoSwitchControleer→pokeomn
![sketch](https://user-images.githubusercontent.com/14195687/112593499-effd2180-8e4a-11eb-95f3-06a7202a7fbc.jpg)

3. ArduinoをPCに接続し、ボードをLeonardoに設定。シリアルポートも接続しているポートに変更する。
![arduino](https://user-images.githubusercontent.com/14195687/112593518-f68b9900-8e4a-11eb-8d68-1ce7df2dfcf2.jpg)

4. 書き込む

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

### 自動ポケモン逃がし(release_pokemons.ino)
1ボックス分のポケモンを全て逃がすスケッチ

初期条件は以下の通り
1. メニューを開いていないこと
2. Xボタンを押したときに「ポケモン」が左上から1つ右の場所にあること

### 自動ワット稼ぎ(auto_gain_watt.ino)
巣穴からワットを回収し続けるスケッチ

初期条件は以下の通り
1. 願いのかたまりを投げ入れた巣穴の前にいること
2. 巣穴のワットは回収済みであること
3. Switchの本体設定で「インターネットで時間をあわせる」がOFFになっていること

### 自動レイドバトル(auto_raid_battle.ino)
レイドバトル→ポケモンを捕獲→ボックスに預ける→願いの塊を投げ入れるを繰り返すスケッチ
ボックスに空きがある限り、レイドバトルを続ける

初期条件は以下の通り
1. 願いの塊を投げ入れた巣穴の前にいること
2. 手持ちが1体のみのこと
3. Aボタン連打でレイドバトルで勝てるようにすること
4. Xボタンを押したときに「ポケモン」が左上の一つ右の場所にあること
5. ボックスが空のこと
6. 願いの塊を大量に持っていること

## 参考
[【ポケモン剣盾】全自動で卵を孵化させる装置](https://www.youtube.com/watch?v=oXnQt_Mbyzk)  
[Arduinoでポケモン剣盾自動化してみた ~自動ワット稼ぎ編~](https://qiita.com/sobassy/items/cb707e50f2f27a851886)