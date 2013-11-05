/*
 * File:   element.h
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 *
 * Created on September 18, 2013
 */

    #include "element.h"
    #include <string>
    #include <iostream>
    
    using namespace std;
    
    /** Default constructor, which initializes data members to placeholder values */
    Element::Element() {
        strTagName = "Placeholder";
        nLineNum = 00000;
        strTagContent = "This is a blank element.";
    }

    /** Three parameter constructor 
     *  @param strElementName The actual element tag
     *  @param nLineNo The line on which the element was found
     *  @param strElementContent The content of the element
     */
    Element::Element( string strElementName, int nLineNo, string strElementContent ) {
        setStrElementName( strElementName );
        setNLineNo( nLineNo );
        setStrElementContent( strElementContent );
    }
  
    /** Sets the line number of the current element
     *  @param lineNo The line number on which the element was found
     */
    void Element::setNLineNo( int lineNo ) {
        nLineNum = lineNo;
    }

    /** Sets the name of the current element
     *  @param strElementName The actual element tag 
     */
    void Element::setStrElementName( string strElementName ) {
        strTagName = strElementName;
    }

    /** Sets the content of the element
     *  @param strElementContent The content of the element
     */
    void Element::setStrElementContent( string strElementContent ) {
        strTagContent = strElementContent;
    }
    
    /** Return the line number at which the current element was found */
    int Element::getNLineNo() const {
        return nLineNum;
    }

    /** Return the name of the element found */
    string Element::getStrElementName() const {
        return strTagName;
	}

    /** Return the content of the element */
    string Element::getStrElementContent() const {
		return strTagContent;
	}
