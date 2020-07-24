# **poissoneqn** 
Parallel Plate Capacitor Solution using FDM

## **Description**
This C++ program solves a 2D Poisson Equation for a source as Parallel Plate Capacitor using Finite Difference Method. 

## **Installation and Run the program**
1. Download the source code. 
2. Install this [C++ wrapper](https://github.com/lava/matplotlib-cpp) to plot the figures. 
3. Compile the code using the command in Terminal(in Linux) `g++ main.cpp -std=c++11 -I/usr/include/python2.7 -lpython2.7`
4. To run `./a.out`
5. Input the data for the following variables : length and width of the grid lines, step size, high and low potential.The putput is then saved in the same folder. 

## **To know**
If you find the above installation process for the C++ wrapper complicated(which might be difficult in Windows), you can edit the code and plot the figures in other suitable ways. Some of the options are GNU plot, or saving the data in the form of csv format and plotting in Python. 
To remove the linkage to the wrapper, comment the following lines in poisson.cpp:

**in the header section**.

`#include "matplotlibcpp.h"`

`namespace plt = matplotlibcpp;`


Now you can use the plotcsv() function to create a csv file in the main.cpp. To read the csv, one easy way is python, and the code is present in the folder. 
One easy way to use Python is to use GoogleCollab because most of the packages are already present there. 

Run the python file and make some modification in the nx and ny. And the output will be ready. 

## **References**
You can check out the theory [here](https://my.ece.utah.edu/~ece6340/LECTURES/Feb1/Nagel%202012%20-%20Solving%20the%20Generalized%20Poisson%20Equation%20using%20FDM.pdf) to understand the poisson equation and finite difference method.


If you have any queries, feel free to contact me at reema.shrestha15@gmail.com. 
