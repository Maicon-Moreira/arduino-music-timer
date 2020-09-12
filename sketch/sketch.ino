int entriesCounter = 0;
long int microsInterval = 0;
bool isClicking = false;
long int lastClick = 0;
long int clickTimes[1000];

void setup() {
  Serial.begin(9600);

  pinMode(52, INPUT);
  pinMode(22, OUTPUT);
}

void loop() {
  int input = digitalRead(52);

  if (input == 1 && !isClicking){
    isClicking = true;

    double currentTime = micros();
    double clickDelay = currentTime - lastClick;

    clickTimes[entriesCounter] = clickDelay;

    entriesCounter ++;
    lastClick = currentTime;

    long int total = 0;
    for (int i = 1; i < entriesCounter; i ++){
       total += clickTimes[i];
    }
    microsInterval = total/(entriesCounter - 1);

    Serial.println("Clique");
    Serial.println(microsInterval);
  }
  
  if (input == 0){
    isClicking = false;  
  }


  if ((micros() - lastClick) % microsInterval < microsInterval*0.5){
    digitalWrite(22, HIGH);  
  }
  else {
    digitalWrite(22, LOW); 
  }
}
