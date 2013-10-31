/*
  * File:   main.cpp
  * Author: Brianna Gainley, brianna_gainley@student.uml.edu
  * With code taken from Jesse M. Heines, from a given partial solution
  *
  * Created on September 16, 2013
  * Edited on October 8th, 2013
  */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>   
#include <string>   
#include <iomanip>  
#include "Element.h"

using namespace std;

// global variables
vector<Element *> vecAllElements;  // vector of pointers to elements
vector<Element * > vecOpenElements; // vecotr of open elements
vector<string> vecString ;  // all lines in file
int lineNum = 0;  // counter to keep track of which line you are on in the file
enum ParserState { UNKNOWN, STARTING_DOCUMENT, DIRECTIVE,
				   ELEMENT_OPENING_TAG, ELEMENT_CONTENT, ELEMENT_NAME_AND_CONTENT,
				   ELEMENT_CLOSING_TAG, SELF_CLOSING_TAG,
				   STARTING_COMMENT, IN_COMMENT, ENDING_COMMENT, ONE_LINE_COMMENT,
				   ERROR } ; // all parser states
ParserState ps = STARTING_DOCUMENT;

// extra function definitions
string openingTag( string strOpening );
void readFile( ifstream& file, vector<string> vecFile );
void printState( ParserState ps, string str );
ParserState determineState( string str );

int main(int argc, char** argv) {

   // variable definitions
   ifstream infile( "Doolittle.xml" ) ; //XML file to be read
   
   readFile( infile, vecString );

   // close the input file to clean up
   infile.close() ;
   
   return 0;
}

// function checks for opening tags for each string in file
string openingTag( string strOpening ) {


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

	return "YA DONE GOOFED";

}

// function reads in file declared in ifstream
void readFile( ifstream& file, vector<string> vecFile ) {
	
	// variable declarations
	bool bContinue = true ;  // loop controller	
    char line[256] ;   // C version of a string
	string str ;   // and single, individual line read from the file
	
	// loop to read lines in continuously and add them each to the end of the vector
    while ( bContinue ) {    
     file.getline( line, 256 ) ;
     str = line ; 
	 lineNum++; // increment line number

	 // if the string length is greater than 0 (if there is another string), continue
     bContinue = ( str.length() > 0 ) ;
     if ( bContinue ) {
      vecString.push_back( str ) ;

	  // print current string
	  cout << str << endl;

	  // determine what the preceding line was and show it
	  ps = determineState( str );
	  printState( ps, str );
	  }	
	}

	return;
}

// function that displays parser state based on enumeration
void printState( ParserState ps, string str ) {
	
	cout << "Parser state = ";
	// switch statement to display parser state
	switch( ps ) {
		case UNKNOWN: cout << "UNKNOWN\n"; break;
		case STARTING_DOCUMENT: cout << "STARTING_DOCUMENT\n"; break;
		case DIRECTIVE: 
			cout << "DIRECTIVE\n"; 
			cout << "Directive = " << str.substr(2, str.length() - 4 ) << endl;
			break;
		case ELEMENT_OPENING_TAG: 
			cout << "ELEMENT_OPENING_TAG\n"; 
			vecOpenElements.push_back(vecAllElements.back());
			cout << "Opening element found: " << vecOpenElements[vecOpenElements.size() - 1] -> getStrElementName() << endl;
			cout << "Stack now contains: ";
			for( int k = 0; k <= vecOpenElements.size() - 1; k++ ) {
				cout << vecOpenElements[k] -> getStrElementName() << " " ;
			}
			cout << "\n\n";
			break;
		case ELEMENT_CONTENT: cout << "ELEMENT_CONTENT\n"; break;
		case ELEMENT_NAME_AND_CONTENT: 
			cout << "ELEMENT_NAME_AND_CONTENT\n"; 
			cout << "Element tag found: " << vecAllElements[vecAllElements.size() - 1] -> getStrElementName() << endl;
			cout << "Element content found: " << vecAllElements[vecAllElements.size() - 1] -> getStrElementContent() << endl;
			cout << "Stack is unchanged.\n";
			break;
		case ELEMENT_CLOSING_TAG: 
			cout << "ELEMENT_CLOSING_TAG\n"; 
			cout << "Element closed: " << vecOpenElements[vecOpenElements.size() - 1] -> getStrElementName() << endl;
			vecOpenElements.pop_back();
			break;
		case SELF_CLOSING_TAG: cout << "SELF_CLOSING_TAG\n"; break;
		case STARTING_COMMENT: cout << "STARTING_COMMENT\n"; break;
		case IN_COMMENT: cout << "IN_COMMENT\n"; break;
		case ENDING_COMMENT: cout << "ENDING_COMMENT\n"; break;
		case ONE_LINE_COMMENT: 
			cout << "ONE_LINE_COMMENT\n"; 
			cout << "Comment = " << str.substr(4, str.length() - 7 ) << endl;
			break;
		case ERROR: cout << "ERROR\n"; break;
		default: cout << "DEFAULT\n"; break;
	}
	cout << endl;
	return;
}

ParserState determineState( string str ) {

	string newElement;
	string elementContent;
	
	// begin enormous if clauses to determine state
	if( str.back() != '>' ) {
		if( ps == STARTING_COMMENT || ps == IN_COMMENT ) {
			ps = IN_COMMENT;
			return ps;
		}
		if( str[0] == '<' && str[1] == '!' && str[2] == '-' && str[3] == '-' ) {
			ps = STARTING_COMMENT;
			return ps;
		}
		else {
			ps = UNKNOWN;
			return ps;
		}
	}
	else if( str.front() != '<' && str[str.length() - 3] == '-' && str[str.length() - 2] == '-' && str.back() == '>' ) {
		ps = ENDING_COMMENT;
		return ps;
	}
	else if( str[0] == '<' && str[1] == '?' ) {
		ps = DIRECTIVE;
		return ps;
	}
	else if( str[0] == '<' && str[1] == '!' && str[2] == '-' && str[3] == '-' ) {
		ps = ONE_LINE_COMMENT;
		return ps;
	}
	else if( str[str.find('<') + 1] == '/' ) {
		ps = ELEMENT_CLOSING_TAG;
		return ps;
	}
	else {		
		newElement = openingTag( str );
		int tmpStrnLen = str.length();
		int tmpElementLen = newElement.length();
		int tmpFirstBracket = str.find( '<' );
		
		tmpFirstBracket++;

		if( str.compare(tmpStrnLen - tmpElementLen - 1, tmpElementLen, newElement) == 0 && str.find( '<', tmpFirstBracket ) != -1 ) { // calls a compare( pos, len, cmpStr ) to check if last part of string is tag again
			ps = ELEMENT_NAME_AND_CONTENT;
			int start = 0;

			start = str.find_first_of( '>', start+1 );

			elementContent = str.substr(start + 1, (str.find_first_of('<', start) - start - 1) ); // finds substring between opening and closing tags
			Element* tmpEl = new Element ( newElement, lineNum, elementContent );  // create a new Element object
			vecAllElements.push_back( tmpEl );  // add the new object to the vector

			return ps;
		}
		else if( str.compare(newElement.length() + 1, 2, "/>") == 0 ) {
			ps = SELF_CLOSING_TAG;

			elementContent = " ";
			Element* tmpEl = new Element ( newElement, lineNum, elementContent );  // create a new Element object
			vecAllElements.push_back( tmpEl );  // add the new object to the vector

			return ps;
		}
		else {
			ps = ELEMENT_OPENING_TAG;

			elementContent = " ";
			Element* tmpEl = new Element ( newElement, lineNum, elementContent );  // create a new Element object
			vecAllElements.push_back( tmpEl );  // add the new object to the vector

			return ps;
		}
	}

	ps = ERROR;
	return ps;
}
