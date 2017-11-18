#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <time.h>

using namespace std;

vector<string> my_vector;

//MinHeap Node Structure
class Min_Heap_Node{
    string data_field;  //Input characters
    int frequency;  //Chracter Frequency
    Min_Heap_Node *leftChild, *rightChild; 
    
	public:
        Min_Heap_Node(string data_field, int frequency){	//Contructor Method
		    this->data_field = data_field;
		    this->frequency = frequency;
		    this->leftChild = this->rightChild = NULL;
		}
		
		int get_frequency_Main(){	//Method to return frequency
		    return this->frequency;
		}
		
		int get_frequency(){	//Calls frequency_main method to return frequency
		    get_frequency_Main();
		}
		
		void set_children_Main(Min_Heap_Node *l, Min_Heap_Node* r){		//Method sets pointer of left child and right child
		    this->leftChild = l;
		    this->rightChild = r;
		}
		
		void set_children(Min_Heap_Node *l, Min_Heap_Node* r){		// Calls method to set children pointer
		    set_children_Main(l,r);
		}
		
		bool is_child(int child){		//Method to check whether a node is a child node
		    if(child == 0 and this->leftChild){
		        return true;
		    }
		    else if(child == 1 and this->rightChild){
		        return true;
		    }
		    return false;
		}
		
		Min_Heap_Node* get_child(int child){	//Method to get child - left child if value is 0 and right child if value is 1
		   if(child == 0){
		        return this->leftChild;
		    }
		    else{
		        return this->rightChild;
		    }
		}
		
		string get_data(){		//Method to get data field
		    return this->data_field;
		}
		
		int isLeaf(){		//Method to check whether node is leaf node or not
		    return !(this->leftChild) && !(this->rightChild);
		}        
};

/*
 *  Four Way Heap Class
 */
class Four_Way_Heap{
    private:
        int CSize;		//Denotes Current Size
        int size;
        Min_Heap_Node **four_way_array;		//Array implementation of 4 Way Heap
    public:

        Four_Way_Heap(int capacity){		//Constructor Method
            CSize = 3;						//Sets Current Size to 3 for optimization
            size = capacity + 4;			//Sets size of array for optimization
            four_way_array = new Min_Heap_Node*[capacity + 4];
            int i = 0 ; 
			while(i < capacity + 4){		//Initialise Array
				four_way_array[i] = NULL;
				i++;
			}
                
        }
 
        bool Check_EmptyMain(){		//Main Method to check whether heap is empty or not
            
        }
        
        bool Check_Empty(){			//Calls main method to check for empty heap
        	Check_EmptyMain();
            return CSize < 4;
        }
 
        bool Check_FullMain(){		///Main Method to check whether heap is full or not           
        }
        
        bool Check_Full(){			//Calls Main Method to check for full heap
        	Check_FullMain();
            return CSize == size;
        }
 
        int parent(int i){		//Method to return parent of i'th Node
            return (i/4 + 2);
        }
 
        int k_Child(int i, int k){		//Method to return index of the k'th child of node i
            return 4 * (i-2) + (k-1);
        }
 
        void insert(Min_Heap_Node* temp){		//Method to insert node into Heap
            if (Check_Full()){
                cout<<"Array Index Out of Bounds"<<endl;
                return;
            }
            int blank = CSize;
            CSize++;
            four_way_array[blank] = temp;
            Up_Heapify(blank);
        }
 
        Min_Heap_Node* findMin(){		//Method to find minimum element out of heap.
            if (Check_Empty()){
                cout<<"Underflow"<<endl;
                return 0;
            }
            return four_way_array[0];
        }

        Min_Heap_Node* deleteMin(){		//Method to delete minimum element out of heap
            if (Check_Empty()){
                cout<<"Underflow"<<endl;
                return 0;
            }
            Min_Heap_Node* Key = four_way_array[3];
            four_way_array[3] = four_way_array[CSize - 1];
            CSize--;
            Down_Heapify(3);
            return Key;
        }
 
        void buildHeap(){		//Method to build Heap
            for (int i = CSize - 1 ; i >= 3; i--)
                Down_Heapify(i);	//Method Call to Heapify Downwards
        }
 
        void Down_Heapify(int blank){		//Method to Heapify Downwards
            int child;
            Min_Heap_Node* temp = four_way_array[blank];
            for ( ; k_Child(blank, 1) < CSize; blank = child){
                child = smallestChild(blank);
                if (four_way_array[child]->get_frequency() < temp->get_frequency())
                    four_way_array[blank] = four_way_array[child];
                else
                    break;
            }
            four_way_array[blank] = temp;
        }
 
        int smallestChild(int blank){		//Method to get Smallest Child
            int bestChild = k_Child(blank, 1);
            int k = 2;
            int candidateChild = k_Child(blank, k);
            while ((k <= 4) && (candidateChild < CSize))
            {
                if (four_way_array[candidateChild]->get_frequency() < four_way_array[bestChild]->get_frequency())
                    bestChild = candidateChild;
                k++;
                candidateChild = k_Child(blank, k);
            }
            return bestChild;
        }
 
 		void Up_Heapify(int blank){		//Method to Heapify Upwards
            Min_Heap_Node* temp = four_way_array[blank];
            for (; blank > 3 && temp->get_frequency() < four_way_array[parent(blank)]->get_frequency(); blank = parent(blank))
                four_way_array[blank] = four_way_array[parent(blank)];
            four_way_array[blank] = temp;
        }
 

        void set_array(int i, string data_field, int frequency){
            this->four_way_array[i] = new Min_Heap_Node(data_field, frequency);
        }

        void set_size(int size){
            this->CSize = size + 3;
        }

        int isSizeOne(){		// Method to check if size of heap is 1 or not
            return (this->CSize == 4);
        }
};

std::string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

// Method to print an array of size n
string Print_Array(int arr[], int n){
    int i;
    string temp = "";
    for (i = 0; i < n; ++i)
        temp = temp + to_string(arr[i]);
    return temp;
}

map<string, string> code_table;
string temp;

void get_Huffman_Code(Min_Heap_Node* root, int arr[], int top){		// Prints huffman codes from the root of Huffman Tree
    
	// Recursive Function
    if (root->is_child(0)){
        arr[top] = 0;
        get_Huffman_Code(root->get_child(0), arr, top + 1);
    }
 
    if (root->is_child(1)){
        arr[top] = 1;
        get_Huffman_Code(root->get_child(1), arr, top + 1);
    }
 
    if (root->isLeaf()){
        code_table[root->get_data()] = Print_Array(arr, top);
    }
}


void get_code_table(){
    ofstream out("code_table.txt");
    if (out.is_open()){
        for(map<string,string>::iterator it=code_table.begin(); it!=code_table.end(); ++it){
            out << it->first << " " << it->second << endl;
        }
        out.close();
    }
    else cout << "Unable to open file" << endl;
}


void get_encoded_data(vector<string> v){
    
	FILE *myfile;
    int bit;
    int current_bit = 0;
    unsigned char bit_buffer;
    string result = "";
    
	for(int i=0; i<v.size(); i++)
        result += code_table[v[i]];
    
	myfile = fopen ("encoded.bin", "wb");
    
	for(int j=0; j<result.size(); j++){
        bit = result[j] - '0';
        if(bit)
            bit_buffer |= (1<<current_bit);
        current_bit++;
        if (current_bit == 8){
            fwrite(&bit_buffer, 1, 1, myfile);
            current_bit = 0;
            bit_buffer = 0;
        }
    }
    fclose(myfile);
}


// Method to build Huffman tree
void Create_Huffman_Tree(map<string, int> FreqTable)
{
    Min_Heap_Node *left, *right, *top;

    Four_Way_Heap* minHeap = new Four_Way_Heap(FreqTable.size());
    int i = 3;
    for(map<string,int>::iterator it=FreqTable.begin(); it!=FreqTable.end(); ++it){
        minHeap->set_array(i, it->first, it->second);
        i++;
    }
    minHeap->set_size(FreqTable.size());
    minHeap->buildHeap();
 
    while(!minHeap->isSizeOne()){
        left = minHeap->deleteMin();
        right = minHeap->deleteMin();
 
        top = new Min_Heap_Node("$", left->get_frequency() + right->get_frequency());
        top->set_children(left, right);
        minHeap->insert(top);
    }
 
    int *arr = new int[FreqTable.size()];
    int head = 0;
    get_Huffman_Code(minHeap->deleteMin(), arr, head);
    get_code_table();
}

map<string, int> read_file(char *filename)
{
	string word;
	map<string, int> FreqTable;
	
	ifstream infile;
	infile.open(filename); 
    
	if (!infile.is_open())
        cout<<"Could not open file\n";
    else{
    	cout << "Reading from the file" << endl; 
    	
        while(!infile.eof( ))
		{
			infile >> word;
			if(word!="")
			{
                my_vector.push_back(word);
                if (FreqTable.find(word) != FreqTable.end())
				{
					FreqTable[word]++;
				}
				else
				{
					FreqTable[word] = 1;
				}	
			}
		}
		
		infile.close();
    }	
    return FreqTable;
}


int main(int argc, char *argv[]){   
    clock_t start_time;
    if (argc != 2) 
        cout<<"usage: "<< argv[0] <<" <filename>\n";
    else{
        map<string, int> input_file = read_file(argv[1]);
        start_time = clock();
        Create_Huffman_Tree(input_file);
        cout << "4 way heap time: " << (clock() - start_time) << " microseconds"<< endl;
        get_encoded_data(my_vector);
    }
}
