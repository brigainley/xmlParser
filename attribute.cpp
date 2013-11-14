/*
 * File:   attribute.h
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 *
 * Created on November 8th, 2013
 */

    #include "attribute.h"
    #include <string>
    #include <iostream>
    
    using namespace std;
    
    /** Default constructor, which initializes data members to placeholder values */
    Attribute::Attribute() {
        strAttrName = "Placeholder";
        nLineNum = 00000;
        strAttrContent = "This is a blank attribute.";
    }

    /** Three parameter constructor 
     *  @param strAttrName The actual attribute tag
     *  @param nLineNo The line on which the attribute was found
     *  @param strAttrContent The content of the attribute
     */
    Attribute::Attribute( string strAttributeName, int nLineNo, string strAttributeContent ) {
        setStrAttributeName( strAttributeName );
        setNLineNo( nLineNo );
        setStrAttributeContent( strAttributeContent );
    }
  
    /** Sets the line number of the current element
     *  @param lineNo The line number on which the element was found
     */
    void Attribute::setNLineNo( int lineNo ) {
        nLineNum = lineNo;
    }

    /** Sets the name of the current attribute
     *  @param strAttrName The actual attribute tag 
     */
    void Attribute::setStrAttributeName( string strAttributeName ) {
        strAttrName = strAttributeName;
    }

    /** Sets the content of the attribute
     *  @param strAttributeContent The content of the attribute
     */
    void Attribute::setStrAttributeContent( string strAttributeContent ) {
        strAttrContent = strAttributeContent;
    }
    
    /** Return the line number at which the current attribute was found */
    int Attribute::getNLineNo() const {
        return nLineNum;
    }

    /** Return the name of the attribute found */
    string Attribute::getStrAttributeName() const {
        return strAttrName;
	}

    /** Return the content of the attribute */
    string Attribute::getStrAttributeContent() const {
		return strAttrContent;
	}
