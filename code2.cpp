/*	Student Name	:	Deepthi Valachery
	Student ID		:	[redact]
	Course Code		:	COMP 1603
	Assignment		:	2
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;

struct Node {
   int data;
   Node * next;
};

Node * createNode (int data){
	Node * newNode = (Node *) malloc (sizeof (Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void insertAtHead (Node ** top, int n){	
	Node * newNode = createNode (n);
	newNode->next = (*top); 
	(*top) = newNode;
}

int size (Node * top) {
   Node * curr;

   int numNodes = 0;
   curr = top;
   while (curr != NULL) {
      numNodes = numNodes + 1;
      curr = curr->next;
   }
   return numNodes;
}


void printList (Node * n){
   while (n) {
    	cout << n->data;
    	n = n->next;
   }
}

Node * reverseList (Node * top) {								//Reverse the digits entering the list
     Node *curr = top;
     Node *advCurr = NULL;

     while (curr != NULL) {
        advCurr = curr->next;
        if (top == curr) 
           top->next = NULL;      
        else { 
			curr->next = top;
            top = curr;
        }
        curr = advCurr;
     }
	 return top;
}

void deleteList (Node ** top){									//Delete list as a whole
	Node * curr = *top;
	Node * next;
	
	while (curr != NULL){
		next = curr->next;
		free(curr);
		curr = next;
	}
	*top = NULL;
}

bool isInteger (char str) {										//Check if the value is integer
	int i = 0;
	
		if (str < '0' || str > '9'){
			return false;
			i++;
		}
	return true;
}

Node * addTwoLists (Node * first, Node * second){				//Find the sum of the lists
	first = reverseList(first);
	second = reverseList(second);
	
	int carry = 0;
	Node *head = NULL, *prev = NULL;
	Node * sum = NULL;
	
	while (first != NULL || second != NULL || carry == 1){
		int newVal=carry;
		if (first)
			newVal += first->data;
		if  (second)
			newVal += second->data;
			
		carry = newVal/10;
		newVal = newVal % 10;
		
		Node * newNode = (Node * ) malloc (sizeof (Node));
		newNode->data = newVal;
		
		newNode->next = sum;
		sum = newNode;
		
		if (first)
			first = first->next;
		if (second)
			second = second->next; 
	}
	return sum;
}

int main() {
	ifstream inputFile;
	inputFile.open("integers.txt");
	
	Node * top1 = NULL;
	Node * top2 = NULL;
	
	char num1[50], num2[50];
	
	if (!inputFile.is_open()) {
	cout << "File could not be opened. Aborting..." << endl;
	exit(1)	;
	}
	
	inputFile >> num1;													//Read the data for integer 1
	
	while (strcmp(num1, "-1")){
		inputFile >> num2;												//Read the data for integer 2
			
			int length1= strlen(num1);
			int length2= strlen(num2);
			
			for (int i=0;i<=length1;i++) {
				if(isInteger(num1[i])) {
					insertAtHead(&top1, num1[i]-'0');					//Store the data for integer 1 in a linked list
					
				}
			}
			for (int i=0;i<=length2;i++) {
				if (isInteger(num2[i])){
					insertAtHead(&top2, num2[i]-'0');					//Store the data for integer 2 in a linked list
				}
			}
			
			cout << "\n";
			top1 = reverseList(top1);		//reverse list
			top2 = reverseList(top2);		//reverse list p2
			
			int size1= size(top1);
			int size2= size(top2);
			
			if (size1 < size2){				//Proper format 
				int space = size2 - size1;
				for (int j=0;j<space;j++)
				cout << " ";
			}
			
			printList(top1);
			cout << " +" << endl;
			
			if (size2 < size1){				//Proper format 
				int space2 = size1 - size2;
				for (int j=0;j<space2;j++)
				cout << " ";
			}
			
			printList(top2);
			cout << endl;
			
			Node * top3 = addTwoLists(top1, top2);						//Store the sum of the integer 1 and 2 in a linked list
			
			int size3= size(top3);
			
			for (int j=0;j<size3;j++){
				cout << "=";
			}
			
			cout << endl;
			
			printList(top3);
			cout << endl;
			
			for (int j=0;j<size3;j++){
				cout << "=";
			}
			
			cout << "\n\n";
			
			deleteList(&top1);
			deleteList(&top2);		//Delete list
		
		inputFile >> num1;
	}
	
return 0;

}
