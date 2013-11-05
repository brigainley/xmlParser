/*
 * File:   element.h
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 * With code from Jesse M. Heines, heines@cs.uml.edu, from a given solution
 *
 * Created on September 18, 2013
 */

    #ifndef ELEMENT_H
    #define ELEMENT_H
  
    #include <string>
    #include <iostream>
  
    using namespace std;
 
    /**
     * This class represents an element in the XML file 
     */
    class Element {
  
    private:
    /** Name of element extracted from an element opening tag */
    string strTagName;  
    
    /** Content of element */
    string strTagContent;
    
    /** Line number at which the element opening tag was found */
	int nLineNum;      

    public:
    /** Default constructor, which initializes data members to placeholder values */
    Element();   
    
    /** Three parameter constructor 
     *  @param strElementName The actual element tag
     *  @param nLineNo The line on which the element was found
     *  @param strElementContent The content of the element
     */
    Element( string strElementName, int nLineNo, string strElementContent );     

    /** Sets the line number of the current element
     *  @param lineNo The line number on which the element was found
     */
	void setNLineNo( int lineNo ); 
    
    /** Sets the name of the current element
     *  @param strElementName The actual element tag 
     */
	void setStrElementName( string strElemenetName );
    
    /** Sets the content of the element
     *  @param strElementContent The content of the element
     */
	void setStrElementContent( string strElementContent ); 
  
    /** Return the line number at which the current element was found */
	int getNLineNo() const;       
    
    /** Return the name of the element found */
    string getStrElementName() const;      
    
    /** Return the content of the element */
	string getStrElementContent() const; 
				 
    };
    
    #endif  