// ***** Nexa Config

#define TX                D2

#define DELAY_GROUP 2700/2
#define DELAY_HIGH  488/2  //447/2
#define DELAY_LOW   630/2 //670/2

#define REPEAT_N 4

uint8_t rc_2_1_on[]   = {1, 0, 2, 2, 1, 2, 2, 3, 2, 1, 3, 1, 2, 3, 1, 3, 2, 2, 2, 2, 1, 2, 2, 2, 3, 2, 1, 3, 2, 1, 3, 2, 2, 2, 1};
uint8_t rc_2_1_off[]  = {1, 0, 2, 2, 1, 2, 2, 3, 2, 1, 3, 1, 2, 3, 1, 3, 2, 2, 2, 2, 1, 2, 2, 2, 3, 2, 1, 3, 2, 2, 2, 2, 2, 2, 1};




void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");
  pinMode(TX, OUTPUT);
  digitalWrite(TX, LOW);

}

void loop() {

  // Wait for 0 or 1 on serial rx

  if(Serial.available()){
    String str_input = Serial.readStringUntil('\n');
    int input = str_input.toInt();
    if(input){
      Serial.println("Turning ON");
      executeN(rc_2_1_on);
    }
    else {
      Serial.println("Turning OFF");
      executeN(rc_2_1_off);
    }
      
  }

}






uint32_t us_next;
void execute(uint8_t * cmd){

  Serial.println("Executing sequence");

  us_next = micros();
  for(int i=0; i < 35; i++){
    for(int j=0; j < cmd[i]; j++){
      
      digitalWrite(TX, HIGH);
      
      us_next = us_next + DELAY_HIGH;
      while(micros() < us_next){
      }

      digitalWrite(TX, LOW);

      if(j == cmd[i]-1){
        break;
      }
      us_next = us_next + DELAY_LOW;
      while(micros() < us_next){
      }
    }
    us_next = us_next + DELAY_GROUP;
    while(micros() < us_next){
    }
  }
}


void executeN(uint8_t * cmd){
  for(int i = 0; i < REPEAT_N; i++){
    execute(cmd);
    delay(12);
  }
}

