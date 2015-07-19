// Taken Fromhttp://hacking.majenko.co.uk/reading-serial-on-the-arduino
int readline(int readch, char *buffer, int len)
{
  static int pos = 0;
  int rpos;

  if (readch > 0) {
    switch (readch) {
      case '\n': // Ignore new-lines
        break;
      case '\r': // Return on CR
        rpos = pos;
        pos = 0;  // Reset position index ready for next time
        return rpos;
      default:
        if (pos < len-1) {
          buffer[pos++] = readch;
          buffer[pos] = 0;
        }
    }
  }
  // No end of line has been found, so return -1.
  return -1;
}

void setup() {
  Serial.begin(9600);
}

void processPinModeCommand(String pin, String mode) {
  int pinInt = pin.toInt();
  int modeInt = mode.toInt();
  bool modeBool = INPUT;
  if(modeInt==0){
    modeBool = INPUT;
    Serial.print("pin: ");
    Serial.println(pin);
    Serial.println("pin mode: in");
  } else {
    Serial.print("pin: ");
    Serial.println(pin);
    Serial.println("pin mode: out");
    modeBool = OUTPUT;
  }
  
  pinMode(pinInt, modeBool);
}

void digitalOutputCommand(String pin, String value) {
  int pinInt = pin.toInt();
  int valueInt = value.toInt();
  Serial.print("pin: ");
  Serial.println(pin);
  Serial.print("value: ");
  Serial.println(value);
  digitalWrite(pinInt, valueInt);
}

void analogOutputCommand(String pin, String value) {
  int pinInt = pin.toInt();
  int valueInt = value.toInt();
  Serial.print("pin: ");
  Serial.println(pin);
  Serial.print("value: ");
  Serial.println(value);
  analogWrite(pinInt, valueInt);
}

void split(String str, char ch, String splitString[]) {
  //String splitString[8];
  bool done = false;

  int splitIndex = 0;
  int previousIndex = 0;
  while(!done){
    int newIndex = str.substring(previousIndex).indexOf(ch);
    if(newIndex==-1){
      splitString[splitIndex] = str.substring(previousIndex);
      done = true;
    } else {
      splitString[splitIndex] = str.substring(previousIndex, newIndex+previousIndex);
    }
    previousIndex = newIndex+previousIndex+1;
    splitIndex++;
  }
}

void processCommand(String command) {
  String splitString[8];
  split(command, ';', splitString);
  if(splitString[0]=="pm"){
    processPinModeCommand(splitString[1], splitString[2]);
  } else if(splitString[0]=="dw"){
    digitalOutputCommand(splitString[1], splitString[2]);
  } else if(splitString[0]=="aw"){
    analogOutputCommand(splitString[1], splitString[2]);
  }
}

void loop() {
  static char buffer[80];
  if (readline(Serial.read(), buffer, 80) > 0) {
    processCommand(String(buffer));
  }

}
