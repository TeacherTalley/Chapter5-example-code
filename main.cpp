#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
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

// Demo cin and cout
void demo_io()
{
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
}

// Demo string behavior
void demo_strings()
{
    // Creating an empty string
    std::cout << std::endl
              << "String examples" << std::endl;
    std::string myString;
    std::cout << "myString = " << myString << std::endl;
    std::cout << "myString.empty(): " << std::boolalpha << myString.empty() << std::endl;

    // Creating a string with an initialized value
    std::string myCourse("Data Structures");
    std::cout << myCourse << std::endl;
    std::cout << "myCourse.at(2): " << myCourse.at(2) << std::endl;

    // Concatenating strings
    std::string myFullCourse = myCourse + " (CSCI 2320)";
    std::cout << myFullCourse << std::endl;

    // Getting a c-style string (char array) from a string
    const char *myCourseCString = myCourse.c_str();
    std::cout << "myCourseCString = " << myCourseCString << std::endl;

    std::cout << "myCourse[3] = " << myCourse[3] << std::endl;
}

// Demo opening, reading, writing, and closing files
void demo_io2(std::string inputFilename, std::string outputFilename)
{
    std::cout << "Reading: " << inputFilename << std::endl;
    std::cout << "Writing: " << outputFilename << std::endl;

    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename);

    if (!inputFile)
    {
        std::cerr << "Unable to open input file: " << inputFilename << std::endl;
        return;
    }

    if (!outputFile)
    {
        std::cerr << "Unable to open output file 2: " << outputFilename << std::endl;
        return;
    }

    std::string line;
    while (getline(inputFile, line))
    {
        outputFile << line << '\n';
    }
}

// Demo cin and cout - This code is not run in the main function
void demo_io_bonus(bool openInputFile, std::string inputFilename, bool openOutputFile, std::string outputFilename)
{
    // BONUS code
    // This code will override cin and cout to use files if specified
    // Save the original stream buffers for cout and cin
    std::streambuf *stream_buffer_cout = std::cout.rdbuf();
    std::streambuf *stream_buffer_cin = std::cin.rdbuf();

    // Declare streams outside the if block
    std::ifstream inputFileHandle(inputFilename);
    std::ofstream outputFileHandle(outputFilename);

    // Change cin and cout to files if specified
    if (openInputFile)
    {
        // Redirect cin to input file
        std::streambuf *stream_buffer_cin = std::cin.rdbuf(inputFileHandle.rdbuf());
        if (openOutputFile)
        {
            // Redirect cout to output file
            // Open output file and override use of cout to file name
            std::streambuf *stream_buffer_cout = std::cout.rdbuf(outputFileHandle.rdbuf());
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
        if (openOutputFile)
        {
            // restore cout to standard input
            std::cout.rdbuf(stream_buffer_cout);
        }
    }
    else
    {
        // remove output file (this is goofy, but works for now)
        std::remove(outputFilename.c_str());
    }
}

int main(int argc, char **argv)
{
    bool openInputFile = false;
    bool openOutputFile = false;
    std::string inputFilename = defaultInputFile;
    std::string outputFilename = defaultOutputFile;

    demo_io();
    demo_io2(inputFilename, outputFilename);
    std::cout << std::endl;
    demo_strings();
    return 0;
}