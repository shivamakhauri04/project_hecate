/**
BSD 3-Clause License
Copyright (c) 2019, Shivam Akhauri,Toyas Dhake
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

/**
* @file main.cpp
* @author Shivam Akhauri, Toyas Dhake
* @date 27 November 2019
* @copyright BSD 3-clause, 2019 Shivam Akhauri,Toyas Dhake
* @brief initializes the RL node.
* calls the navigation functions and the rl-training functions
*/
#include <ros/ros.h>
#include <string>
#include "Navigation.hpp"

/**
* @param argc int
* @param argv char array
* @return 0
* @brief main function 
*/

int main(int argc, char *argv[]) {
    // Initializes roombaRobot package
    ros::init(argc, argv, "hecate");
    // Object initialisation
    Navigation navigation;
    // Start the turtlebot movement
    if (strcmp(argv[1], "test") == 0) {
        // Set parameters for testRobot
        navigation.x_goal = std::stod(argv[3]);  // Initial x coordinate
        navigation.y_goal = std::stod(argv[4]);  // Initial y coordinate
        std::vector<int> state;
        ros::Rate loop_rate(10);                // Set Loop rate
        QLearning qLearning;
        qLearning.getQtable(argv[2]);
        // Run testRobot till ctrl+c is pressed
        while (ros::ok()) {
            navigation.runRobot(std::stod(argv[3]), std::stod(argv[5]),
                               std::stod(argv[6]), qLearning, state, loop_rate);
        }
    } else if (strcmp(argv[1], "train") == 0) {
        // Set parameters for trainRobot
        int highestReward = 0;

        int episodeCount = 0;
        int totalEpisode = 20;

        int innerLoopLimit = 700;   // Number of generation
        int nextStateIndex;

        ros::Rate loop_rate(10);
        // Run trainRobot till ctrl+c is pressed
        while (ros::ok()) {
            navigation.runRobot(argv[2], highestReward, episodeCount,
                       totalEpisode, nextStateIndex, loop_rate, innerLoopLimit);
        }
    }
    return 0;
}
