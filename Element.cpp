/*
 * File:   element.h
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 *
 * Created on September 18, 2013
 */

    #include "attribute.h"
    #include "element.h"
    #include <string>
    #include <iostream>
    #include <vector>
    
    using namespace std;
    
    /** Default constructor, which initializes data members to placeholder values */
    Element::Element() {
        strTagName = "Placeholder";
        nLineNum = 00000;
		indentationLvl = 00000;
        strTagContent = "This is a blank element.";
        vecChildren.clear();
        vecAttributes.clear();
    }

    /** Three parameter constructor 
     *  @param strElementName The actual element tag
     *  @param nLineNo The line on which the element was found
     *  @param strElementContent The content of the element
     */
    Element::Element( string strElementName, int nLineNo, string strElementContent, int indentationLevel ) {
        setStrElementName( strElementName );
        setNLineNo( nLineNo );
        setStrElementContent( strElementContent );
		setIndentationLevel( indentationLevel );
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
    
    /** Sets the next attribute in the vector
     *  @param attrNewAttribute The newest attribute
     */
    void Element::setNewAttribute( Attribute* attrNewAttribute ) {
        vecAttributes.push_back(attrNewAttribute);     
     }

	/** Sets the indentation level of the current element 
	 *  @param indentLevel The current indentation level
	 */
	void Element::setIndentationLevel( int indentationLevel ) {
		indentationLvl = indentationLevel;	
	}
    
    /** Return the line number at which the current element was found */
    int Element::getNLineNo() const {
        return nLineNum;
    }

	/** Returns the indentation level of the element */
	int Element::getIndentationLevel() const {
		return indentationLvl;
	}

    /** Return the name of the element found */
    string Element::getStrElementName() const {
        return strTagName;
	}

    /** Return the content of the element */
    string Element::getStrElementContent() const {
		return strTagContent;
	}

	/** Returns the size of the attribute vector */
	int Element::getVecAttributeSize() const {
		return vecAttributes.size();
	}

	/** Returns an attribute name specified by passed vector index
	 *  @param i The vector index to be accessed
	 */
	string Element::getAttributeName( int i ) const {
		return vecAttributes.at(i) -> getStrAttributeName();
	}

	/** Returns an attribute content specified by passed vector index
	 *  @param i The vector index to be accessed
	 */
	string Element::getAttributeContent( int i ) const {
		return vecAttributes.at(i) -> getStrAttributeContent();
	}