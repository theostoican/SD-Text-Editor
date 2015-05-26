#ifndef BACKEND_H_
#define BACKEND_H_
#include <string>
#include "list.h"
#include "stack.h"
using namespace std;


class Backend {
	LinkedList<string> text;
	LinkedList<string> clipboard;
	LinkedList<string> copylist;
	Stack <LinkedList<string> > undo;
	Stack <LinkedList<string> > redo;
public:
	// Constructor
	Backend();

	// Destructor
	~Backend();

	// Cuts all the words from the start to the stop index
	void Cut(const int start, const int stop);

	// Saves all the words from the start to the stop index to the clipboard
	void Copy(const int start, const int stop);

	// Pastes all the words in the clipboard at the start index
	void Paste(const int start);

	// Undoes the last operation
	void Undo(void);

	// Redoes the last undone operation
	void Redo(void);

	// Adds the string held by "word" to the text at position "index"
	void Add(const int index, const char *word);

	// Rebuilds and returns the whole text held by the backend
	char *GetText();
};

#endif
