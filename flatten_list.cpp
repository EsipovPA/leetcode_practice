#include <iostream>
#include <vector>

using namespace std;


// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};


class Solution {
public:
    Node* flatten(Node* head) {
        Node* node{ head };

        while(node != nullptr){
        	if(node->child != nullptr){
        		Node* buff{ node->next };

        		node->next = flatten(node->child);
        		node->next->prev = node;
        		node->child = nullptr;

        		while(node->next != nullptr){
        			node = node->next;
        		}

        		node->next = buff;
        		buff->prev = node;
        	}

        	node = node->next;
        }

        return head;
    }
};


int main(){



	return 0;
}