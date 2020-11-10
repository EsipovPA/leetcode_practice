#include <iostream>
#include <vector>


using namespace std;


#define LIST_GET		0
#define LIST_ADD_HEAD	1
#define LIST_ADD_TAIL	2
#define LIST_ADD_INDEX	3
#define LIST_DEL_INDEX	4

#define LIST_ADD_TO_NEXT true
#define LIST_ADD_TO_PREV false

// Copy to leetcode
class MyLinkedList {
private:
	struct Node{
		int val;
		Node* prev;
		Node* next;

		Node(): val(0), next(nullptr), prev(nullptr) {}
		Node(int v): val(v), next(nullptr), prev(nullptr) {}
		Node(int v, Node* prv, Node* nxt): val(v), next(nxt), prev(prv) {}
	};

	Node* head;
	Node* back;
	size_t list_size;


	Node* getNodeAtIndex(int index){
		if(index < 0 || index >= list_size){
			return nullptr;
		}

		Node* node{ head };
		int pos{ 0 };

		while(pos < index){
			pos++;
			node = node->next;
		}

		return node;
	}

public:
	// Delete these
	bool runSelfCheck(){
		Node* node{ head };
		Node* prev{ nullptr };
		int count{ 0 };

		while(node != nullptr){
			if(node->prev != prev){
				cout << "\nincorrect previous pointer\n";
				return false;
			}

			prev = node;
			node = node->next;

			count++;
		}

		if(count != list_size){
			cout << "\nincorrect list size: count = " << to_string(count) << " size = " << list_size << endl;
			return false;
		}

		return true;
	}

	vector<int> ToVector(){
		vector<int> res{};
		Node* node{ head };

		while(node != nullptr){
			res.push_back(node->val);
			node = node->next;
		}

		return res;
	}

	void PrintList(){
		Node* node{ head };

		cout << "list test output: ";
		while(node != nullptr){
			cout << to_string(node->val) << " ";
			node = node->next;
		}
		cout << endl;
	}

	void RevecePrint(){
		Node* node{ back };

		cout << "backwards list: ";
		while(node != nullptr){
			cout << node->val << " ";
			node = node->prev;
		}
		cout << endl;
	}

    /** Initialize your data structure here. */
    MyLinkedList(): head(nullptr), back(nullptr), list_size(0) {}
    
    /** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
    int get(int index) {
    	Node* node{ getNodeAtIndex(index) };
    	return (node != nullptr ? node->val : -1);

    }
    
    /** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
    void addAtHead(int val) {
        if(head == nullptr){
        	head = new Node(val);
        	back = head;
        }else{
        	head = new Node(val, nullptr, head);
        	head->next->prev = head;
        }
    }
    
    /** Append a node of value val to the last element of the linked list. */
    void addAtTail(int val) {
        if(back == nullptr){
        	back = new Node(val);
        	head = back;
        }else{
        	back = new Node(val, back, nullptr);
        	back->prev->next = back;
        }
    }
    
    /** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
    void addAtIndex(int index, int val) {
        if(index == 0){
        	addAtHead(val);
        }else if(index == list_size){
        	addAtTail(val);
        }else{
        	Node* node{ getNodeAtIndex(index) };

        	if(node == nullptr){
        		return;
        	}

        	Node* newNode = new Node(val, node->prev, node);
        	
        	if(newNode->prev != nullptr){
        		newNode->prev->next = newNode;
        	}

        	if(newNode->next != nullptr){
        		newNode->next->prev = newNode;
        	}
        }

        list_size++;
    }
    
    /** Delete the index-th node in the linked list, if the index is valid. */
    void deleteAtIndex(int index) {
        Node* node{ getNodeAtIndex(index) };

        if(node == nullptr){
        	return;
        }

        if(node == head){
        	head = head->next;
        }else if(node == back){
        	back = back->prev;
        }

		if(node->prev != nullptr){
			node->prev->next = node->next;
		}

		if(node->next != nullptr){
			node->next->prev = node->prev;
		}

		delete node;

        list_size--;
    }
};
// End of copy to leetcode
/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */


bool isCorrectList(MyLinkedList& list, const vector<int>& res){
	if(!list.runSelfCheck()){
		return false;
	}

	vector<int> list_vect = list.ToVector();
	if(list_vect.size() != res.size()){
		return false;
	}

	for(int i = 0; i < res.size(); i++){
		if(list_vect[i] != res[i]){
			return false;
		}
	}

	return true;
}


void RunTests(const vector<vector<vector<int>>>& input, const vector<vector<int>>& res){
	for(int i = 0; i < input.size(); i++){
		MyLinkedList list;


		for(int j = 0; j < input[i].size(); j++){
			cout << "pos = " << to_string(j) << " req = " << to_string(input[i][j][0]) << " ";
			list.PrintList();
			list.RevecePrint();


			switch(input[i][j][0]){
				case LIST_GET: {
					int get = list.get(input[i][j][1]);
					cout << "list get result[" << to_string(input[i][j][1]) << " ] = " << to_string(get) << endl;
					break;
				}

				case LIST_ADD_HEAD: {
					list.addAtHead(input[i][j][1]);
					break;
				}

				case LIST_ADD_TAIL: {
					list.addAtTail(input[i][j][1]);
					break;
				}

				case LIST_ADD_INDEX: {
					list.addAtIndex(input[i][j][1], input[i][j][2]);
					break;
				}

				case LIST_DEL_INDEX: {
					list.deleteAtIndex(input[i][j][1]);
					break;
				}
			}
		}

		cout << "\v!!!!test " << to_string(i) << (isCorrectList(list, res[i]) ? " success\n\n" : " failure\n\n");
	}
}


int main(){
	vector<vector<vector<int>>> input{
		{
			{LIST_ADD_HEAD, 1},
			{LIST_ADD_TAIL, 3},
			{LIST_ADD_INDEX, 1, 2},
			{LIST_GET, 1},
			{LIST_DEL_INDEX, 1},
			{LIST_GET, 1}
		},

		{
			{LIST_ADD_HEAD, 7},
			{LIST_ADD_HEAD, 2},
			{LIST_ADD_HEAD, 1},
			{LIST_ADD_INDEX, 3, 0},
			{LIST_DEL_INDEX, 2},
			{LIST_ADD_HEAD, 6},
			{LIST_ADD_TAIL, 4},
			{LIST_GET, 4},
			{LIST_ADD_HEAD, 4},
			{LIST_ADD_INDEX, 5, 0},
			{LIST_ADD_HEAD, 6}
		},

		{
			{LIST_ADD_HEAD, 1},
			{LIST_ADD_TAIL, 3},
			{LIST_ADD_INDEX, 1, 2},
			{LIST_GET, 1},
			{LIST_DEL_INDEX, 0},
			{LIST_GET, 0}
		}
	};

	vector<vector<int>> res{
		{1, 3},
		{4, 6, 1, 2, 0, 0, 4},
		{2, 3}
	};

	RunTests(input, res);

	return 0;
}