# Epuck2 Robot: Tape Follower
This project is designed to make the Epuck2 robot follow a specific color of tape on the ground in order to reach a specified location. The robot uses ChibiOS and multithreading to achieve this goal.

## Requirements
In order to run this project, you will need the following:
- An Epuck2 robot
- A computer with a USB port
- A ChibiOS development environment set up on your computer
- A tape with the desired color

## Setup
- Connect the Epuck2 robot to your computer via USB.
- Clone this repository to your computer.
- Build the project using ChibiOS.
- Upload the compiled code to the Epuck2 robot.
- Place the robot at the starting location, with the tape color selector set to the desired color.
- Set the destination location in the code.

## Usage
Once the robot is set up and the code is uploaded, it will automatically begin following the tape of the specified color. The robot uses multithreading to ensure that it can both follow the tape and avoid obstacles in its path.
If the robot encounters an obstacle, it will use its proximity sensors to determine the best path around it. Once it reaches the destination location, it will stop moving.

## Contributing
If you would like to contribute to this project, please follow these steps:
- Fork this repository.
- Create a new branch: git checkout -b my-new-feature
- Make changes to the codebase.
- Commit your changes: git commit -am 'Add some feature'
- Push the branch to the remote repository: git push origin my-new-feature
- Create a new pull request on GitHub.
  
## Help
If you need help you can refernce the links below:
- [Wiki](https://github.com/Tony-Hany/ROBOTIQUE/wiki)
- [epuck](https://www.gctronic.com/doc/index.php/e-puck2)
- [Cortex-M4](https://developer.arm.com/Processors/Cortex-M4)
