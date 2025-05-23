// C++(STL) program for Huffman Coding with STL 
#include <bits/stdc++.h> 
using namespace std; 
  
// A Huffman tree node 
class MinHeapNode { 
    public:
    // One of the input characters 
    char data; 
  
    // Frequency of the character , unsigned is like int
    unsigned freq; 
  
    // Left and right child 
    MinHeapNode *left, *right; 
  
    MinHeapNode(char data, unsigned freq) 
    { 
  
        left = right = NULL; 
        this->data = data; 
        this->freq = freq; 
    } 
}; 
  
// For comparison of two heap nodes (needed in min heap) 
// Comparator to order the min-heap (priority queue)
class compare { 
    public:
    bool operator()(MinHeapNode* a, MinHeapNode* b) //a=left b =right
    { 
        return (a->freq > b->freq); 
    } 
}; 
  
// Prints huffman codes from the root of Huffman Tree. 
void printCodes(MinHeapNode* root, string str) 
{ 
  
    if (!root) 
        return; 
  
    if (root->data != '$') //ie a,b esa hua
        cout << root->data << ": " << str << "\n"; 
  
    printCodes(root->left, str + "0"); 
    printCodes(root->right, str + "1"); 
} 
  
// The main function that builds a Huffman Tree and 
// print codes by traversing the built Huffman Tree 
void HuffmanCodes(char data[], int freq[], int size) 
{ 
    MinHeapNode *left, *right, *top; 
  
    // Create a min heap & inserts all characters of data[] 
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap; 
  
    for (int i = 0; i < size; ++i) 
        minHeap.push(new MinHeapNode(data[i], freq[i])); 
  
    // Iterate while size of heap doesn't become 1 ie only 1 node left
    while (minHeap.size() != 1) { 
  
        // Extract the two minimum freq items from min heap 
        left = minHeap.top(); 
        minHeap.pop(); 
  
        right = minHeap.top(); 
        minHeap.pop(); 
  
        // Create a new internal node with 
        // frequency equal to the sum of the 
        // two nodes frequencies. Make the 
        // two extracted node as left and right children 
        // of this new node. Add this node 
        // to the min heap '$' is a special value(data) 
        // for internal nodes, not used 
        top = new MinHeapNode('$', left->freq + right->freq); 
  
        top->left = left; 
        top->right = right; 
  
        minHeap.push(top); 
    } 
  
    // Print Huffman codes using the Huffman tree built above 
    printCodes(minHeap.top(), ""); 
} 
  
// Driver Code 
int main() 
{ 
    // int n;
    // cout << "Enter the number of characters: ";
    // cin >> n;

    // char arr[n];
    // int freq[n];

    // cout << "Enter characters:\n";
    // for (int i = 0; i < n; i++) {
    //     cin >> arr[i];
    // }

    // cout << "Enter frequencies of each character:\n";
    // for (int i = 0; i < n; i++) {
    //     cin >> freq[i];
    // }

    // HuffmanCodes(arr, freq, n);

    // return 0;
    
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
  
    int size = sizeof(arr) / sizeof(arr[0]); 
  
    HuffmanCodes(arr, freq, size); 
  
    return 0; 
} 