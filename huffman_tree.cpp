#include "huffman_tree.h"
using namespace std;
//priority queues and maps
/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Reads the contents of file_name and constructs a
				huffman tree based on the character frequencies of the file contents
*/

huffman_tree::huffman_tree(const string &file_name) {
	ifstream myText(file_name);
	char ch; //ch is whatever character you've landed on while iterating
	if (myText.is_open()) {
		while (myText.get(ch)) {
			string cha = string(1, ch);
			pair<int, string> pear(1, cha);
			bool added = false;
			for (auto iter = myMap.begin(); iter != myMap.end(); iter++)
			{
				if (iter->second == pear.second)
				{
					pair<int, string> pear2(iter->first+1, cha);
					myMap.erase(iter);
					myMap.emplace(pear2);
					added = true;
					break;
				}
			}
			if (!added)
			{
				myMap.emplace(pear);
			}
		}
	}
	myText.close(); //close the file
	for (auto iterator = myMap.begin(); iterator != myMap.end(); iterator++) {
		pq.push_back(nodeFunction1((*iterator).first, ((*iterator).second)));
	}
	//priority queue is done!

	Node* temp1 = new Node();
	Node* temp2 = new Node();
	while (pq.size() > 1) {
		temp1 = pq[0];
		pq.erase(pq.begin());
		temp2 = pq[0];
		pq.erase(pq.begin());
		int total = temp1->f + temp2->f;
		Node* pnode = parent(total, temp1, temp2);
		if (pq.size() != 0)
		{
			bool added = false;
			for (auto iter = pq.begin(); iter != pq.end(); iter++)
			{
				if ((*iter)->f >= pnode->f)
				{
					pq.insert(iter, pnode);
					added = true;
					break;
				}
			}
			if (!added)
			{
				pq.push_back(pnode);
			}
		}
		else
		{
			pq.push_back(pnode);
		}
		
	}
}

string huffman_tree::recursion_encode(Node* currnode, string s, char c) const {
	if ((currnode->ch).length() != 0)
	{
		string cha = string(1, c);
		if (currnode->ch == cha)
		{
			return s;
		}
		else
		{
			return "";
		}
	}
	else
	{
		string s1 = recursion_encode(currnode->left, s + "0", c);
		string s2 = recursion_encode(currnode->right, s + "1", c);
		if (s1 == "" && s2 == "")
		{
			return "";
		}
		else if (s2 == "")
		{
			return s1;
		}
		else
		{
			return s2;
		}
	}
}

string huffman_tree::recursion_decode(Node* currnode, string s) const {
	if ((currnode->ch).length() != 0)
	{
		return currnode->ch;
	}
	else
	{
		if (s[0] == '0' && s.length() != 0)
		{
			return recursion_decode(currnode->left, s.substr(1, s.length()));
		}
		else if (s[0] == '1' && s.length() != 0)
		{
			return recursion_decode(currnode->right, s.substr(1, s.length()));
		}
		else 
		{
			return "";
		}
	}
}

huffman_tree::~huffman_tree() {

}

/*
Preconditions: Character is a character with an ASCII value
				between 0 and 127 (inclusive).
Postconditions: Returns the Huffman code for character if character is in the tree
				and an empty string otherwise.
*/
string huffman_tree::get_character_code(char character) const {
	if (pq.size() != 0)
	{
		if ((pq[0]->ch.length()) != 0)
		{
			string cha = string(1, character);
			if (pq[0]->ch == cha)
			{
				return "0";
			}
			else
			{
				return "";
			}
		}
		else
		{
			return recursion_encode(pq[0], "", character);
		}
	}
	else
	{
		return "";
	}
}

/*
Preconditions: file_name is the name of (and possibly path to) a text file
Postconditions: Returns the Huffman encoding for the contents of file_name
				if file name exists and an empty string otherwise.
				If the file contains letters not present in the huffman_tree,
				return an empty string
*/
string huffman_tree::encode(const string &file_name) const {
	ifstream myText(file_name);
	if (!myText)
	{
		return "";
	}
	char ch;
	string s;
	if (myText.is_open()) {
		while (myText.get(ch)) {
			string code;
			code = get_character_code(ch);
			if (code != "")
			{
				s += get_character_code(ch);
			}
			else
			{
				myText.close();
				return "";
			}
		}
	}
	myText.close(); //close the file
	return s;
}

/*
Preconditions: string_to_decode is a string containing Huffman-encoded text
Postconditions: Returns the plaintext represented by the string if the string
				is a valid Huffman encoding and an empty string otherwise
*/
string huffman_tree::decode(const string &string_to_decode) const {
	string s;
	unsigned int pos = 0;
	if (pq.size() != 0)
	{
		while (pos < string_to_decode.length())
		{
			string c = recursion_decode(pq[0], string_to_decode.substr(pos, string_to_decode.length()));
			if (c.length() == 0)
			{
				return "";
			}
			else
			{
				s += c;
				const char* cha = c.c_str();
				pos += get_character_code(cha[0]).length();
			}
		}
	}
	else
	{
		return "";
	}
	return s;
}