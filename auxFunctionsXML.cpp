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
#include "attribute.h"
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
    
/** vector of pointers to all elements */
vector<Element *> vecAllElements; 

/** vector of open elements */
vector<Element *> vecOpenElements;

#pragma region VARIABLES
/** all lines in a file */
vector<string> vecString ;

/** counter to keep track of what line in the file you're on */
int lineNum = 0;

/** indentation level */
int indentLvl = 0; 

/** sets initial global parser state */
ParserState ps = STARTING_DOCUMENT;

// helper functions, see above each definition for JavaDocs commentary
string openingTag( string strOpening );
void printState( ParserState ps, string str, ofstream& file );
ParserState determineState( string str );
string trim( string& str );
void findAttr( string strFull, size_t spacePos );
void printTree( ofstream& xmlTreeFile, int vectorPos );

#pragma endregion VARIABLES
 
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
	ofstream parserStateFile; // file to which parserStates will be output
	ofstream xmlTreeFile; // writes tree structure with children and attributes to file
	
	parserStateFile.open("parserStates.txt"); // creates text file for parser states
	xmlTreeFile.open("xmlTreeFile.txt"); // creates text file for tree structure
	    
    // loop to read lines in continuously and add them each to the end of the vector
    while ( file.getline( line, 256 ) ) {    
        bContinue = true;
        str = line; 
        str = trim(str);
        lineNum++; 

        if ( bContinue ) {
        vecString.push_back( str );

        // print current string
        parserStateFile << str << endl;

        // determine what state the parser is in after the line just read and print it
        ps = determineState( str );
        printState( ps, str, parserStateFile );
        }	
    }

	printTree( xmlTreeFile, 0 );

	parserStateFile.close();
	xmlTreeFile.close();
	cout << "\nProgram Success. See output files." << endl;
	return;
}

/**
 *  Trim leading and trailing white space (spaces and tabs) from the string
 *  passed as an argument and return the trimmed string
 *  @param str The string being trimmed
 *  @return The trimmed string
 */
string trim( string& str ) {
	while( str[0] == ' ' || str[0] == '\t' || str[0] == '\r' ) {
		str.erase( str.begin() );
	}
	while( str[str.length() - 1] == ' ' || str[str.length() - 1] == '\t'  || str[str.length() - 1] == '\r' ) {
		str.erase( str.end() - 1 );
	}
	return str;
}

/** 
 *  findAttr finds attributes within the line and adds them
 *  to the current element's attribute vector
 *  @param strFull The full string of the current line
 *  @param spacePos The position of the first space in the tag 
 */
void findAttr( string strFull, size_t spacePos ) {
    size_t newSpacePos, strBegin, equalSign, nextQuote;
     
	if( spacePos == 0 ) spacePos = strFull.find( ' ' );
    if( spacePos == -1 ) return;
    
    strBegin = spacePos + 1; // find position of character after first space        
    newSpacePos = strFull.find( ' ', strBegin ); // see if any spaces exist in tag after last space
    equalSign = strFull.find( '=', strBegin ); // finds equal sign
	nextQuote = strFull.find( '"', equalSign + 3 );
    
    string strName( strFull, strBegin, equalSign - strBegin ); // construct new strings using original string
    string strContent( strFull, equalSign + 2, nextQuote - ( equalSign + 2 ));
    
    Attribute* tmpAttr = new Attribute ( strName, lineNum, strContent );  // create a new Attribute object
    vecAllElements.back() -> setNewAttribute( tmpAttr ); // add the new object to the vector of attributes

    findAttr( strFull, newSpacePos );
    
}

/** printState that displays parser state based on global enumeration
 *  @param ps The current state of the parser
 *  @param str The last line read in from the file
 */
void printState( ParserState ps, string str, ofstream& parserStateFile ) {
	
    parserStateFile << "Parser state = ";
    // switch statement to display parser state
    switch( ps ) {
        case UNKNOWN: parserStateFile << "UNKNOWN\n"; break;
        case STARTING_DOCUMENT: parserStateFile << "STARTING_DOCUMENT\n"; break;
        case DIRECTIVE: 
            parserStateFile << "DIRECTIVE\n"; 
            parserStateFile << "Directive = " << str.substr(2, str.length() - 4 ) << endl;
            break;
        case ELEMENT_OPENING_TAG: 
            parserStateFile << "ELEMENT_OPENING_TAG\n"; 
            vecOpenElements.push_back(vecAllElements.back());
            parserStateFile << "Opening element found: " << vecOpenElements[vecOpenElements.size() - 1] -> getStrElementName() << endl;
            parserStateFile << "Stack now contains: ";
            for( int k = 0; k <= vecOpenElements.size() - 1; k++ ) {
                parserStateFile << vecOpenElements[k] -> getStrElementName() << " " ;
            }
            parserStateFile << "\n\n";
            break;
        case ELEMENT_CONTENT: parserStateFile << "ELEMENT_CONTENT\n"; break;
        case ELEMENT_NAME_AND_CONTENT: 
            parserStateFile << "ELEMENT_NAME_AND_CONTENT\n"; 
            parserStateFile << "Element tag found: " << vecAllElements[vecAllElements.size() - 1] -> getStrElementName() << endl;
            parserStateFile << "Element content found: " << vecAllElements[vecAllElements.size() - 1] -> getStrElementContent() << endl;
            parserStateFile << "Stack is unchanged.\n";
            break;
        case ELEMENT_CLOSING_TAG: 
            parserStateFile << "ELEMENT_CLOSING_TAG\n"; 
            parserStateFile << "Element closed: " << vecOpenElements[vecOpenElements.size() - 1] -> getStrElementName() << endl;
            vecOpenElements.pop_back();
            parserStateFile << "Stack now contains: ";
            for( int k = 0; k <= vecOpenElements.size() - 1; k++ ) {
                if( vecOpenElements.size() == 0 ) break;
                parserStateFile << vecOpenElements[k] -> getStrElementName() << " " ;
            }
            parserStateFile << "\n\n";
            break;
        case SELF_CLOSING_TAG: parserStateFile << "SELF_CLOSING_TAG\n"; break;
        case STARTING_COMMENT: parserStateFile << "STARTING_COMMENT\n"; break;
        case IN_COMMENT: parserStateFile << "IN_COMMENT\n"; break;
        case ENDING_COMMENT: parserStateFile << "ENDING_COMMENT\n"; break;
        case ONE_LINE_COMMENT: 
            parserStateFile << "ONE_LINE_COMMENT\n"; 
            parserStateFile << "Comment = " << str.substr(4, str.length() - 7 ) << endl;
            break;
        case ERROR: parserStateFile << "ERROR\n"; break;
        default: parserStateFile << "DEFAULT\n"; break;
    }
    parserStateFile << endl;
    return;
}

/** printTree prints the state of the XML tree with attributes and child levels 
 *  @param xmlTreeFile The file where all output is being saved
 *  @param vectorPos The new position of elements to be sorted and their children
 */
void printTree( ofstream& xmlTreeFile, int vectorPos ) {

	int newVecPos = vectorPos + 1, numberOfChildren = 0;

	// cycle through until end of vector is reached
	if( vectorPos < vecAllElements.size() ) {

		// print indent asterisks for visual output
		for( int i = 1; i < vecAllElements.at(vectorPos) -> getIndentationLevel(); i++ ) {
			xmlTreeFile << "* ";
		}

		// print element name and line number
		xmlTreeFile << "Element \"" << vecAllElements.at(vectorPos) -> getStrElementName() << "\" was found at line " 
			<< vecAllElements.at(vectorPos) -> getNLineNo() << " with ";

		// print content if there is any
		if( vecAllElements.at(vectorPos) -> getStrElementContent() != " " ) {
			xmlTreeFile << "\"" << vecAllElements.at(vectorPos) -> getStrElementContent() << "\" content, ";
		}
		else {
			xmlTreeFile << "no content, ";
		}

		// print attributes 
		if( vecAllElements.at(vectorPos) -> getVecAttributeSize() != 0 ) {
			for( int i = 0; i < vecAllElements.at(vectorPos) -> getVecAttributeSize(); i++ ) {
				xmlTreeFile << "attribute \"" << vecAllElements.at(vectorPos) -> getAttributeName(i) << "\"";
				xmlTreeFile << " with attribute content \"" << vecAllElements.at(vectorPos) -> getAttributeContent(i) << "\", ";
			}
		}
		else xmlTreeFile << "with no attributes ";
		// print number of children
		xmlTreeFile << "and "; 

		if( newVecPos < vecAllElements.size() ) { // check if this is the last element in tree
			while( vecAllElements.at(newVecPos) -> getIndentationLevel() != vecAllElements.at(vectorPos) -> getIndentationLevel() ) {
				numberOfChildren++;
				newVecPos++;
				if( newVecPos >= vecAllElements.size() ) break;
			}
		}
		else numberOfChildren = 0;

		xmlTreeFile << numberOfChildren << " children." << endl;

		newVecPos = vectorPos + 1;

		// call function recursively to traverse entire tree
		printTree( xmlTreeFile, newVecPos );
	}
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
    if( str[str.length()-1] != '>' ) {
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
        indentLvl--;
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
			Element* tmpEl = new Element ( newElement, lineNum, elementContent, indentLvl + 1 );  // create a new Element object
            vecAllElements.push_back( tmpEl );  // add the new object to the vector
			findAttr(str, 0); // use function again to find attributes
    
            return ps;
        }
        else if( str.compare(newElement.length() + 1, 2, "/>") == 0 ) {
            ps = SELF_CLOSING_TAG;
    
            elementContent = " ";
			Element* tmpEl = new Element ( newElement, lineNum, elementContent, indentLvl );  // create a new Element object
            vecAllElements.push_back( tmpEl );  // add the new object to the vector
			findAttr(str, 0); // use function again to find attributes
    
            return ps;
        }
        else {
            ps = ELEMENT_OPENING_TAG;
            indentLvl++;
    
            elementContent = " ";
			Element* tmpEl = new Element ( newElement, lineNum, elementContent, indentLvl );  // create a new Element object
            vecAllElements.push_back( tmpEl );  // add the new object to the vector
            findAttr(str, 0); // use function again to find attributes
    
            return ps;
        }
    }
    
    ps = ERROR;
    return ps;
}