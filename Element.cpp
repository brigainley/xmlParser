/*
 * File:   Element.h
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 *
 * Created on September 18, 2013
 */

  #include "Element.h"
  #include <string>
  #include <iostream>
  
  using namespace std;

  // Default Element Contructor
  Element::Element() {
	  strTagName = "Placeholder";
	  nLineNum = 00000;
	  strTagContent = "This is a blank element.";
  }

  // Constructor with arguments
  Element::Element( string strElementName, int nLineNo, string strElementContent ) {
	  setStrElementName( strElementName );
	  setNLineNo( nLineNo );
	  setStrElementContent( strElementContent );
  }

  void Element::setNLineNo( int lineNo ) {
	  nLineNum = lineNo;
  }

    void Element::setStrElementName( string strElementName ) {
	  strTagName = strElementName;
  }

	void Element::setStrElementContent( string strElementContent ) {
	  strTagContent = strElementContent;
	}

  int Element::getNLineNo() const {
		return nLineNum;
	}

  string Element::getStrElementName() const {
		return strTagName;
	}

  string Element::getStrElementContent() const {
		return strTagContent;
	}
