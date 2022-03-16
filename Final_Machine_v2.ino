#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

//////////////////////////XXXXXXXXXXX((STRING CONTANTS ))////////////////////////////

String new_line0a = "       WELCOME TO  ";
String new_line0b=  "    ******AJF*****";
String MSG = "PUT GASKET ON FIXTURE CAVITY & PLACE <PCBA> ON CAVITY APPLY PRESSURE";


//////////////////////XXXXXXXXXX(((INTEGER CONSTANTS )))XXXXXXXXXXXXXXXXXXXXXXXXX//////////////////////////


const int A = 8, B = 9, C = 10, D = 11; // the number of the pushbutton pin
int A_STATE, B_STATE, C_STATE, D_STATE = 0;    // variable for reading the pushbutton status
int c_cnt;
int addr;
const unsigned long eventInterval = 1000;
unsigned long previousTime = 0;
int tmr=0;
  int screenWidth = 20;
  int screenHeight = 4;
  
  int stringStart=0;
  int stringStop=0;
  int scrollCursor= screenWidth;
    

/////////////////////XXXXXXXXXXXXXXXX((( CUSTOM FUNCTIONS )))XXXXXXXXXXXXXXXXXXXX//////////////////////////


void ch_bits()
{
  A_STATE = digitalRead(A);
  B_STATE = digitalRead(B);
  C_STATE = digitalRead(C);
  D_STATE = digitalRead(D);

}

void WriteEpInt(int location , int value){
  EEPROM.write(location, value);
  EEPROM.write(location + 1, value >> 8);
}

int ReadEpInt(int location){
  int val;

  val = (EEPROM.read(location + 1) << 8);
  val |= EEPROM.read(location);

  return val;
}


/////////////////////XXXXXXXXXXXXXXXX(((BOOT WARMUP )))XXXXXXXXXXXXXXXX/////////////////


void setup()
{
  
  Serial.begin(9600);   // Initialize Serial Communication
  addr=0;
  
//////////////////////COUNTER INITIALISATION //////////////////////////////////////////

       c_cnt=ReadEpInt(addr);
//     WriteEpInt(addr,c_cnt);
//     Serial.println(ReadEpInt(addr));

////////////////////////////////////////////////////////////////////////////////////

  lcd.init();                      // initialize the lcd
                                   // Print a message to the LCD.
  lcd.backlight();
  lcd.noBlink();
  lcd.setCursor(0,0);
  lcd.print("********************");
  lcd.setCursor(0, 1);
  lcd.print("   WELCOME TO AJF");
  lcd.setCursor(0,2);
  lcd.print("     AUTOMATION");
  lcd.setCursor(0, 3);
  lcd.print("********************");
 
  delay (2000); //// BOOT DELAY 
  lcd.clear();  /// CLEANOUT 

  // // initialize the pushbutton pin as an input:////////////////////////////////

  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);

  A_STATE = digitalRead(A);
  B_STATE = digitalRead(B);
  C_STATE = digitalRead(C);
  D_STATE = digitalRead(D);

tmr=0;

}

//////////////////////////////XXXXXXXXXXXXX(((MAIN CODE CYCLE)))XXXXXXXXXXXXXX//////

void loop()
{
  ////// check the pin status every cycle startup /// ;)

ch_bits();
 unsigned long currentTime = millis();
 if (currentTime - previousTime >= eventInterval)
 {
   tmr++;
   previousTime = currentTime;

 }

  //  /////////////////////////////////////////// WHAT IF ?(0000) ///////////////////////////////// Not using

if (A_STATE == HIGH && B_STATE == LOW && C_STATE == LOW && D_STATE == LOW) 
{
   //STANDBY MODE
  lcd.clear();
  lcd.noBlink();
  lcd.setCursor(0, 1);
  lcd.print(new_line0a);
  lcd.setCursor(0, 3);
  lcd.print(new_line0b);
  
  while(A_STATE == LOW && B_STATE == LOW && C_STATE == LOW && D_STATE == LOW)
  {
   ch_bits();
  }
   //break;
}
  /////////////////////////////////////////// WHAT IF ?(0001) /////////////////////////////////  Now its 000

else if (A_STATE == LOW && B_STATE == LOW && C_STATE == LOW && D_STATE == LOW )
{
  tmr=0;
  lcd.clear();
  lcd.noBlink();
//  lcd.setCursor(0, 0);
//  lcd.print("Put gasket on ");
  lcd.setCursor(0, 0);
  lcd.print("PROGRESS:>>> ");
  lcd.setCursor(14, 0);
  lcd.print("01(12)");
//  lcd.setCursor(0, 1);
//  lcd.print("Fixture Cavity &");
//  lcd.setCursor(0, 2);
//  lcd.print("Plac PCBA on CAvi&");
//  lcd.setCursor(0, 3);
//  lcd.print("Apply Pressure");
            lcd.setCursor(5, 1);
      lcd.print("TASK NO #!");
  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(6, 3);
  lcd.print(ReadEpInt(addr));
 
  lcd.setCursor(10, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
  
  while(A_STATE == LOW && B_STATE == LOW && C_STATE == LOW && D_STATE == LOW)
   {
    currentTime = millis();
 if (currentTime - previousTime >= eventInterval)
 {
   tmr++;
   previousTime = currentTime;

 }
    ch_bits();
     lcd.noBlink();
//  lcd.setCursor(0, 0);
//  lcd.print("Put gasket on ");
  lcd.setCursor(0, 0);
  lcd.print("PROGRESS:>>> ");
  lcd.setCursor(14, 0);
  lcd.print("01(12)");
 
//  lcd.setCursor(0, 3);
//  lcd.print("Apply Pressure");
  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(6, 3);
  lcd.print(ReadEpInt(addr));
      lcd.setCursor(10, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
            lcd.setCursor(5, 1);
      lcd.print("TASK NO.#1");


    lcd.setCursor(scrollCursor, 2);
    lcd.print(MSG.substring(stringStart,stringStop));
    delay(170);
    lcd.clear();
  
  if(stringStart == 0 && scrollCursor > 0){
    scrollCursor--;
    stringStop++;
  } else if (stringStart == stringStop){
    stringStart = stringStop = 0;
    scrollCursor = screenWidth;
  } else if (stringStop == MSG.length() && scrollCursor== 0) {
    stringStart++;
  } else {
    stringStart++;
    stringStop++;
  }

      
   }
}
//  /////////////////////////////////////////// WHAT IF ?(0010) /////////////////////////////////

else if (A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW && D_STATE == LOW ) 
{
  lcd.clear();
  lcd.noBlink();
//  lcd.setCursor(0, 0);
//  lcd.print("Take 4127,and Instl");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("02(12)");
  lcd.setCursor(0, 1);
  lcd.print("Ring by Hand,Install");
  lcd.setCursor(0, 2);
  lcd.print("Above 4127 in Cavi");
//  lcd.setCursor(0, 3);
//  lcd.print("IntSL harnes on PCB");
  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
  lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
  
  while(A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW && D_STATE == LOW)
    {
     ch_bits();
      lcd.setCursor(11, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
      if(tmr>=1000)
      tmr=0;
      
    }
}
 



  /////////////////////////////////////////// WHAT IF ? (0011)/////////////////////////////////

 else if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW  && D_STATE == LOW) {
   lcd.clear();
   lcd.noBlink();
//   lcd.setCursor(0, 0);
//   lcd.print("As per VA4450-787879");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("03(12)");
   lcd.setCursor(0, 1);
   lcd.print("Route harnes as /VA");
   lcd.setCursor(0, 2);
   lcd.print("Plce PCB445-078789");
//   lcd.setCursor(0, 3);
//   lcd.print("On abv assbly,Plce");
  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
    lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr); 

  
   while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW  && D_STATE == LOW)
    {
     ch_bits();
      lcd.setCursor(11, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
    }
}


 /////////////////////////////////////////// WHAT IF ? (0100)/////////////////////////////////

else if (A_STATE == LOW && B_STATE == LOW && C_STATE == HIGH  && D_STATE == LOW) {
   lcd.clear();
   lcd.noBlink();
//   lcd.setCursor(0, 0);
//   lcd.print("Cble Guid On Asbly");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("04(12)");
   lcd.setCursor(0, 1);
   lcd.print("Rout harnes as /VA");
   lcd.setCursor(0, 2);
   lcd.print("Put Adsiv tap On");
//   lcd.setCursor(0, 3);
//   lcd.print("Routed Harnes");

  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
     lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
   while(A_STATE == LOW && B_STATE == LOW && C_STATE == HIGH  && D_STATE == LOW)
    {
     ch_bits();
      lcd.setCursor(11, 3);
      lcd.print("T(SEC):");
      lcd.setCursor(17, 3);
      lcd.print(tmr);
    }
}


  /////////////////////////////////////////// WHAT IF ? (0101)/////////////////////////////////

 else if (A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH  && D_STATE == LOW) {
    lcd.clear();
    lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Instl Harnes Covr");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("05(12)");
    lcd.setCursor(0, 1);
    lcd.print("Help of 3 Screw");
    lcd.setCursor(0, 2);

  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
    lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr); 
   // delay(200);
    while(A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH  && D_STATE == LOW)
    {
   
  ch_bits();
    lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
    }
   //  break;
  }





  /////////////////////////////////////////// WHAT IF ? (0110)/////////////////////////////////

  else if (A_STATE == LOW && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == LOW) {
    
    lcd.clear();
    lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Unlok abv assbly");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("06(12)");
    lcd.setCursor(0, 1);
    lcd.print("From CAvi A Instl");
    lcd.setCursor(0, 2);
    lcd.print("Housing with");
//    lcd.setCursor(0, 3);
//    lcd.print("Notch fit"); 

  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
        lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr); 
    //delay(200);
    while(A_STATE == LOW && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == LOW)
    {
  ch_bits();
    lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
    }
   //  break;
  }



  /////////////////////////////////////////// WHAT IF ? (1110)/////////////////////////////////0

 else  if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == LOW) {
    
    lcd.clear();
    lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Align hol to");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("07(12)");
    lcd.setCursor(0, 1);
    lcd.print("Instl 1 Screw on");
    lcd.setCursor(0, 2);
    lcd.print("Housing");

  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
        lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr); 
   // delay(200);
        while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == LOW)
    {
  ch_bits();
    lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
    }
  }


  /////////////////////////////////////////// WHAT IF ? (1000)/////////////////////////////////

else if (A_STATE == LOW && B_STATE == LOW && C_STATE == LOW  && D_STATE == HIGH) 
{
    lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Plac Unit in B ");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("08(12)");
    lcd.setCursor(0, 1);
    lcd.print("Cavi Fixture");
    lcd.setCursor(0, 2);
    lcd.print("& Lock");

  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
        lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr); 

  while(A_STATE == LOW && B_STATE == LOW && C_STATE == LOW  && D_STATE == HIGH)
   {
     ch_bits();
       lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
    }
   
}


 /////////////////////////////////////////// WHAT IF ? (1001)/////////////////////////////////

else if (A_STATE == HIGH && B_STATE == LOW && C_STATE == LOW  && D_STATE == HIGH) 
{
    lcd.clear();
    lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print("Plc PCBA-4450789");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("09(12)");
    lcd.setCursor(0, 1);
    lcd.print("998 In housing");
    lcd.setCursor(0, 2);
    lcd.print("Conect Harnes to");
//    lcd.setCursor(0, 3);
//    lcd.print("PCBA");

  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
    lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.print(tmr);

  while(A_STATE == HIGH && B_STATE == LOW && C_STATE == LOW  && D_STATE == HIGH)
   {
    ch_bits();
      lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
   }
}


 /////////////////////////////////////////// WHAT IF ? (0101)/////////////////////////////////


else if (A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW  && D_STATE == HIGH) 
{
    lcd.clear();
    lcd.noBlink();
//    lcd.setCursor(0, 0);
//    lcd.print( "Instl Hosing Cvr");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("10(12)");
    lcd.setCursor(0, 1);
    lcd.print("with 4 screw,Instl");
    lcd.setCursor(0, 2);
    lcd.print("Co-x Cvr,Plc 21Lbl");

  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
        lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr); 
    
 while(A_STATE == LOW && B_STATE == HIGH && C_STATE == LOW  && D_STATE == HIGH)
  {
    ch_bits();
      lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
  }
}
  
 /////////////////////////////////////////// WHAT IF ? (1101)/////////////////////////////////

else if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW  && D_STATE == HIGH) {
    lcd.clear();
    
    lcd.noBlink();   
//    lcd.setCursor(0, 0);
//    lcd.print("ORING DIP On &");
  lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("11(12)");
    lcd.setCursor(0, 1);
    lcd.print("Abov AsBly Instl");
    lcd.setCursor(0, 2);
    lcd.print("4 Scre on Cable");
//    lcd.setCursor(0,3);
//    lcd.print("Guide cvr");

  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
    lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr); 
 while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == LOW  && D_STATE == HIGH)
  {
   ch_bits();
     lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
  }
}


/////////////////////////////////////////// WHAT IF ? (0011)/////////////////////////////////

 else if (A_STATE == LOW && B_STATE == LOW && C_STATE == HIGH  && D_STATE == HIGH) {
   lcd.clear();
    lcd.noBlink();
      lcd.setCursor(0, 0);
  lcd.print("Progress:>>> ");
  lcd.setCursor(0, 15);
  lcd.print("12(12)");
    lcd.setCursor(5, 1);
    lcd.print("Task done");
     c_cnt++;
     WriteEpInt(addr,c_cnt);
    Serial.println(ReadEpInt(addr));
    
  lcd.setCursor(0, 3);
  lcd.print("C.CNT:");
  lcd.setCursor(7, 3);
  lcd.print(ReadEpInt(addr));
  lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
   // delay(200);
    while(A_STATE == LOW && B_STATE == LOW && C_STATE == HIGH  && D_STATE == HIGH)
    {
    ch_bits();
      lcd.setCursor(11, 3);
  lcd.print("T(SEC):");
  lcd.setCursor(17, 3);
  lcd.print(tmr);
    }
   //  break;
   }

  


  /////////////////////////////////////////// WHAT IF NOTHIG ? /////////////////////////////////

//ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE ELSE

 else if (A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH  && D_STATE == HIGH) {
   lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("DEFAULT FOE 1101");
   
   // delay(200);
    while(A_STATE == HIGH && B_STATE == LOW && C_STATE == HIGH  && D_STATE == HIGH)
    {
    ch_bits();
    }
   //  break;
  }

  else if (A_STATE == LOW && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == HIGH) {
   lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("DEFAULT FOE 1110");
   
   // delay(200);
    while(A_STATE == LOW && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == HIGH)
    {
    ch_bits();
    }
   //  break;
  }


   else if (A_STATE == HIGH && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == HIGH) {
   lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0, 0);
    lcd.print("DEFAULT FOE 1111");
   
   // delay(200);
    while(A_STATE == HIGH && B_STATE == HIGH && C_STATE == HIGH  && D_STATE == HIGH)
    {
    ch_bits();
    }
   //  break;
  }
}
