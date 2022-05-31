#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

#define EMPTY_STRING ""


struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};


Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}


struct comp
{
    bool operator()(const Node* l, const Node* r) const
    {
        // the highest priority item has the lowest frequency
        return l->freq > r->freq;
    }
};

bool isLeaf(Node* root) {
    return root->left == nullptr && root->right == nullptr;
}


void encode(Node* root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr) {
        return;
    }

 
    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}


void decode(Node* root, int &index, string str)
{
    if (root == nullptr) {
        return;
    }

    // found a leaf node
    if (isLeaf(root))
    {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0') {
        decode(root->left, index, str);
    }
    else {
        decode(root->right, index, str);
    }
}

void buildHuffmanTree(string text)
{
    // base case: empty string
    if (text == EMPTY_STRING) {
        return;
    }
    unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }
    priority_queue<Node*, vector<Node*>, comp> pq;

    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    while (pq.size() != 1)
    {

        Node* left = pq.top(); pq.pop();
        Node* right = pq.top();    pq.pop();

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
    Node* root = pq.top();

    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);

    cout << "Huffman Codes are:\n" << endl;
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << endl;
    }

    cout << "\nThe original string is:\n" << text << endl;
    cout<<"size of original string"<<text.length()<<endl;

    string str;
    for (char ch: text) {
        str += huffmanCode[ch];
    }

    cout << "\nThe encoded string is:\n" << str <<"size of encoded"<< str.length()<< endl;
    cout << "\nThe decoded string is:\n";

    if (isLeaf(root))
    {
        while (root->freq--) {
            cout << root->ch;
        }
    }
    else {
        int index = -1;
        while (index < (int)str.size() - 1) {
            decode(root, index, str);
        }
    }
    
}

int main()
{
    string text = "To get a better understanding of how the multi-armed bandits algorithm works, let's look at where the name comes from. This is an analogy with slot machines in a casino which have several levers that a player can pull to get some random amount of money. The player can pull the levers multiple times in any order. Each lever has a fixed probability for the corresponding amount of money given out, but the player does not know how it works and can only learn it from experience playing the game. Once they figure it out, they can maximize their winnings.One approach to maximizing the reward is to evaluate the probability distribution for each lever at each step based on the game statistics from previous steps. Then we mentally win a random reward for each lever, based on the distributions received. Finally, we pull the lever that had the best outcome in our mental game. This approach is called Thompson Sampling";
    buildHuffmanTree(text);

    return 0;
}
