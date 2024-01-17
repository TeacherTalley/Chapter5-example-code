#include <iostream>
#include <iomanip>
#include <fstream>
/**
* ---------------------------------------------------------------------
* @copyright
* Copyright 2024 Michelle Talley University of Central Arkansas
*
* @author: <Student name>
* @course: Data Structures (CSCI 2320)
*
* @file main.cpp
* @brief Driver program for Chapter 5 Example code
*        Demonstrates uslse of cin and cout
*        Demonstrates use of string
-----------------------------------------------------------------------
*/

const std::string defaultInputFile = "input.txt";
const std::string defaultOutputFile = "output.txt";

void demo(bool openInputFile, std::string inputFilename,bool openOutputFile, std::string outputFilename)
{
    // Save the original stream buffers for cout and cin
    std::streambuf* stream_buffer_cout = std::cout.rdbuf();
    std::streambuf* stream_buffer_cin = std::cin.rdbuf();

    // Declare streams outside the if block
    std::ifstream inputFileHandle(inputFilename);
    std::ofstream outputFileHandle(outputFilename);

    // Change cin and cout to files if specified
    if (openInputFile)
    {
        // Redirect cin to input file
        std::streambuf* stream_buffer_cin = std::cin.rdbuf(inputFileHandle.rdbuf());
        if (openOutputFile)
        {
            // Redirect cout to output file
            // Open output file and override use of cout to file name
            std::streambuf* stream_buffer_cout = std::cout.rdbuf(outputFileHandle.rdbuf());
        } 
    }

    // Example using cout and cin, input operator and output operator
    // integer
    int age;
    std::cout << "Enter your age: ";
    std::cin >> age;

    std::cout << "You are " << age << " years old" << std::endl;

    // Example using cout and cin, input operator and output operator
    // float
    float pay;
    std::cout << "Enter your pay in dollars: ";
    std::cin >> pay;

    // Example using cout, output operator with errors
    std::cout << "You are paid " << pay << " dollars." << std::endl;

    // print out of cin flags
    std::cout << std::endl;
    std::cout << "cin.good() = " << std::boolalpha << std::cin.good() << std::endl;
    std::cout << "cin.fail() = " << std::boolalpha << std::cin.fail() << std::endl;
    std::cout << "cin.eof() = " << std::boolalpha << std::cin.eof() << std::endl;
    std::cout << "cin.bad() = " << std::boolalpha << std::cin.bad() << std::endl;

    if (openInputFile) 
    {
        // restore cin to standard input
        std::cin.rdbuf(stream_buffer_cin);
        if (openInputFile) 
        {
            std::cin.rdbuf(stream_buffer_cout);
        }
    }
    else 
    {
        // remove output file (this is goofy, but works for now)
        std::remove(outputFilename.c_str());
    }
}
int main(int argc, char** argv)
{
    bool openInputFile = false;
    bool openOutputFile = false;
    std::string inputFilename = defaultInputFile;
    std::string outputFilename = defaultOutputFile;

    // options to run this program
    // option 1 - accept user input
    // ./main
    // option 2 - accept input from file (ONLY WORKS ON LINUX)
    // cat ./input.txt | ./main
    // option 3 - open an input file by name
    // ./main ./input.txt
    // option 4 - open an input file by name and output to a file
    // ./main ./input.txt ./output.txt
    
    if (argc > 0)
    {
        std::cout << "argc = " << argc << std::endl;
        std::cout << "argv[0] = " << argv[0] << std::endl;
    }
    if (argc > 1){
        std::cout << "argv[1] = " << argv[1] << std::endl;
        inputFilename = argv[1];
        openInputFile = true;
    }
    if (argc > 2){
        std::cout << "argv[2] = " << argv[2] << std::endl;
        outputFilename = argv[2];
        openOutputFile = true;
    }
    if (argc > 3)
    {
        std::cout << "Usage: " << argc << "[input file] [output file]" << std::endl;
        return(1);
    }

    std::cout << std::endl;
    demo(openInputFile, inputFilename, openOutputFile, outputFilename);
    return 0;
}