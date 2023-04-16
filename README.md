# Hexagon_Challenge
Code developed for the Control Analist position in the R&D division in Hexagon Agriculture
Candidate: Arthur Schmietke Czech
Date: April 15th, 2023
This code was developed in order to implement an algorithm capable of opening a data file
containing the X, Y and Z accelerations from a MMA8451 accelerometer test, parsing said data,
estimate the roll and pitch angles and save the reults in an output file. For conducting this
activity an application note (provided by Hexagon Agriculture) was used. The equations used
from this document are disclosed in the comments below. The rotation sequence used was xyz.

The input file must have the values separated by ';' for the algorithm to work correctly, and its structur must be as follows:
Fisrt column: Timestamp; Second column: X acceleration; Third column: Y acceleration; Fourth column: Z acceleration.
.
The otput file structure is as follows: Fisrt column: Timestamp; Second column: Roll angle in degrees; Third column: Pitch angle in degrees.

This code was developed in Linux Mint 21 OS. For the file to be compiled, the terminal must be open in this directory, and the following command line
must be used:

g++  vehicle_attitude.cpp -o exam

For the executable file to be executed, this command line must be used:

./exam
