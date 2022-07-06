//LEDpin定義
#define pin 12

//文字，モールス符号，符号長定義
String charCode = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
String tontuTest[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."//alphabet
  ,".----","..---","...--","....-",".....","-....","--...","---..","----.","-----","s"//0~9,space
};



//点灯時間
int ton = 190;//トン.
int tu = ton*3;//ツー-
int space = ton * 4;//空白＋文字間空白k
int rest = ton * 3;//文字間空白

//文字列設定
String message = "12My name is katoshu21";
//message.toUpperCase();

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  message.toUpperCase();
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(pin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  Serial.println(message);
  Serial.println(message.length());
  
  for(int i = 0; i < message.length();i++){
      int s = charCode.indexOf(message[i]);
      gettontuCode(s);
    }
}

void gettontuCode(int s){
    for(int j = 0; j < tontuTest[s].length();j++){
      Serial.print(tontuTest[s].charAt(j));
      setLightTime(String(tontuTest[s].charAt(j)));
    }
    Serial.println();
    delay(rest);
  }

void setLightTime(String str){
    int time = 0;
    if(str.equals(".")){//トン
        time = ton;
        digitalWrite(pin,HIGH);
    }else if(str.equals("-")){//ツー
        time = tu;
        digitalWrite(pin,HIGH);
    }else if(str.equals("k")){//空白
        time = space;
    }else{
        delay(0);
    }
    delay(time);
    digitalWrite(pin,LOW);
    delay(ton);

  }
