#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class Min_Heap_Node{
	public:
	    string data_field;
	    Min_Heap_Node *left_child, *right_child;
		
		Min_Heap_Node(string data_field){
			this->data_field = data_field;
			left_child = NULL;
			right_child = NULL;
		}
};

vector<int> read_file_Main(char* my_file){
	ifstream infile(my_file, ios::binary | ios::in);
	vector<int> my_vector;
	char ch;
	int bit;
	int i = 0;
	while (infile.get(ch)){
		i=0;
	    while(i < 8){
	    	bit = (ch >> i) & 1;
	        my_vector.push_back(bit);
	        i++;
	    }
	}
	return my_vector;
}

vector<int> Read_Encoded_File(char* my_file){
	vector<int> my_vector = read_file_Main(my_file);
	return my_vector;
}


Min_Heap_Node *Create_Huffman_Tree_Main(char* my_file){
	map<string, string> Map;
	Min_Heap_Node* root = new Min_Heap_Node("$");
	Min_Heap_Node* head = root;
	Min_Heap_Node *temp = root;
	//feed code table to hashmap
	ifstream infile(my_file);
    if (infile.is_open()){
        string key, value;
        while (infile >> key >> value){
        	Map[key] = value;
	    }
	}
	else{
		cout<<"Could not open file\n";
	}

	//build huffman from code table
	for (map<string,string>::iterator x=Map.begin(); x!=Map.end(); ++x){
		root = temp;
    	for (int i=0; i < x->second.size(); i++){
    		
	        if(x->second[i]!='0'){
	        	if(!root->right_child)
	        		root->right_child = new Min_Heap_Node("$");
	        	root = root->right_child;
	        }
	        else{
	        	if(!root->left_child)
	        		root->left_child = new Min_Heap_Node("$");
	        	root = root->left_child;
	        }
    	}
    	root->data_field = x->first;
    }
    return head;
}

Min_Heap_Node *Create_Huffman_Tree(char* my_file){
	Create_Huffman_Tree_Main(my_file);
}



void Decode_Code_Table(Min_Heap_Node* root, vector<int> my_vector){
	Min_Heap_Node* head = root;
	ofstream outfile("decoded.txt");
    int i;
    
    if (outfile.is_open()){
	    for(i = 0; i<my_vector.size(); i++){
	    	if(my_vector[i])
	            root = root->right_child;
	        else
	            root = root->left_child;

	        if(!root->left_child && !root->right_child){
	            outfile << root->data_field << endl;
	            root = head;
	        }
	    }
	}
	else{
		cout<<"Could not open file\n";
	}
	outfile.close();
}

int main(int argc, char *argv[]){
	if(argc != 3)
    	cout<<"usage: "<< argv[0] <<" <my_file> " << "<my_file> " << endl;
  	else{
		vector<int> my_vector = Read_Encoded_File(argv[1]);
		Min_Heap_Node* head = Create_Huffman_Tree(argv[2]);
		Decode_Code_Table(head, my_vector);
	}
	return 0;
}

