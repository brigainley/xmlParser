/*
 * File:   Element.h
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 * With code from Jesse M. Heines, heines@cs.uml.edu, from a given solution
 *
 * Created on September 18, 2013
 */

  #ifndef ELEMENT_H
  #define ELEMENT_H
  
  #include <string>
  #include <iostream>
  
  using namespace std ;
 
  /**
   * This class represents an element in the XML file.  Version 1, for 91.204
   * Computing IV Assignment No. 1, is rudimentary and only contains the element
   * name and the line number at which that element was found.
   */

  class Element {
  
  private:
    string strTagName ; //name of element extracted from an element opening tag  
    string strTagContent; // content of element
	int nLineNum ;      // line number at which the element opening tag was found 


  public:
    Element();          // default constructor, which initializes data members to placeholder values
    Element( string strElementName, int nLineNo, string strElementContent ) ;       // three parameter constructor

	void setNLineNo( int lineNo ); // sets the line number of the current element
	void setStrElementName( string strElemenetName ); // sets the name of the current element
	void setStrElementContent( string strElementContent ); // sets the content of the element
  
	int getNLineNo() const ;       // return the line number at which the current element was found	 
    string getStrElementName() const ;      // return the name of the element found
	string getStrElementContent() const; // return the content of the element
				 
  };
  
  #endif  