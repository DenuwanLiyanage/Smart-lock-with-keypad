#include <EEPROMex.h>
#include <Keypad.h>

String adminPW="9632";
String pinadmin="";
byte rowPins[4]={2,3,4,5};
byte colPins[4]={6,7,8,9};

String myPin="1234";
String pin;
String newPin="";
int count=0;
int j;
int i=0;
int m=0;
int count1;
boolean flag =false;

char keys[4][4]={{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}};
Keypad newKeyPad = Keypad(makeKeymap(keys),rowPins,colPins,4,4);

void setup() {
  Serial.begin(19200);  

}

void loop() {
  j=EEPROM.read(101);
  char newK = newKeyPad.getKey();
  switch (newK){
  
  case 'A':

      Serial.println("Enter Admin Password");  
      while (m<4){  
        char key2 = newKeyPad.getKey();
        if (key2 !=NO_KEY){
          pinadmin += String(key2);   
          m+=1;  
        }   
      }
      Serial.println("admin :"+pinadmin);
      if (adminPW==pinadmin){
          Serial.println("CAN ACCESS");
          m=0;
          while(true){
            Serial.println("Enter New Password");
            while (m<4){  
              char key1 = newKeyPad.getKey();
                if (key1 !=NO_KEY){
                  pin += String(key1);   
                  m+=1;  
                }   
            }
          m=0;
          Serial.println(pin);
          Serial.println("Comfirm Password! Press D OR Clear to press C");
          char key3= newKeyPad.waitForKey(); 
          if (key3=='D'){
            Serial.println("Comfirmed!");
            count=pin.toInt();
            pin="";
            EEPROM.write(j,count);
            j+=1;
            EEPROM.write(101,j);
            break;
          }
          else if(key3=='C'){
            pin="";
          }      
        }
       }
       else{
          Serial.println("Wrong  Admin Password");}
          pinadmin="";
          pin="";
          m=0;
          break;
          
    case 'B':    
      Serial.println("Enter Password to Entry !");
      while (i<4){  
        char key = newKeyPad.getKey();
        if (key !=NO_KEY){
          newPin += String(key);   
          i+=1;  
        }   
      }
      i=0;
      EEPROM.write(100,newPin.toInt());
      for(int k=0;k<j;k++){
        Serial.println(count1);
        if (EEPROM.read(k) == EEPROM.read(100) ){
            flag=true;
            break;
        }else{
          flag=false; 
        }
      }
      if (flag==true){
        digitalWrite(12,HIGH);
        Serial.println("CAN ACCESS");  
      }else{
        Serial.println("WRONG PIN");
      }
      
      newPin="";
      break;
  }
  }
  
