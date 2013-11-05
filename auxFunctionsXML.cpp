/* File: auxFunctionsXML.cpp
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 
 * Created 11/4/13
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>   
#include <string>   
#include <iomanip>  
#include "element.h"
#include "auxFunctionsXML.h"

using namespace std;
 
// global variables
/**
 *  All possible parser states
 */
 enum ParserState { UNKNOWN, STARTING_DOCUMENT, DIRECTIVE,
    ELEMENT_OPENING_TAG, ELEMENT_CONTENT, ELEMENT_NAME_AND_CONTENT,
    ELEMENT_CLOSING_TAG, SELF_CLOSING_TAG,
    STARTING_COMMENT, IN_COMMENT, ENDING_COMMENT, ONE_LINE_COMMENT,
    ERROR };
vector<Element *> vecAllElements;  // vector of pointers to elements
vector<Element *> vecOpenElements; // vecotr of open elements
vector<string> vecString ;  // all lines in file
int lineNum = 0;  // counter to keep track of which line you are on in the file
ParserState ps = STARTING_DOCUMENT; // sets initial global parser state

// helper functions, see above each definition for JavaDocs commentary
string openingTag( string strOpening );
void printState( ParserState ps, string str );
ParserState determineState( string str );
 
/** openingTag checks for opening tags for each line in file
 *  Only called if an element opening tag is found in parser state reading function
 *  @param strOpening Newest line read in from XML file and added to the tail of the vector
 *  @return Returns a string containing the element opening tag itself
 */
string openingTag( string strOpening ) {

    size_t strBegin, strRB, strSpace;
    
    strBegin = strOpening.find( "<" ); // find position of '<' character
    
    // check to make sure next character is not ?, !, or /
    if( strOpening.at(strBegin + 1) != '?' && strOpening.at(strBegin + 1) != '!' && strOpening.at(strBegin + 1) != '/' ) {
        
        strSpace = strOpening.find( " ", strBegin ); // see if any spaces exist in tag after LB
        strRB = strOpening.find( ">" ); // find close of opening tag
    
        // construct new string with what is in between open and close tags
        if( strSpace == -1 || strRB < strSpace ) {
            string strFind( strOpening.begin() + strBegin + 1, strOpening.begin() + strRB ); 
            return strFind;
        }
    
        // else, construct new string with what is in between open tag and space
        else if( strSpace < strRB ) {
            string strFind( strOpening.begin() + strBegin + 1, strOpening.begin() + strSpace ); 
            return strFind;
        }
    }

    return "YA DONE GOOFED"; // ERROR - should never get here!
}

/** readFile reads in the file declared in ifstream in main
 *  Pushes each line of file onto the tail of the file vector individually
 *  @param file The XML file read in from main
 */
void readFile( ifstream& file ) {
	
	bool bContinue = true;  // loop controller	
    char line[256];   // C version of a string, needed for file.getline()
	string str;   // single, individual line read from the file
	
	// loop to read lines in continuously and add them each to the end of the vector
    while ( bContinue ) {    
     file.getline( line, 256 );
     str = line; 
	 lineNum++; 

	 // if the next string length is greater than 0 (if there is another string), continue
     bContinue = ( str.length() > 0 );
     if ( bContinue ) {
      vecString.push_back( str );

	  // print current string
	  cout << str << endl;

	  // determine what state the parser is in after the line just read and print it
	  ps = determineState( str );
	  printState( ps, str );
	  }	
	}

	return;
}

/** printState that displays parser state based on global enumeration
 *  @param ps The current state of the parser
 *  @param str The last line read in from the file
 */
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

/** determineState figures out the current state of the parser based on the file line just read 
 *  @param str The last line read in from the XML file
 *  @return Returns a new ParserState 
 */
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
            int end = 0;
    
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
