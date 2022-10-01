//Homework 5

/*
 *  Filename:           main.cpp
 * 
 *  Purpose:            The purpose of this program is to read input from a 
 *                      txt file, and write output to a txt file. The 
 *                      information read in is in the order last name, 
 *                      first name, salary, and percent raise. The output 
 *                      text file will write data in the order of first name, 
 *                      last name, and new salary.
 * 
 *  Author:             Zachary Charles Stewart
 *  Student ID:         105903414
 *  Date:               1/26/2017 12:13 PST
 */

#include<iostream>      //<< and >> operators
#include<iomanip>       //setw() function
#include<cstdlib>       //exit(EXIT_SUCCESS)
#include<fstream>       //ifstream, ofstream
#include<string>        //string class
#include<locale>        //locale to be imbued
#include<algorithm>     //count function
#include<sstream>       //stringstream

using namespace std;

//User defined function to covert a double to its dollar amount
//Accomplished with the imbue function and a stringstream
string dollarConvert(double amt)
{
    stringstream dollarAmt;
    dollarAmt.imbue(locale("en_US.UTF8"));
    dollarAmt << fixed << showpoint << setprecision(2) << amt;
    return dollarAmt.str();
}

int main(int argc, char** argv)
{
    //Declare variables for use in program
    string name_First, name_Last, name_Full;
    double salary, raise, per_raise, sal2;
    int fileLength, sal1;
    
    //Declare file stream variables
    ifstream inData;
    ofstream outData;
    
    //Associate the file stream variables with input and output txt files
    inData.open("SalaryData.txt");
    
    if(!inData)
    {
        cout << "Failed to open file" << endl;
        exit(EXIT_FAILURE);
    }
    outData.open("SalaryRaises.txt");
    
    //Determine length of file to be used with for loop
    fileLength = count(istreambuf_iterator <char> (inData), 
                       istreambuf_iterator <char> (), '\n');
    
    //Return to beginning of file
    inData.seekg(0);
    
    //Do while to traverse through txt file
    for(int i = 0; i < fileLength; i++)
    {
        //Read data in from SalaryData.txt
        inData >> name_Last >> name_First >> salary >> per_raise;
        
        //Determine full name
        name_Full = name_First + " " + name_Last;
        
        //Compute raise
        raise = salary * (per_raise / 100.0);
        
        //Add raise to salary
        salary = salary + raise;
                
        //Write data out to SalaryRaises.txt
        outData << fixed << showpoint << setprecision(2) << setw(14) << left;  
        outData << name_Full << "\t" << "$" << dollarConvert(salary) << endl;
    }
    
    //Close the text files upon completion
    inData.close();
    outData.close();
    
    //Terminate program upon successful completion
    exit(EXIT_SUCCESS);
}
