#include <iostream>
#include <cstdio>
#include "backend.h"

Backend::Backend()
{
}

Backend::~Backend()
{
}

void Backend::Cut(const int start, const int stop)
{
	undo.push(text);
	redo.push(text);
	Node<string> *p1, *p2, *copyp1;
	p1 = text.searchstart (start);
	p2 = text.searchstop (stop);
	copyp1 = p1;
	//golesc clipboardul, pentru a copia altceva
	while (!clipboard.isEmpty())
	    clipboard.removeLast();
	if (p1 == NULL)
	{
		return;
	}
	if (start < stop && (int)p1->value.length() <= (stop - start))
	{
		while (p1 != p2)
		{	
			clipboard.addLast(p1->value);
			p1 = p1->next;
		}
		text.deletecut(copyp1, p2);
	}
}
void Backend::Copy(const int start, const int stop)
{
	Node<string> *p1, *p2;
	p1 = text.searchstart (start);
	std::cout<<stop;
	p2 = text.searchstop (stop);
	while (!clipboard.isEmpty())
	    clipboard.removeLast();
	if (p1 == NULL)
	{
		return;
	}
	
	if (start < stop && (int)(p1->value.length()) <= stop - start)
	{
		while (p1 != p2 )
		{
			clipboard.addLast(p1->value);
			p1 = p1->next;
		}
	}
}

void Backend::Paste(const int start)
{
	undo.push(text);
	Node<string> *p = text.searchstart (start), *q;
	string aux;
	const char *s;
	q = clipboard.getFirst();
	Node <string> *r = q, *m = text.pfirst;
	while(r != NULL)
	{
		r = r->next;
	}
	while (m!= NULL)
	{
		m = m->next;
	}
	//inceput si sir nevid
	if (start == 0 && p != NULL)
	{
		while (q != NULL)
		{	
			aux = q->value;
			s = aux.c_str();
			text.add(p, s);
			q = q->next;
		}
	}
	//final sau sir vid
	else if (p == NULL)
	{
		while (q != NULL)
		{
			aux = q->value;
			s = aux.c_str();
			text.addLast(aux);
			q = q->next;
		}
	}
	//cazul in care se insereaza in mijloc
	else
	{
		while (q != NULL)
		{
			aux = q->value;
			s = aux.c_str();
			text.add (p, s);
			q = q->next;
		}
	}
}

void Backend::Undo(void)
{
	if (undo.isEmpty() == 0)
	{
		redo.push(text);
		LinkedList<string> aux = undo.pop();
		text = aux;
	}
}

void Backend::Redo(void)
{
	//cand voi da redo, voi adauga in stiva de undo, pentru a sti unde sa ma intorc
	undo.push(text);
	if (redo.isEmpty() == 0)
	{
		LinkedList<string> aux = redo.pop();
		text = aux;
	}
}

void Backend::Add(const int index, const char *word)
{
	undo.push(text);
	Node<string> *p;
	//creez un nou cuvant pentru a adauga si spatiu
	char aux[strlen(word)+1];
	strcpy(aux, word);
	strcat(aux, " ");
	p = text.searchstart (index);
	if (p != NULL)
	{
		text.add (p, aux);
	}
	else 
	{
		text.addLast(aux);
	}
}

char* Backend::GetText()
{
	char* toprint = text.printlist();
	if (toprint != NULL)
		return toprint;
	else 
	{
		//intorc sirul vid
	    char *textaux = new char[1];
	    strcpy(textaux,"");
	    return textaux;
	}
}

