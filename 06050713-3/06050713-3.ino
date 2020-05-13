#include <LiquidCrystal.h>
#define ROW_NUM 2 // 2列
#define COL_NUM 16 // 16欄（一列可顯示16個字）
int index = 0; // 游標的位置，也是下一字元的位置，範圍是0~31。
#define INDEX_MAX (COL_NUM * ROW_NUM) // 最多可輸入32個字
#define ROW(x) (x / COL_NUM) // 傳入index，可算出游標的列，0或1。
#define COL(x) (x % COL_NUM) // 傳入index，可算出游標的欄，0~15。

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup(){
  Serial.begin(9600);
  lcd.begin(COL_NUM, ROW_NUM);
  lcd.setCursor(0, 0); // 設定游標位置
  lcd.cursor(); // 顯示游標
  lcd.blink(); // 讓游標閃爍
}

void loop(){
  int b;
  while( (b = Serial.read()) != -1){ // 從序列埠讀取資料
    // 若是可視字元，ASCII碼從0x20到0x7E
    if(0x20 <= b && b <= 0x7E){
      if(index == INDEX_MAX - 1){
        // 如果游標已經停在最後一個位置
        // 跳回最開頭，並且清除LCD上的顯示資料
        index = 0;
        lcd.clear();
      }

      lcd.write(b); // 輸出從序列埠收到的資料
      index++; // 指向下一個位置
      lcd.setCursor(COL(index), ROW(index));
    }
  }
}
