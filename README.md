# 2025 UTRAHacks Project - Color Me Buggy
A Coleoptera-looking nimble robot capable of navigating a colorful landscape

Devpost Link: https://devpost.com/software/color-rover#updates

# Description:
Navigating the world requires perception, adaptability, and decision-making—qualities we wanted to instill in our robotic project. Inspired by autonomous rovers used in space exploration and color-sensing robotics in manufacturing, we set out to create a simple but effective rover that could navigate mazes, identify colors, and interact with objects in its environment. Our goal was to make an engaging, interactive robot that could be used for educational purposes, competitions, and real-world applications.

## What it does
Color Me Buggy is an autonomous robot designed to sense colors, navigate mazes, and interact with flags by catching and releasing them. Using a combination of sensors and intelligent decision-making, the rover detects and follows colored pathways, avoids obstacles, and identifies specific flag colors to pick up and drop off at designated zones. Its applications range from robotics education to autonomous navigation research and even gamified obstacle courses.

## How we built it
We built Color Rover using:

Hardware: A compact chassis with wheels, color sensors, ultrasonic sensors for obstacle detection, servo motors for flag handling, and a microcontroller (Raspberry Pi or Arduino).
Software: An Arduino C++ control system that processes sensor inputs and makes real-time navigation decisions.
Navigation Algorithm: A combination of line-following logic, color recognition, and decision trees to ensure the rover can efficiently traverse a maze and interact with objects.
Communication: Wireless connectivity for remote monitoring and potential manual overrides.
Challenges we ran into
Building Color Rover came with its share of challenges:

Color Recognition Accuracy: Lighting conditions affected sensor readings, requiring calibration for reliable color detection.
Maze Navigation Logic: Ensuring the rover could adjust dynamically to obstacles while staying on track was a significant coding challenge.
Flag Handling Mechanism: Designing an efficient catch-and-release system that worked consistently required multiple iterations.
Power Management: Balancing processing power, battery efficiency, and motor control to achieve smooth performance.

## Accomplishments that we're proud of
Successfully integrating color recognition, maze navigation, and flag interaction into one cohesive system.
Achieving real-time decision-making capabilities that allow the rover to adapt to different environments.
Designing a simple but effective flag capture and release mechanism.
Creating an interactive, educational, and competitive robotics project that can be expanded upon for future developments.

## What we learned
The importance of sensor calibration and environmental factors in robotics.
How to refine real-time navigation algorithms for dynamic obstacle avoidance.
The iterative nature of designing and testing hardware mechanisms.
Effective teamwork and problem-solving skills during the hackathon under time constraints.

## What's next for Color Rover
Sensor Fusion for Localization: combination of RPM sensor, ultrasonic and color sensor data to achieve precise navigation through awareness of distance travelled.
Advanced AI Navigation: Implementing machine learning to improve maze-solving efficiency.
Enhanced Flag Interaction: Adding object recognition to distinguish between different types of flags.
Multi-Rover Coordination: Enabling multiple rovers to work together in a competitive or cooperative setting.
Open-Source Expansion: Sharing our code and designs with the robotics community for educational and experimental use.
Larger-Scale Applications: Exploring real-world use cases, such as warehouse automation and search-and-rescue simulations.
Color Rover is just the beginning—we're excited to see where it goes next!