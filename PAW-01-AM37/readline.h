const byte numChars = 32;
char receivedChars[numChars];
char* ReadCOM() {
    char endMarker = '\n';
    int read_bytes = 0;
    Serial.setTimeout(50);
    if(Serial.available()){
        read_bytes = Serial.readBytesUntil(endMarker, receivedChars, numChars - 1);
        if(read_bytes != 0){
            receivedChars[read_bytes] = 0;
            return receivedChars;
        }
    }

    return NULL;
}
