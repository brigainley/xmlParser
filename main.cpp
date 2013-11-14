/*
  * File:   main.cpp
  * Author: Brianna Gainley, brianna_gainley@student.uml.edu
  * With code taken from Jesse M. Heines, from a given partial solution
  *
  * Created on September 16th, 2013
  * Edited on November 4th, 2013
  */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>   
#include <string>   
#include <iomanip>  
#include "auxFunctionsXML.h"

using namespace std;

/** Typical C++ main function
 *  Takes a file and sends it to main auxilliary processing functions
 *  @param argc Number of command line arguments
 *  @param argv Array of pointers to command line arguments
 *  @return 0 Return 0 to indicate exit success
 */
int main(int argc, char** argv) {

    // variable definitions
    ifstream infile( "Doolittle.xml" ) ; //XML file to be read
    
    readFile( infile );
    
    // close the input file to clean up
    infile.close() ;
    
    return 0;
}