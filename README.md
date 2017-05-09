# GR-LYCHEE_ESP32_Serial_Bridge
ESP32(UART)とPC(USB)をブリッジするサンプルプログラムです。  
ESP32の評価やFlash書き込みの際にご利用いただけます。  
GR-LYCHEEの開発環境については、[GR-LYCHEE用オフライン開発環境の手順](https://developer.mbed.org/users/dkato/notebook/offline-development-lychee-langja/)を参照ください。


## 使い方
### シリアル設定
GR-LYCHEEのUSB0ポートをPCと接続して使用します。  
Windows10以外ご使用の場合、ドライバのインストールが必要となります。下記サイトの「Driver required on Windows!」からドライバーをダウンロードできます。  

https://developer.mbed.org/handbook/USBSerial

但し、「署名なしドライバ」となっていますので、お使いのWindowsバージョンによってはそのままインストールすることはできません。お使いのPC毎に設定方法が異なるため、検索サイトで「署名なしドライバ」で検索してください。  

ターミナルソフトソフトを立ち上げ、下記設定で通信してください。  

|            |        |
|:-----------|:-------|
| ボーレート | 115200 |
| データ     | 8bit   |
| パリティ   | none   |
| ストップ   | 1bit   |
| フロー制御 | none   |

### ボタン
US0ボタンでEN端子、US1ボタンでBOOT端子を操作できます。ボタンを押すとLOW、離すと HIGHになります。  

### ESP32のFlash書き込み
ESP32を書き込みモードにする際は、US1を押しながらUS0を短押し、その後US1を離します。  

##### Flash Download Toolsの使い方
フラッシュ書き込みの例として、ここでは、Windows PC版 Flash Download Tools V3.4.4の使い方を紹介します。  

Espressif’s official Flash Download Tools:  
http://espressif.com/en/support/download/other-tools?keys=&field_type_tid%5B%5D=13


`flash_download_tools_v3.4.4.zip`を展開し、`ESPFlashDownloadTool_v3.4.4.exe`を実行します。  

![](docs/img/esp32_tool_1.jpg)  
*ESP32 DownloadTool* を選択します。  

![](docs/img/esp32_tool_2.jpg)  

1. 書き込み用の.binファイルを設定します。  
2. SPI SPEEDに*40MHz*を設定します。  
3. SPI MODEに*DIO*を設定します。  
4. FLASH SIZEに*32Mbit*を設定します。  
5. COMにUSB0に割り当たったCOMポートを設定します。  
6. ボーレートを選択します。460800bpsでの書き込みを確認できていますが、書き込みに失敗するようでしたらボーレートを下げてください。
7. ESP32を書き込みモードにするため、GR-LYCHEEのUS1を押しながらUS0を短押し、その後US1を離します。最後にツールのSTARTボタンを押すと書き込みを開始します。  
