#include <iostream>
#include <string>
#include <cstring>
using namespace std;

template <typename T> struct Node{
	T value;
	Node<T> *next;
	Node<T> *prev;
};

template <typename T> class LinkedList{
	
	private:
		Node<T> *pfirst, *plast;
	public:
		friend class Backend;
			//respecta rule of three
			LinkedList()
			{
				pfirst = NULL;
				plast = NULL;
			}
			~LinkedList()
			{
				Node<T> *pdel = pfirst;
				while (pfirst != NULL)
				{
					pfirst = pfirst->next;
					delete pdel;
					pdel = pfirst;
				}
				plast = NULL;
			}

			//functie care returneaza un pointer care imi spune 
			//de unde ar trebui sa incep sa dau copy/cut
			Node<string>* searchstart (int start)
			{
				Node<string> *p = pfirst;
				if (p == NULL) 
				{
					return NULL;
				}
				int leng = 0;
				//cazul cand adaugam inaintea primului element
				if (start == 0) return p;
				while (leng < start && p != NULL)
				{
					leng += p->value.length();
					p = p->next;
				}
				return p;
			}

			//functie care returneaza un pointer care imi spune
			//pana unde trebuie sa dau copy/cut
			Node<string>* searchstop (int stop)
			{
				Node<string> *p = pfirst, *q;
				if (p == NULL) 
				{
					return NULL;
				}
				int leng = 0;
				if (stop == 0) return p;
				while (leng < stop && p != NULL)
				{
					q = p;
					leng += p->value.length();
					p = p->next;
				}
				if (leng > stop ) return q;
				else return p;
			}
			void deletecut (Node<T> *p1, Node<T> *p2)
			{
				if(p1 == NULL) return;
				Node<T> *start = p1->prev , *q;
				q = p1;
				while (p1 != p2 )
				{
					q = p1;
					p1 = p1->next;
					delete q;
				}
				//partea de modificare pfirst si plast
				if (start != NULL)
				{
					start->next = p2;
					//cazul in care am sters de la un index pana la sfarsit
					if (p2 == NULL) plast = start;
					else
					{
					  	//cazul in care am sters din mijloc
						p2->prev = start;
					}
				}
				else
				{
					//cazul in care am sters de la inceput pana la un index
					if (p2 != NULL)
					{
						pfirst = p2;
						p2->prev = start;
					}
					else 
					{
					  	//cazul in care am sters totul
						plast  = NULL;
						pfirst = NULL;
					}
				}
			}
			void remove()
			{
				Node<T> *q;
				while (pfirst != NULL)
				{
					q = pfirst;
					pfirst = pfirst->next;
					delete q;
				}
				plast = NULL;
			}
			void removeEl (Node <T> *p)
			{
				Node<T> *start = p->prev;
				//daca elementul este in mijloc
				if (start != NULL && p->next != NULL)
				{
					start->next = p->next;
					p->next->prev = start;
					delete p;
				}
				//daca este un singur element in lista
				else if (start == NULL && p->next == NULL)
				{
					delete p;
					pfirst = NULL;
					plast = NULL;
				}
				//daca este primul element
				else if (start == NULL)
				{
					pfirst = p->next;
					p->next->prev = NULL;
					delete p;
				}
				//daca este ultimul element
				else if (p->next == NULL)
				{
					plast = start;
					start->next = NULL;
					delete p;
				}
			}
			void add (Node<T> *where, const char *word)
			{
				if (where != pfirst)
				{
				  	Node<T> *p = new Node<T>;
					//ADAUG IN SPATELE ELEMENTULUI
					p->prev = where->prev;
					p->next = where;
					where->prev->next = p;
					where->prev = p;
					p->value = word;
				}
				else if (where == pfirst)
				{
					addFirst(word);
				}
			}
			//copy constructor
			LinkedList<T>(const LinkedList<T>& a)
			{
				pfirst = NULL;
				plast = NULL;
				Node<T> *p = a.pfirst;
				T aux;
				if (p == NULL)
				{
					plast = NULL;
					pfirst = NULL;
					return ;
				}
				while (p != NULL)
				{
					aux = p->value;
					addLast(aux);
					p = p->next;
				}
			}
			//assignment operator
			void operator=(LinkedList<T>& a)
			{
				Node<T> *p = a.pfirst;
				T aux;

				while (!isEmpty())
				{
					removeLast();
				}
				if (p == NULL)
				{
					plast = NULL;
					pfirst = NULL;
				}
				while (p != NULL)
				{
					aux = p->value;
					addLast(aux);
					p = p->next;
				}
			}
			void addLast(T value)
			{
				Node<T> *newnode=new Node<T>;
				newnode->value = value;
				if (pfirst == NULL && plast == NULL)
				{
					pfirst = newnode;
					plast = newnode;
					newnode->next = NULL;
					newnode->prev = NULL;
				}	
				else
				{

					newnode->next = NULL;
					newnode->prev = plast;
					plast->next = newnode;
					plast=newnode;
				}
			}
			void addFirst (T value)
			{
			  
				Node<T> *newnode = new Node<T>;
				newnode->value = value;
				if (pfirst == NULL && plast == NULL)
				{
					pfirst = newnode;
					plast = newnode;
					plast->next = NULL;
					plast->prev = NULL;
				}
				else
				{
					newnode->next = pfirst;
					newnode->prev = NULL;
					pfirst->prev = newnode;
					pfirst = newnode;
				}
			}
			Node<T>* getFirst()
			{
				return pfirst;
			}
			T removeFirst()
			{
				if (pfirst == plast && pfirst != NULL)
				{
					T val = pfirst->value;
					delete pfirst;
					pfirst = NULL;
					plast = NULL;
					return val;
				}
				else if (pfirst == plast && pfirst == NULL)
				{
					std::cout<<"The list is already empty";
					return 0;
				}
				else
				{
					Node<T> *newnode = pfirst->next;
					T val = pfirst->value;
					delete pfirst;
					pfirst = newnode;
					pfirst->prev = NULL;
					return val;
				}
			}
			T removeLast()
			{
				if (pfirst == plast && pfirst != NULL)
				{
					T val = pfirst->value;
					delete pfirst;
					pfirst = NULL;
					plast = NULL;
					return val;
				}
				else if (pfirst == plast && pfirst == NULL)
				{
					T toreturn;
					std::cout<<"The list is already empty";
					return toreturn;
				}
				Node<T> *newnode = plast->prev;
				T val = plast->value;
				delete plast;
				plast = newnode;
				plast->next = NULL;
				return val;
			}
			bool isEmpty()
			{
				if (pfirst == NULL && plast == NULL)
				{
					return true;
				}
				else return false;
			}
			char* printlist()
			{
				Node<T> *newnode = pfirst;
				//Caz limita
				if (newnode == NULL)
				{
					return NULL;
				}

				char* wholetext, *copy; 
				int leng;
				char *aux = new char[newnode->value.size() + 1];

				//nu merge varianta cu strdup, asa ca aloc manual cu new
				std::copy(newnode->value.begin(), newnode->value.end(), aux);
				aux[newnode->value.size()] = '\0';
				wholetext = new char[strlen(aux) + 1];
				strcpy(wholetext, aux);
				newnode = newnode->next;
				while (newnode != NULL)
				{
					delete[] aux;
					aux = new char[newnode->value.size() + 1];
					std::copy(newnode->value.begin(), newnode->value.end(), aux);
					aux[newnode->value.size()] = '\0';
					leng = newnode->value.length();
					copy = new char[strlen(wholetext) + leng + 1];
					strcpy (copy, wholetext);
					delete[] wholetext;
					strcat(copy, aux);
					wholetext = copy;
					newnode = newnode->next;
				}
				delete[] aux;
				return wholetext;
			}
	};

