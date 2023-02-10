# Sun_Water_Heater

This project demonstrates the control of a water heater using the sun as the energy source. It uses a combination of sensors and actuators to monitor and control the temperature of the water. The project is also integrated with Firebase and a Flutter app, which serves as the graphical user interface (GUI) for controlling the water heater.

## Getting Started

To get started with this project, you will need the following hardware components:

- Arduino board
- Sensors (e.g. temperature sensor)
- Actuators (e.g. relay)
- Solar panel

You will also need to install the Arduino software on your computer, which is available for free from the [Arduino website](https://www.arduino.cc/en/software). In addition, you will need to set up a Firebase account and install the Flutter framework on your computer to develop the GUI app.

## Project Overview

The project works by using the solar panel to power the water heater. The temperature sensor is used to monitor the temperature of the water, and the relay is used to control the power supply to the water heater. The data from the temperature sensor is sent to Firebase, where it can be accessed by the Flutter app. The Flutter app allows the user to set the desired temperature for the water and to monitor the current temperature in real-time.

## Setting up Firebase

To set up Firebase, you will need to create a new project and add the necessary configurations to the Arduino code. The Firebase documentation provides detailed instructions on how to set up a new project and integrate it with the Arduino platform.

## Developing the GUI App

The GUI app is developed using the Flutter framework. The app allows the user to set the desired temperature for the water and to monitor the current temperature in real-time. The app communicates with Firebase to retrieve the temperature data and to control the relay.

## Contributions

We welcome contributions to this project. If you have suggestions or improvements, please feel free to submit a pull request.

## License

This project is licensed under the MIT License. Please see the [LICENSE](LICENSE) file for more information.
