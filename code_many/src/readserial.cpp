/*
 * =====================================================================================
 *
 *       Filename:  readserial.cpp
 *
 *    Description:  From https://majenko.co.uk/blog/reading-serial-arduino, to test
 *
 *        Version:  1.0
 *        Created:  09/19/2022 10:44:13 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

char buf[80];

int readline(int readch, char *buffer, int len) {
    static int pos = 0;
    int rpos;

    if (readch > 0) {
        switch (readch) {
            case '\r': // Ignore CR
                break;
            case '\n': // Return on new-line
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
    return 0;
}

void setup() {
    Serial.begin(115200);
}

void loop() {
    if (readline(Serial.read(), buf, 80) > 0) {
        Serial.print("You entered: >");
        Serial.print(buf);
        Serial.println("<");
    }
}
