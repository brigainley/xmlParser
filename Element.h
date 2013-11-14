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
    #include <vector>
    #include "attribute.h"
  
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

	/** Indentation level of this element */
	int indentationLvl;
   
    /** Vector of other elements */
    vector<Element *> vecChildren;
    
    /** Vector of attributes for this element */
    vector<Attribute *> vecAttributes;

    public:
    /** Default constructor, which initializes data members to placeholder values */
    Element();   
    
    /** Three parameter constructor 
     *  @param strElementName The actual element tag
     *  @param nLineNo The line on which the element was found
     *  @param strElementContent The content of the element
     */
	Element( string strElementName, int nLineNo, string strElementContent, int indentationLevel );     

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
        
    /** Sets the next attribute in the vector
     *  @param attrNewAttribute The newest attribute
     */
        void setNewAttribute( Attribute* attrNewAttribute );

	/** Sets the indentation level of the current element 
	 *  @param indentLevel The current indentation level
	 */
		void setIndentationLevel( int indentationLevel );
  
    /** Return the line number at which the current element was found */
		int getNLineNo() const;       
    
	/** Returns the indentation level of the element */
		int getIndentationLevel() const;

    /** Return the name of the element found */
        string getStrElementName() const;      
    
    /** Return the content of the element */
		string getStrElementContent() const; 

	/** Returns the size of the attribute vector */
		int getVecAttributeSize() const;
		
	/** Returns an attribute name specified by passed vector index
	 *  @param i The vector index to be accessed
	 */
		string getAttributeName( int i ) const;

	/** Returns an attribute content specified by passed vector index
	 *  @param i The vector index to be accessed
	 */
		string getAttributeContent( int i ) const;
				 
    };
    
    #endif  