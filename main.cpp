//
//  main.cpp
//  LRUCache
//
//  Created by Yuliia Ivanechko on 22.11.2021.
//
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node
{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache
{
   
   protected:
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};

class LRUCache : public Cache
{
private:
    int capacity;
    int pointer = 0;
public:
    LRUCache(int n)
    {
        this -> capacity = n;
        this-> head = new Node (0, 0);

        Node* current = head;
        for (int i = 0; i != n; i++)
        {
            Node* temp = new Node (0, 0);
            current -> next = temp;
            temp -> prev = current;
            mp.emplace(i, temp);
            current = temp;
        }
        this -> tail = current;
    }
    
    virtual void set(int a, int b)
    {
        if (this -> pointer == this -> capacity - 1 )
        {
            this -> pointer = 0;
        }
        this -> mp[this -> pointer] -> key = a;
        this -> mp[this -> pointer] -> value = b;
        this -> pointer++;
    }
    virtual int get(int f)
    {
        std::map<int, Node*>::iterator result = std::find_if(mp.begin(), mp.end(), [f](const std::pair<int, Node*>& el){ return el.second -> key == f; });
        if (result == mp.end())
        {
            return -1;
        }
        else
        {
            return result -> second -> value;
        }
    }
    ~LRUCache()
    {
        for (std::size_t i = 0; i != this->capacity; ++i)
        {
            Node* temp = tail -> prev;
            delete tail;
            temp -> next = nullptr;
            this -> tail = temp;
        }
        delete this -> head;
        head = nullptr;
    }
};

int main() {
   int n, capacity, i;
   cin >> n >> capacity;
   LRUCache l(capacity);

   for(i = 0; i < n; i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
