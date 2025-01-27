#include <Arduino.h>
#include <ros.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Point.h>
#include <TinyGPSPlus.h>

// ROS NodeHandle
ros::NodeHandle nh;

// ------------------- Steering System ------------------- //

std_msgs::Int16 steer_msg;
int choice;
int input_pwm = 120;

// Define pins
#define dir_fl PB9
#define pwm_fl PB8
#define dir_fr PA1
#define pwm_fr PA2

class Motor {
private:
    int dir_pin;
    int pwm_pin;

public:
    Motor(int pin1, int pin2);
    void clockwise();
    void anticlockwise();
    void pwm(int input_pwm);
};

Motor::Motor(int pin1, int pin2) {
    dir_pin = pin1;
    pwm_pin = pin2;
    pinMode(dir_pin, OUTPUT);
    pinMode(pwm_pin, OUTPUT);
}

void Motor::clockwise() {
    digitalWrite(dir_pin, LOW);
}

void Motor::anticlockwise() {
    digitalWrite(dir_pin, HIGH);
}

void Motor::pwm(int input_pwm) {
    analogWrite(pwm_pin, input_pwm);
}

Motor motorFLS(dir_fl, pwm_fl);
Motor motorFRS(dir_fr, pwm_fr);

void commandCallback(const std_msgs::Int16 &msg) {
    choice = msg.data;
    switch (choice) {
        case 1: // Right Wheel Right
            motorFRS.clockwise();
            motorFRS.pwm(input_pwm);
            break;
        case 2: // Right Wheel Left
            motorFRS.anticlockwise();
            motorFRS.pwm(input_pwm);
            break;
        case 3: // Left Wheel Right
            motorFLS.clockwise();
            motorFLS.pwm(input_pwm);
            break;
        case 4: // Left Wheel Left
            motorFLS.anticlockwise();
            motorFLS.pwm(input_pwm);
            break;
        case 5: // Both Wheels Right
            motorFLS.clockwise();
            motorFRS.clockwise();
            motorFLS.pwm(input_pwm);
            motorFRS.pwm(input_pwm);
            break;
        case 6: // Both Wheels Left
            motorFLS.anticlockwise();
            motorFRS.anticlockwise();
            motorFLS.pwm(input_pwm);
            motorFRS.pwm(input_pwm);
            break;
        case 0: // Stop
            motorFLS.pwm(0);
            motorFRS.pwm(0);
            break;
    }
}

ros::Subscriber<std_msgs::Int16> steer_sub("/rover/steer", commandCallback);

// ------------------- GPS System ------------------- //

HardwareSerial Serial1(PB7, PB6); // GPS communication (RX,TX)
TinyGPSPlus gps;

unsigned long lastUpdate = 0;
const unsigned long updateInterval = 2000;

geometry_msgs::Point gpsData;
ros::Publisher gpsPublisher("/gps/data", &gpsData);

void setup() {
    // Initialize Serial for GPS
    Serial1.begin(9600);

    // Initialize ROS node
    nh.initNode();

    // Advertise and subscribe to ROS topics
    nh.advertise(gpsPublisher);
    nh.subscribe(steer_sub);
}

void loop() {
    // Read GPS data
    while (Serial1.available() > 0) {
        char c = Serial1.read();
        gps.encode(c);
    }

    // Publish GPS data at intervals
    if (millis() - lastUpdate >= updateInterval) {
        lastUpdate = millis();

        if (gps.location.isValid()) {
            gpsData.x = gps.location.lat(); // Latitude
            gpsData.y = gps.location.lng(); // Longitude
            gpsData.z = gps.altitude.meters(); // Altitude

            gpsPublisher.publish(&gpsData);
            nh.loginfo("Published GPS data to /gps/data topic");
        } else {
            nh.logwarn("GPS data invalid");
        }
    }

    // Handle ROS communication
    nh.spinOnce();
    delay(10);
}
