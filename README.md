# Desk Light Automation
Individual project for the course "IoT: algorithms and services" at Sapienza Università di Roma Engineering in Computer Science master degree.

[LinkedIn Profile]("https://www.linkedin.com/in/rishiraj-salam-78ba32151/)

### Brief Description
Desk Light Automation is an innovative IoT solution that combines the power of ESP32 microcontroller, ROIT OS (Operating System for Internet of Things), and AWS ecosystem. The project aims to create a smart light for desk setup with real-time monitoring, data analysis, and a user-friendly wed interface.

### Concept

The core concept behind the project is to create a smart light for personal desk setup that detects an individual approaching towards the desk and switch on the lights if the individual stays infront of the desk for atleast 3 seconds. The lights automatically switches off once the individual moves away from the threshold range of the sensor connected to the system. The system can help improve productivity of an individual and can also reduce household energy cosumption. The ESP32 board serves as the central control unit, efficiently processing sensor data and managing the light switch on and off system. Overall, the Desk Light Automation consists of ESP32 board, an Ultrasonic sensor, an LED lamp and automation program to create a productive light management system.

### Components
#### ESP32v3 board & Riot OS
![heltec-esp32](https://github.com/rishiraj09/desk-light-automation/assets/30042823/8b54f5eb-d59a-481f-b2ef-1a1490e5ef0a) ![riotos](https://github.com/rishiraj09/desk-light-automation/assets/30042823/808286de-64d7-43a2-8254-efd7bbd267ef)

The ESP32v3 board is a powerful microcontroller board featuring the ESP32 chip, renowned for its versatility and capabilities. With built-in Wi-Fi and Bluetooth connectivity, ample processing power, and a rich set of I/O interfaces, the ESP32v3 board is an ideal choice for IoT projects, robotics, and advanced embedded systems. It offers an extensive range of functionalities and supports various programming frameworks, making it a reliable and flexible solution for diverse applications. RIOT OS is a lightweight operating system designed specifically for the Internet of Things (IoT), offering low memory footprint and energy-efficient operation. It is valuable for IoT applications as it provides a reliable and scalable platform for managing IoT devices, facilitating seamless communication, and optimizing resource utilization.

#### Ultrasonic sensor HC-SR04
![ultrasonic](https://github.com/rishiraj09/desk-light-automation/assets/30042823/60641abe-1966-4118-9134-02c978349c14)

The HC-SR04 ultrasonic sensor is a popular distance measuring module used in various projects. It utilizes ultrasonic waves to accurately measure distances between objects and the sensor. In this project, the HC-SR04 sensor can be employed to detect the presence of objects near the smart dust bin, triggering the lid to open automatically. By providing precise distance measurements, it ensures efficient and timely lid operation, enhancing the convenience and usability of the system.

#### LED Light
![led](https://github.com/rishiraj09/desk-light-automation/assets/30042823/4d901ed7-40ba-4e77-8bfb-463c76dbc120)

LED lamps are low energy consuming lights which are convinient for desk setup. For the purpose of the project LED lamp will serve as a feedback.

#### Mosquitto MQTT-Broker

Mosquitto is an open-source MQTT broker that facilitates lightweight messaging between devices in an IoT project. In this project, Mosquitto is used to enable efficient and secure communication between the desk-automation-system and other components, such as the ESP32 board and the web interface, ensuring reliable data transmission and real-time updates.

#### AWS Ecosystem

The Desk Light Automation project leverages the power of the AWS ecosystem to enhance its functionality and capabilities. AWS IoT Core enables secure communication between the ESP32 board and the cloud, while Amazon DynamoDB provides efficient storage and retrieval of light switching on events and load measurements. AWS Lambda functions process real-time data, triggering automated actions. Amazon API Gateway offers a secure web interface for users to monitor and control the system, and AWS Amplify simplifies the development of a user-friendly application. Together, these services ensure seamless connectivity, real-time data analysis, controlled access, and an enhanced user experience for the Desk Light Automation project.

![ecosystem](https://github.com/rishiraj09/desk-light-automation/assets/30042823/730e07e1-4bd7-42f6-8abb-b41b2d9fdc9d)

#### Design and Functioning

The design behind Desk Light Automation is as follows, the core sensor module consists of HC-SR04 ultrasonic sensor and the ESP32 microcontroller mounted on the bread board which is to placed near the desk to detect individual presence within a threshold range of 150cm. The core system is then connected to the LED lamp on the desk.

Wokkflow:
* The ultrasonic sensor detects the presence of an individual within the threshold range(150cm).
* When the individual is present (sitting or standing) infront of the desk for at least 2 second the core system triggers the LEP PIN output to high.
* Once the LED pin is high the LED lamp(s) is switched on until the individual leaves from the spot or the individual is beyond the ultrasonic threshold range.

Every time the ultrasonic sensor reads a distance below threshold it sends a message to the Mosquitto MQTT broker which will forward the message to AWS IOT cloud with the help of transparent python bridge. The message will contain the informations that will be displayed on the web interface, such as the date time, the detected distance and the actuale state of the light. The sampling period of two seconds is dued to a compromise within the power consumption and an acceptable responsiveness of the of the model.

The following image represents a prototype of the Desk Light Automation System.

![IMG_2632 (1)](https://github.com/rishiraj09/desk-light-automation/assets/30042823/119b8481-68c0-43ee-97dc-9ff2cb5763b2)

#### Circuit Diagram

![circuit-diagram](https://github.com/rishiraj09/desk-light-automation/assets/30042823/20a3ab67-06a5-4e97-97c8-62d940d6eae9)

#### Hands-On Walkthrough

1. Get RIOT OS
    * Install RiotOS and all its dependencies on your machine by following the instructions in the official repo of the operating system. I suggest to install everything on an Ubuntu machine.

2. Create a new Riot application
    * Go into the examples folder under the Riot base directory.
    * Create a new folder and call it "deskLightAutomation"
    * Paste into the just created folder the files that are into the "code" folder of this repository.

3. Install and configure Mosquitto
    * Download and install the mosquitto MQTT-Broker following the instructions at this link
    * Go into the installation folder (On Ubuntu it's "etc/mosquitto/") and create a new file called "mosquitto.conf" and paste the following lines into it:
        - allow_anonymous true
        - listener 1883

4. Connection to AWS
    * Create an AWS account if you don't have one.

5.  IoT Core
    * Connect a new thing following the instructions given by AWS and download the  SDK package on your pc.
    * Go into "Things" and click on your thing and then go into "Certificates" section. Connect the policy that is under SDK folder downloaded in the previous step and edit the active version as follows: Add the following 5 lines in the JSON document of the policy. The first two under the "Publish" action in the "Resource" section, the following two under "Subscribe" and the last one under "Connect".
        - "arn:aws:iot:eu-west-3:477201098489:topic/desklight"
        - "arn:aws:iot:eu-west-3:477201098489:topic/desklight/data"
        - "arn:aws:iot:eu-west-3:477201098489:topicfilter/desklight"
        - "arn:aws:iot:eu-west-3:477201098489:topicfilter/desklight/data"
        - "arn:aws:iot:eu-west-3:477201098489:client/ESP32"
    * Go into message routing section in the side menu and then into Rules to create a new rule called "desklightRule" and click on the next button.
    * SELECT * FROM 'desklight/data'
    * Choose DynamoDBv2 and then create a new table called "desklightTable" with "timestamp" as partition key attribute.
    * Go back to the rule settings, select the just created table and create a new IAM role "user" and select it.
    * Complete the rule creation.

6. Lambda
    * Create a new python Lambda function, name it "getDesklightData" and paste the code of the same named python script included in this repository.
    * Save changes and deploy your function.
    * Now you must give the lambda function the permission to access a dynamoDB table, to do this search "IAM" in the AWS research bar or click on this link, the go into the "Policy" settings and search "dynamoDB". Click on the first result (It should be something like "amazonDynamoDBFullAccess"), and then into the "Entities attached" section click on "Attach" in order to attach the policy to your lambda function.
    * If you want now you can test your function by clicking on the "Test" button.

7. API Gateway
    * Create a new REST API called "desklightAPI".
    * Click on "Options" into the resource section and create a new "GET" method.
    * Be sure to paste the ARN of your lambda function where requested and
    * Then under the options click on "Enable CORS" and enable it.
    * Finally click on deploy API, select "New phase" and call it "dev". Now you obtained the URL of the API needed in the web app javascript file.

8. Amplify
    * Create a new App and call it "desklightAPP".
    * Choose the option to implement without a git provider.
    * Rename the enviroment to "dev" and drag and drop the folder of the web application of the project.
   
#### How to run the code
1. Go into the Riot application folder:
    * In the Makefile: -- Change the Wi-Fi parameters to the ones that you want to use
    * In the main.c file: -- Change the BROKER_ADDRESS with your IPv4 ip address.
2. Flash the firmware onto your esp32 board using the following command:
    * $ sudo BOARD=esp32s3-devkit BUILD_IN_DOCKER=1 DOCKER="sudo docker" PORT=/dev/ttyUSB0 make all flash
3. Run Mosquitto from its root directory with the command:
    * $ mosquitto -v -c mosquitto.conf
4. Go into the python transparent bridge provided in this repo:
    * Change the BROKER_ADDRESS variable value to yours
    * Change the three paths of root-CA, private-key and certificate.pem to yours.
    * Change the value of AWS endpoint variable to yours
5. Start the bridge with:
    * $ python3 MQTTClient_transparentBridge
6. In the javascript file of the web application make sure to change the URL passed in the "callAPI()" function to the one corresponding to your API endpoint.

Now everything should work and you should start to see the real data updates in the web dashboard. You can see this process in more details by watching the youtube video demonstration of the project.

#### Web Dashboard

#### Video Demonstration

#### Hackster.io Article