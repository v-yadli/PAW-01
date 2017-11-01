#define MOUSE_LEFT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

const byte numChars = 32;
char receivedChars[numChars];
char* ReadCOM() {
    char endMarker = '\n';
    int read_bytes = 0;
    Serial.setTimeout(5);
    if(Serial.available()){
        read_bytes = Serial.readBytesUntil(endMarker, receivedChars, numChars - 1);
        if(read_bytes != 0){
            receivedChars[read_bytes] = 0;
            return receivedChars;
        }
    }

    return NULL;
}

void MousePush(int button)
{
    Serial.print("MP,");
    Serial.println(button);
}

void MouseRelease(int button)
{
    Serial.print("MR,");
    Serial.println(button);
}

void MouseMove(int x, int y, int wheel)
{
    Serial.print("MM,");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(wheel);
}
