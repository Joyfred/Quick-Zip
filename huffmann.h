
#include <bits/stdc++.h>
#include<utility>
#include<string.h>
using namespace std;

int global_counter=0;

struct MinHeapNode {
 
    char data;
    unsigned freq;
    MinHeapNode *left, *right;
    MinHeapNode(char data, unsigned freq)
    {
 
        left=right=NULL;
        this->data=data;
        this->freq=freq;
    }
};
 
//comparison function for ordering in priority queue
struct compare 
{
 
    bool operator()(MinHeapNode* l,MinHeapNode* r)
 
    {
        return(l->freq > r->freq);
    }
};

void assignCodes(struct MinHeapNode* root,string str,pair<char,string> code[])
{
 
    if (!root)
        return;
 
    if (root->data!='*')
    {
        //cout << root->data << ": " << str << "\n";
        code[global_counter].first=root->data;
        code[global_counter].second=str;
        global_counter+=1;
    }
 
    assignCodes(root->left,str + "0",code);
    assignCodes(root->right,str + "1",code);
}
 
void HuffmanCodes(vector<char> data,vector<int>freq,int size,pair<char,string> code[])
{
    struct MinHeapNode *left, *right, *top;
    //inbuilt priority queue using stl,
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
 
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));
    while (minHeap.size() != 1) 
    {
 
 
        left = minHeap.top();
        minHeap.pop();
 
        right = minHeap.top();
        minHeap.pop();

        top = new MinHeapNode('*', left->freq + right->freq);
 
        top->left = left;
        top->right = right;
 
        minHeap.push(top);
    }
 

    assignCodes(minHeap.top(), "",code);
}
 


 