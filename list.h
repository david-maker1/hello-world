#include <iostream>

class Node{
public:
	Node* next;
	int val;
};

class List{
public:	
	Node* head;
	List();
	~List();
	void push_front(int val);
	void pop_front();
	void push_back(int val);
	void pop_back();
	void print();
	void clear();
	void del(int index);
	void insert(int index, int val);
	List& operator=(List& list);
	int operator[](int index);
	int len();
};

List::List(){
	this->head = nullptr;
}

List::~List(){
	Node* current = this->head;
	while(this->head){
		delete head;
		head = current->next;
		current = current->next;
	}
}

void List::push_front(int val){
	Node* nd = new Node;
	nd->val = val;
	nd->next = this->head;
	this->head = nd;
}

void List::pop_front(){
	Node* current = this->head;
	if(current){
		this->head = this->head->next;
	}
}

void List::push_back(int val){
	Node* nd = new Node;
	nd->val = val;
	nd->next = nullptr;
	if (this->head){
		Node* current = this->head;
		while(current->next){
			current = current->next;
		}
		current->next = nd;
	}
	else{
		head = nd;
	}
}
	
void List::pop_back(){
	Node* current = this->head;
	if (current){
		if (current->next){
			while(current->next->next){
				current = current->next;
			}
		Node* nd = current->next;
		current->next = nullptr;
		}
		else{
			this->head = nullptr;
		}
	}
}
			
void List::print(){
	Node* nd = this->head;
        if (!nd)
		return;

	while(nd->next){
                std::cout << nd->val << " ";
                nd = nd->next;
        }

	std::cout << nd->val << std::endl;
}

void List::clear(){
	while(this->head){
		this->pop_front();
	}
}

int List::len(){
	Node* nd = this->head;
	int i = 0;
        if (nd){
                while(nd->next){
                        i++;
                        nd = nd->next;
                }
                i++;
        }
	return i;
}

void List::del(int index){
	Node* nd = this->head;
	int i = 1;
	if (index == 1){
		this->pop_front();
	}
	else{
		if((index >= 1) && (index <= this->len())){
        		while((i != index - 1)&&(nd)){
               			i++;
				nd = nd->next;
        		}
			Node* current = nd->next;
			nd->next = current->next;
		}
	}
}

void List::insert(int index, int val){
	Node* new_nd = new Node;
	new_nd->val = val;
	new_nd->next = nullptr;
	if (index == 1){
                this->push_front(val);
        }
        else{
                if((index >= 1) && (index <= this->len() + 1)){
			Node* nd = this->head;
			int i = 1;
                        while((i != index - 1) && nd){
                                i++;
                                nd = nd->next;
                        }
			new_nd->next = nd->next;
			nd->next = new_nd;
                }
        }
}

List& List::operator=(List& list){
	Node* new_nd = new Node; 
	Node* nd = list.head;
	new_nd = nd;
	this->head = new_nd;
	if (!nd)
		return *this;
       	while(nd->next){
		nd = nd->next;
		new_nd->next = new Node;
		new_nd->next = nd;
		new_nd = new_nd->next;	
	}
	return *this;
}

int List::operator[](int index){
	if((index >= 1) && (index <= this->len())){
		Node* nd = this->head;
		int i = 0;
		while((i != index - 1)&&(nd)){
                	i++;
                        nd = nd->next;
                }
		return nd->val;
        }
        std::cout << "Index out of range" << std::endl;
	return 0;
}
