/*
  * File:   main.cpp
  * Author: Brianna Gainley, brianna_gainley@student.uml.edu
  * With code taken from Jesse M. Heines, from a given solution
  *
  * Created on September 16, 2013
  */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>   // added after class
#include <string>   // added after class
#include <iomanip>  // added after class
#include "Element.h"

using namespace std;

string checkStr( string strOpening ); // declaration for function to check content of string

int main(int argc, char** argv) {

   vector<Element *> vecElementPtrs;  // vector of pointers to elements
   vector<string> vecString ;  // all lines in file
   string str ;   // and single, individual line read from the file

   ifstream infile( "Doolittle.xml" ) ; //XML file to be read
   
   bool bContinue = true ;  // loop controller
   char line[256] ;   // C version of a string
   int lineNum = 0;  // counter to keep track of which line you are on in the file
   string tmpString;
   int test = 0;

   // loop to read lines in continuously and add them each to the end of the vector
   while ( bContinue ) {    
     infile.getline( line, 256 ) ;
     str = line ; 
	 test++;
	 lineNum++; // increment line number

     bContinue = ( str.length() > 0 ) ;
     if ( bContinue ) {
      vecString.push_back( str ) ;  

	  tmpString = checkStr( str ); // check string function to see if there is an opening tag

		if( tmpString != "NULL" ) { // if there was a useful string detected
			Element* tmpEl = new Element ( tmpString, lineNum );  // create a new Element object
			vecElementPtrs.push_back( tmpEl );  // add the new object to the vector
		}	
	 }

   }

   // close the input file to clean up
   infile.close() ;
   
   // output a confirmation message to the user
   cout << "The program read " << vecString.size() << 
           " lines from the file." << endl ;
   
   // print the lines read
   cout << endl ;
   for ( int k = 0 ; k < vecString.size() ; k++ ) {
     cout << std::setw( 3 ) << k+1 << ":  " << vecString.at( k ) << endl ;
   }

   // start printing elements
   cout << endl << "/********************ELEMENT NAMES************************/" << endl;

   // print the elements found and their line numbers
   cout << endl;
   for( int k = 0; k < vecElementPtrs.size(); k++ ) {
	   cout << std::setw( 3 ) << vecElementPtrs[k] -> getNLineNo() << ":  " << vecElementPtrs[k] -> getStrElementName() << endl;
   }

   return 0;
}



// function checks for opening tags for each string in file
string checkStr( string strOpening ) {

	size_t strBegin;
	size_t strRB;
	size_t strSpace;

	strBegin = strOpening.find( "<" ); // find position of '<' character

	// check to make sure next character is not ?, !, or /
	if( strOpening.at(strBegin + 1) != '?' && strOpening.at(strBegin + 1) != '!' && strOpening.at(strBegin + 1) != '/' ) {
		
		strSpace = strOpening.find( " ", strBegin ); // see if any spaces exist in tag after LB
		strRB = strOpening.find( ">" ); // find close of opening tag

		if( strSpace == -1 || strRB < strSpace ) {
			string strFind( strOpening.begin() + strBegin + 1, strOpening.begin() + strRB ); // construct new string with what is in between open and close tags
			return strFind;
		}

		else if( strSpace < strRB ) {
			string strFind( strOpening.begin() + strBegin + 1, strOpening.begin() + strSpace ); // construct new string with what is in between open tag and space
			return strFind;
		}
	}

	return "NULL";

}

