#include <wiringPi.h>
#include <stdio.h>


#define TRIG1 8
#define ECHO1 9
#define LED1  7

#define TRIG2 0
#define ECHO2 2
#define LED2  3

double distance1 = 0.0;
double distance2 = 0.0;

// Initializes the ultrasonic sensor by setting up the TRIG, ECHO, and LED pins.
void initSensor(int trig, int echo, int led)
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(led, OUTPUT);

    digitalWrite(trig, LOW);
}

// Initializes the wiringPi library and sets up the ultrasonic sensors, and LED
void setup()
{
    wiringPiSetup();

    initSensor(TRIG1, ECHO1, LED1);
    initSensor(TRIG2, ECHO2, LED2);

    delay(30);
}

double getDistance(int trig, int echo)
{
    // Trigger the ultrasonic pulse
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    // Wait for the ECHO pin to go HIGH
    while (digitalRead(echo) == LOW);

    // Record the start time
    long startTime = micros();

    // Wait for the ECHO pin to go LOW
    while (digitalRead(echo) == HIGH);

    // Calculate the travel time of the pulse
    long travelTime = micros() - startTime;

    // Calculate the distance
    double distance = (travelTime / 2.0) * 0.0343;

    return distance;
}

void controlLED(int led, double distance, double threshold)
{
    // Control the LED based on the distance compared to the threshold
    if (distance <= threshold)
    {
        digitalWrite(led, HIGH);
    }
    else
    {
        digitalWrite(led, LOW);
    }
}

int main(void)
{
    setup();

    while (1)
    {
        distance1 = getDistance(TRIG1, ECHO1);
        distance2 = getDistance(TRIG2, ECHO2);

        // Control LEDs based on the distances
        controlLED(LED1, distance1, 30.0);
        controlLED(LED2, distance2, 30.0);

        delay(500);
    }

    return 0;
}
