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
    int nLineNum ;      // line number at which the element opening tag was found 

  public:
    Element();          // default constructor, which initializes data members to placeholder values

    Element( string strElementName, int nLineNo ) ;       // two-parameter constructor
														  // @param strElementName name of element extracted from an element opening tag
														  // @param nLineNo line number at which the element opening tag was found

    string toString() ;			   // represent the object's information as a string in a reasonable format
								   // @return a string representing the object
  
	int getNLineNo() const ;       // get the line number at which the current element was found
								   // @return line number at which the current element was found
 
    string getStrElementName() const ;      // get the name of the element found
											// @return name of the element found  
  };
  
  #endif  