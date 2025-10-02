#include <iostream>
#include "Food.h"
using namespace std;

// node singly linked list
struct SNode
{
    Food food;
    struct SNode *next;
};

// singly linked list
struct SinglyLinkedList{
    SNode* Head=NULL;
    SNode* Tail=NULL;

    Food getValue(int ind){
        if(ind<0){
            throw runtime_error("index khong hop le");
        }
        SNode*curNode = Head;
        for(int i=0;i<ind && curNode != nullptr;i++){
            curNode=curNode->next;
        }
        if(curNode==nullptr){
            throw runtime_error("index khong hop le");
        }
        return curNode->food;
    }

    void add(Food f){
        if(!Head){
            SNode* newHead = new SNode;

            newHead->food=f;
            newHead->next=NULL;
            Head=newHead;
            Tail=newHead;
        }else{
            SNode* nextNode=new SNode;
            nextNode->food = f;
            nextNode->next=NULL;

            Tail->next = nextNode;
            Tail = nextNode;
        }
    }

    // void insertIndex(Food f, int ind){
    //     if(ind<0){
    //         throw runtime_error("index khong hop le");
    //     }
    //     if(ind==0){
    //         SNode* newNode = new SNode;
    //         newNode->food = f;
    //         newNode->next = Head;
    //         Head = newNode;
    //         return;
    //     }

    //     int curInd=0;
    //     SNode* curNode = Head;
    //     SNode* prevNode = NULL;

    //     while(curNode){
            
    //         if(curInd == ind){
    //             SNode* newNode = new SNode;
    //             newNode->food = f;
    //             newNode->next = curNode;
    //             prevNode->next = newNode;
    //             return;
    //         }

    //         prevNode=curNode;
    //         curNode=curNode->next;
    //         curInd++;
    //     }

    //     if(curInd==ind){
    //         SNode* newNode=new SNode;
    //         newNode->food=f;
    //         newNode->next=NULL;
    //         prevNode->next=newNode;
    //     }else{
    //         throw runtime_error("index khong hop le");
    //     }
    // }

    // void print(){
    //     SNode* curNode = Head;
    //     while(curNode){
    //         cout<<curNode->food.name<<" ("<<curNode->food.price<<" VND)";
    //         cout<<", ";
    //         curNode=curNode->next;
    //     }
    //     cout<<endl; 
    // }

    int getSize(){
        int count = 0;
        SNode* curNode=Head;
        while(curNode != NULL){
            count++;
            curNode=curNode->next;
        }
        return count;
    }

    void removeAt(int ind){
        if(Head==NULL || ind < 0){
            throw runtime_error("index khong hop le");
        }
        if(ind==0){
            Head=Head->next;
            return;
        }
        SNode* curNode=Head;
        for(int i=0; curNode!=NULL && i<ind-1; i++){
            curNode=curNode->next;
        }
        if(curNode==NULL || curNode->next==NULL){
            throw runtime_error("index khong hop le");
        }
        curNode->next=curNode->next->next;
    }

    // void clear(){
    //     Head=NULL;
    //     Tail=NULL;
    //     return;
    // }

    // void removeAll(string foodName){
    //     if(Head==NULL){
    //         return;
    //     }

    //     while(Head != NULL && Head->food.name == foodName){
    //         Head=Head->next;
    //     }

    //     if(Head==NULL){
    //         Tail=NULL;
    //         return;
    //     }   

    //     SNode* curNode=Head;
    //     while(curNode->next!=NULL){
    //         if(curNode->next->food.name==foodName){
    //             curNode->next=curNode->next->next;
    //         }else{
    //                 curNode=curNode->next;
    //         }
    //     }
    //     Tail = curNode; 
    //     return;
    // }

    // template<std::size_t N>
    // void addRange(Food (&fs)[N]){
    //     for(int i=0;i<N;i++){
    //         add(fs[i]);
    //     }
    //     return;
    // }

    // SNode* getNode(int ind){
    //     if(ind<0){
    //         throw runtime_error("index khong hop le");
    //     }

    //     SNode* curNode=Head;
    //     for(int i=0; i < ind && curNode != NULL;i++){
    //         curNode=curNode->next;
    //     }

    //     if(curNode==NULL){
    //         throw runtime_error("index khong hop le");
    //     }
    //     return curNode;
    // }

    // void insertNode(Food f,SNode* node){
    //     if(node == NULL){
    //         throw runtime_error("node khong hop le");
    //     }
    //     SNode* newNode=new SNode;
    //     newNode->food = f;
    //     newNode->next=node->next;
    //     node->next=newNode;

    //     if(node==Tail){
    //         Tail=newNode;
    //     }
    //     return;
    // }

    // void remove(SNode* node){
    //     if(Head==NULL || node==NULL){
    //         throw runtime_error("node khong hop le");
    //     }

    //     if(node==Head){
    //         Head=Head->next;
    //         if(Head==NULL){
    //             Tail=NULL;
    //         }
    //         return;
    //     }

    //     SNode* prev=Head;
    //     while(prev->next != NULL && prev->next != node){
    //         prev=prev->next;
    //     }

    //     if(prev->next==node){
    //         prev->next=node->next;
    //         if(node==Tail){
    //             Tail=prev;
    //         }
    //     }else{
    //         throw runtime_error("node khong ton tai trong danh sach");
    //     };
    // }

    // void insertHead(Food f){
    //     SNode* newNode = new SNode;
    //     newNode->food = f;
    //     newNode->next = Head;
    //     if(Head==NULL){
    //         Head=newNode;
    //         Tail=newNode;
    //     }else{
    //         Head=newNode;
    //     }
    //     return;
    // }

    // void insertTail(Food f){
    //     SNode* newNode = new SNode;
    //     newNode->food = f;
    //     newNode->next = NULL;
    //     if(Head==NULL){
    //         Head=newNode;
    //         Tail=newNode;
    //     }else{
    //         Tail->next=newNode;
    //         Tail=newNode;
    //     }
    //     return;
    // }
};
