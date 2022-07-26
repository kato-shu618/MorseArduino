#include <Arduino_FreeRTOS.h>

#define pin 12
//文字，モールス符号，符号長定義
String charCode = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
String tontuCode[] = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."//alphabet
  ,".----","..---","...--","....-",".....","-....","--...","---..","----.","-----","s"//0~9,space
};

//点灯時間
int ton = 190;//トン.
int tu = ton*3;//ツー-
int space = ton * 4;//空白＋文字間空白k
int rest = ton * 3;//文字間空白

//文字列設定
String message = "Default Message ";
String tempMessage;
boolean serialFlag = false;


// define two tasks
void TaskMorse(void *pvParameters);
void TaskSerialPrint(void *pvParameters);

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  message.toUpperCase();
  pinMode(pin,OUTPUT);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskSerialPrint
    , "SerialPrint"
    , 128
    , NULL
    , 1
    , NULL
    );

  xTaskCreate(
    TaskMorse
    , "Morse"
    , 128 //Stack size
    , NULL
    , 2 //Priority
    , NULL 
    );
  
  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/


void TaskSerialPrint(void *pvParameters)
{
  (void) pvParameters;

  for(;;)
  {
     if(Serial.available() > 0){
        tempMessage = Serial.readString();
        serialFlag = true;
        Serial.println(tempMessage);
      }
     vTaskDelay(1000); 
   }
}

void TaskMorse(void *pvParameters)
{
  (void) pvParameters;
  for(;;){

if(serialFlag){
        Serial.println("changeMessage");
        message = tempMessage;
        tempMessage = "";
        message.toUpperCase();
        serialFlag = false;
        delay(100);
      }
    
      Serial.println(message);
      Serial.println(message.length());
      Serial.print("serialFlag:");
      Serial.println(serialFlag);

      

      for(int i = 0;i<message.length();i++){
          int s = charCode.indexOf(message[i]);
          Serial.print(charCode[s]);
          Serial.print(" : ");
          getTontuCode(s);
        }
        vTaskDelay(100);
    }
}

void getTontuCode(int s){
    for(int j = 0; j < tontuCode[s].length();j++){
      Serial.print(tontuCode[s].charAt(j));
      setLightTime(String(tontuCode[s].charAt(j)));
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
