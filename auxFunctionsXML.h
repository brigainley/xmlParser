/*
 * File:   auxFunctionsXML.h
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 *
 * Created on November 4th, 2013
 */

    #ifndef AUXFUNCTIONSXML_H
    #define AUXFUNCTIONSXML_H
    
    #include <string>
    #include <iostream>
    
    using namespace std;

    /** readFile reads in the file declared in ifstream in main
     *  Pushes each line of file onto the tail of the file vector individually
     *  @param file The XML file read in from main
     */
    void readFile( ifstream& file );
  
    #endif  