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
	  nLineNum = 999;
  }

  // Constructor with arguments
  Element::Element( string strElementName, int nLineNo ) {
	  strTagName = strElementName;
	  nLineNum = nLineNo;
  }

  int Element::getNLineNo() const {
		return nLineNum;
	}

  string Element::getStrElementName() const {
		return strTagName;
	}

