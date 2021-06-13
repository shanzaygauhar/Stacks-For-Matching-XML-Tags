#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template<class T>
class Node {
public:
	Node()
	{
		next = 0;
		data = 0;
	}
	Node(T d = 0, Node<T>* n = 0)
	{
		data = d;
		next = n;
	}
	~Node()
	{

	}
	T data;
	Node<T> * next;
};

template<class T>
class Stack {
public:
	Stack()
	{
		top = 0;
	}
	~Stack()
	{
		T data;
		if (!IsEmpty())
		{
			while (!IsEmpty())
			{
				pop(data);   //pop function deletes
			}
		}
	}
	bool IsEmpty()
	{
		if (top == 0)  //top is null or 0 when the stack is empty
			return true;
		return false;
	}
	bool push(T & val)
	{
		if (IsEmpty())
		{
			Node<T>* obj = new Node<T>(val, 0);  //top is initialised to zero
			top = obj;
			return true;
		}
		else
		{
			Node<T>* obj = new Node<T>(val, top);
			top = obj;
			return true;
		}
		return false;

	}
	bool pop(T & val)
	{
		if (!IsEmpty())
		{
			Node<T>* obj = top;

			val = top->data;   //puts the popped value in the val
			top = top->next;
			delete obj;
			return true;
		}
		return false;
	}
	T gettop()
	{
		if (!IsEmpty())
			return top->data;
		return -1;       //the stack is empty
	}
	void print()
	{
		Node<T>* ptr = top;
		while (ptr != nullptr)
		{
			cout << ptr->data << "\t";
			ptr = ptr->next;
		}
	}
private:
	Node<T> * top;
};
class Xmldata{
private:
	int lineNumber;
	char operators;
	string tags;

public:
	//Constructor
	Xmldata()
	{
		lineNumber = 0;
		operators = '\0';
		tags = "\0";
	}
	//Overloaded Constructor
	Xmldata(int num, char op = '\0', string tag = "\0")
	{
		lineNumber = num;
		operators = op;
		tags = tag;
	}
	//Copy Constructor
	Xmldata(Xmldata& obj)
	{
		lineNumber = obj.lineNumber;
		operators = obj.operators;
		tags = obj.tags;
	}
	//Operator=
	Xmldata& operator=(Xmldata& obj)
	{
		lineNumber = obj.lineNumber;
		operators = obj.operators;
		tags = obj.tags;
		return *this;
	}

	int getLineNumber()
	{
		return lineNumber;
	}
	char getoperator()
	{
		return operators;
	}
	string getTag()
	{
		return tags;
	}
	void setoperator(char op)
	{
		operators = op;
	}
	
};

bool CheckTags(string ptr, int Linenum, Stack<Xmldata>& Tag)
{
	int index = 0;          // for string ptr
	int i;                 //for temp
	Xmldata check;
	char temp[100];

		while (ptr[index] != '\0' && ptr[index] != '\n')
		{
			i = 0;
			if (ptr[index] == '<' && ptr[index+1] != '/' && ptr[index+1] != '!') //ignores closing tags and comments
			{
				index++;

				//copies contents of tags
				while (ptr[index] != '>' && ptr[index] != 32)
				{
					temp[i] = ptr[index];
					i++;
					index++;
				}
				temp[i] = '\0';
				Xmldata object(Linenum, '\0', temp);  
				Tag.push(object);           //push opening tags in the stack
			} 
			
			else if (ptr[index] == '<' && ptr[index + 1] == '/')
			{
				i = 0;

				index++;    //skips <
				index++;   //skips /

				//copies contents of tags
				while (ptr[index] != '>' && ptr[index] != 32)  
				{
					temp[i] = ptr[index];
					i++;
					index++;
				}
				temp[i] = '\0';

				Xmldata object = Tag.gettop();
				if (object.getTag() == temp)   //if opening tag is equal to closing tag then no error else error
				{
					Tag.pop(check);
					return true;
				}
				else if (object.getTag() != temp)
				{
					cout << "The tag </" << object.getTag()<< "> is missing from line number " << object.getLineNumber() << endl;
					return false;
				}
				
			}
			index++;
			
		}
		return true;
}

void Compile(ifstream& in, Stack<Xmldata>& Tag)
{
	string ptr;
	Xmldata check;
	int lineNumber = 1;
	int index = 0;
	bool flag = false;
	bool isTag = false;

	while (!in.eof())
	{
		getline(in, ptr);

		flag = false;
		isTag = false;
		 index = 0;


		 while (ptr[index] != '\0' && ptr[index] != '\n')
		 {
			 //Comments are to be ignored all at once
			 if (ptr[index] == '<' && ptr[index + 1] == '!')
			 {
				 Xmldata object(lineNumber, ptr[index]);
				 Tag.push(object);
				 
				 index++;    //moves to !
				 index++;   // moves to - for the next condition

				 if (ptr[index] == '-' && ptr[index+1] == '-')
				 {
					 object.setoperator(ptr[index]);
					 Tag.push(object);

					 index++;    // moves to - identified in the previous condition
					 index++;   // moves ahead of previous - to look for the ending -

					 while (ptr[index] != '-'&& ptr[index] != '\0')
					 {
						 index++;
					 }

					 if (ptr[index] == '-' && ptr[index+1] == '-')
					 {
						 Tag.pop(check);
					 }
					 else
					 {
						 cout << "Error in Comment: The operator - is missing from line Number " << lineNumber << endl;
						 return;
					 }

					 index++;   // moves to - identified in the previous condition
					 index++;  //moves to > if present or any other character present

					 if (ptr[index] == '>')
					 {
						 Tag.pop(check);
					 }
					 else
					 {
						 cout << "The comment has an error and the operator  > " << " is missing from line number " << lineNumber << endl;
						 return;
					 }
				 }
				 else
				 {
					 cout << "Error in Comment: The operator - is missing from line Number " << lineNumber << endl;
					 return;
				 }
			 }
			 //Operators
			  else if (ptr[index] == '<')
			 {
				 Xmldata object(lineNumber, ptr[index]);
				 Tag.push(object);
				 isTag = true;
				 //special header case
				 if (lineNumber == 1 && ptr[index + 1] == '?') //header is <?
				 {
					 index++;
					 Xmldata object(lineNumber, ptr[index]);
					 Tag.push(object);
				 }
				 else if (lineNumber == 1 && ptr[index + 1] != '?')
				 {
					 cout << "Error in Header: The operator ? is missing from line number " << lineNumber << endl;
					 return;
				 }
			 }
			 else if (ptr[index] == '>')
			 {
				 if (lineNumber == 1 && ptr[index - 1] != '?')   //if its a header and index-1 is not ? give error
				 {
					 cout << "Error in Header: The operator ? is missing from line number " << lineNumber << endl;
					 return;
				 }
				 
				 Xmldata object = Tag.gettop();
				 if (object.getoperator() == '<')
					 Tag.pop(check);
				 else if (object.getoperator() != '<'){
					 cout << "The operator < " << "is missing from line number " << lineNumber << endl;
					 return;
				 }
				 isTag = false;
			 }
			  //Header Condition
			 else if (lineNumber == 1 && ptr[index] == '?')
			 {
				 Xmldata object = Tag.gettop();
				 if (ptr[index] == object.getoperator())
					 Tag.pop(check);
				 else{
					 cout << "Error in Header: The operator ? is missing from line number " << lineNumber << endl;
					 return;
				 }
			 }
			 //Attributes
			 else if (isTag==true && ptr[index] == '"')        //attributes to be checked in tags
			 {
				 index++;                                         //shifts one position ahead of previous "
				 while (ptr[index] != '"' && ptr[index] != '\0') //until next " is found
				 {
					 if (ptr[index] == 39)   //if  " or ' occurs
					 {
						 char a = '"';
						 cout << "The operator  " << a << " is missing from line number " << lineNumber << endl;
						 return;
					 }
					 index++;
				 }
				 if (ptr[index] != '"')
				 {
					 char a = '"';
					 cout << "The operator  " << a << " is missing from line number " << lineNumber << endl;
					 return;
				 }
			 }
			 else if (isTag == true && ptr[index] == 39) //attributes to be checked in tags
			 {
				 index++;                                       //shifts one position ahead of previous "

				 while (ptr[index] != 39 && ptr[index] != '\0')  //until next ' is found
				 {
					 
					 if (ptr[index] == '"') //if ' or " occurs
					 {
						 char a = '"';
						 cout << "The operator  " << a << " is missing from line number " << lineNumber << endl;
						 return;
					 }
					 index++;
				 }
				if(ptr[index] != 39)
				 {
					 char a = 39;
					 cout << "The operator  " << a << " is missing from line number " << lineNumber << endl;
					 return;
				 }
			 }

			 index++;
		 }
		 if (!Tag.IsEmpty())  //if tag is not empty after characters are pop and pushed this MIGHT indicate 
		 {                    //indicate an error in characters
			 Xmldata obj = Tag.gettop();
			 if (obj.getoperator() == '<')
			 {
				 cout << "The operator > is missing from line number " << obj.getLineNumber() << endl;
				 return;
			 }
			 else if (obj.getoperator() == '"')
			 {
				 cout << "The operator " << obj.getoperator() << " is missing from line number " << obj.getLineNumber() << endl;
				 return;
			 }
			 else if (obj.getoperator() == 39)
			 {
				 cout << "The operator " << obj.getoperator() << " is missing from line number " << obj.getLineNumber() << endl;
				 return;
			 }
			 else if (obj.getoperator() == '?')
			 {
				 cout << "The operator " << obj.getoperator() << " is missing from line number " << obj.getLineNumber() << endl;
				 return;
			 }
		 }
		 if (lineNumber != 1)
		 {
			 bool ch = true;
			 ch = CheckTags(ptr, lineNumber, Tag);
			 if (ch == false)
			 {
				 return;
			 }
		 }
		lineNumber++;
	}

	if (!Tag.IsEmpty())
	{
		Xmldata object = Tag.gettop();
		cout << "The tag </ " << object.getTag() << "> is missing from line number " << object.getLineNumber() << endl;
		return;
	}
}

void main()
{
	ifstream input;
	input.open("Error.txt");
	if (!input)
	{
		cout << "ERROR OPENNING FILE\n";
		return;
	}
	else{
		Stack<Xmldata> obj;
		Compile(input, obj);
	
	}
}