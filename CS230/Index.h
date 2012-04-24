/* Author: Thomas Scroggins
 * File: Index.h
 * Description: Header file containing declaration of all 3 classes for CS230 Assignment 9
 */


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///********************************************************************************************************************************///
///*													Class Declarations														  *///
///********************************************************************************************************************************///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************************************************************/
/*															Entry - Declarations												*/
/********************************************************************************************************************************/
class Entry
{
	public:
				Entry(string chapter, int paragraph, int line);							//run of the mill constructor
		void	print(ostream &);														//Prints the entry in format <chapter>:P<paragraph>L<line>
		
		
	private:
		string	chapter;
		int 	paragraph;
		int 	line;
};

/********************************************************************************************************************************/
/*															Word - Declarations												*/
/********************************************************************************************************************************/
class Word
{
	public:
				Word(string name, string chapter, int paragraph, int line);				//Constructor makes one entry (otherwise we wouldn't need the word. Also, we don't use name, but I forgot to tak it out of the design so I'm stickin with it
		void	addEntry(string chapter, int paragraph, int line);						//Constructs an entry into the list
		void	print(ostream &);														//Prints all the entries in the correct format (actually passes responsiblility down)
	
	
	private:
		list<Entry> entries;

};

/********************************************************************************************************************************/
/*															Index - Declarations												*/
/********************************************************************************************************************************/
class Index 
{
	public:
		void	addEntry(string word, string chapter, int paragraph, int line);			//This will make a new word (if there isn't one already), and then calls the add entry operator for it
		void	print(ostream &);														//Prints the entire index in the correct format (actually passes responsibilty downwards)
	
	private:
		map<string, Word> words;

};
