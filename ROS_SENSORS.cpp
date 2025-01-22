#include <DHT.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <std_msgs/Float32.h>
#include <ros.h>

// Define pins for the sensors
#define DHTPIN 2       // Pin where the DHT11 is connected
#define DHTTYPE DHT11  // DHT11 sensor type
#define MQ4PIN A0      // Analog pin where MQ-4 is connected

ros::NodeHandle nh;
std_msgs::Float32 sensor1_data_msg;
std_msgs::Float32 sensor2_data_msg;
std_msgs::Float32 sensor3_data_msg;
std_msgs::Float32 sensor4_data_msg;
std_msgs::Float32 sensor5_data_msg;

ros::Publisher sensor1_data_pub("/temp_dht_data", &sensor1_data_msg);
ros::Publisher sensor2_data_pub("/pressure_data", &sensor2_data_msg);
ros::Publisher sensor3_data_pub("/humidity_data", &sensor3_data_msg);
ros::Publisher sensor4_data_pub("/mq4_data", &sensor4_data_msg);
ros::Publisher sensor5_data_pub("/temp_bmp_data", &sensor5_data_msg);
// Initialize the sensors
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp; // BMP280 instance

void setup() { 
    dht.begin();         // Start the DHT11 sensor
    nh.initNode();
    nh.advertise(sensor1_data_pub);
    nh.advertise(sensor2_data_pub);
    nh.advertise(sensor3_data_pub);
    nh.advertise(sensor4_data_pub);
    nh.advertise(sensor5_data_pub);
    if (!bmp.begin(0x76)) {
        nh.loginfo("Could not find a valid BMP280 sensor, check wiring!");
        //while (1);
    }
    nh.loginfo("Sensors are starting...");
}

void loop() {
    // Reading temperature and humidity from DHT11
    float temperatureDHT = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Reading temperature and pressure from BMP280
    float temperatureBMP = bmp.readTemperature();
    float pressure = bmp.readPressure(); // Convert to hPa

    // Reading methane gas level from MQ-4
    int methaneLevel1 = analogRead(MQ4PIN);
    float methaneLevel = static_cast<float>(methaneLevel1);

    // Check if any reads failed and exit early (to try again)
    // if (isnan(temperatureDHT) || isnan(humidity)) 
    //   {
    //     nh.loginfo("Failed to read from DHT sensor!");
    //   }
        sensor1_data_msg.data = temperatureDHT;
        sensor3_data_msg.data = humidity;
        sensor5_data_msg.data = temperatureBMP;
        sensor2_data_msg.data = pressure;
        sensor4_data_msg.data = methaneLevel;

    sensor1_data_pub.publish(&sensor1_data_msg);
    sensor2_data_pub.publish(&sensor2_data_msg);
    sensor3_data_pub.publish(&sensor3_data_msg);
    sensor4_data_pub.publish(&sensor4_data_msg);
    sensor5_data_pub.publish(&sensor5_data_msg);
   
      delay(2000); // Delay for 2 seconds before the next reading
   
      nh.spinOnce();
       delay(10);
}
