/*
 * File:   attribute.h
 * Author: Brianna Gainley, brianna_gainley@student.uml.edu
 * With code from Jesse M. Heines, heines@cs.uml.edu, from a given solution
 *
 * Created on November 8th, 2013
 */

    #ifndef ATTRIBUTE_H
    #define ATTRIBUTE_H
  
    #include <string>
    #include <iostream>
  
    using namespace std;
 
    /**
     * This class represents an attribute in the XML file 
     */
    class Attribute {
  
    private:
    /** Name of element extracted from an element opening tag */
    string strAttrName;  
    
    /** Content of element */
    string strAttrContent;
    
    /** Line number at which the element opening tag was found */
	int nLineNum;      

    public:
    /** Default constructor, which initializes data members to placeholder values */
    Attribute();   
    
    /** Three parameter constructor 
     *  @param strAttributeName The actual attribute tag
     *  @param nLineNo The line on which the attribute was found
     *  @param strAttributeContent The content of the attribute
     */
    Attribute( string strAttributeName, int nLineNo, string strAttributeContent );     

    /** Sets the line number of the current attribute
     *  @param lineNo The line number on which the attribute was found
     */
	void setNLineNo( int lineNo ); 
    
    /** Sets the name of the current attribute
     *  @param strAttributeName The actual attribute tag 
     */
	void setStrAttributeName( string strAttributeName );
    
    /** Sets the content of the attribute
     *  @param strAttributeContent The content of the attribute
     */
	void setStrAttributeContent( string strAttributeContent ); 
  
    /** Return the line number at which the current attribute was found */
	int getNLineNo() const;       
    
    /** Return the name of the attribute found */
    string getStrAttributeName() const;      
    
    /** Return the content of the attribute */
	string getStrAttributeContent() const; 
				 
    };
    
    #endif  