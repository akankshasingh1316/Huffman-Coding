# HuffmanCoding

## PROBLEM STATEMENT

## Encoder
The encoder reads an input file that is to be compressed and generates two output files – the compressed version of the input file and the code table.
      
#### Input Format-

Input file name will be given as a command line argument. This file can have up to 100,000,000 lines and each line will contain a decimal value in the range of 0 to 999,999. 

#### Building Frequency Table-

First step towards Huffman encoding is to build the frequency table for each value in input. As values will be within 0 to 999999, an array can be used for storing frequency for each value. Frequency mapping for the given input file is: 

          0 ==> 4

          2245 ==> 4

          999999 ==> 2

          34 ==> 3

          446 ==> 2

          2 ==> 1

#### Build Huffman Tree and Code Table-

Using a 4-way Heap, build the Huffman code table. The code table can be built from the Huffman tree by doing a traversal of the tree.

#### Encode Data-

Once the code table is built, it can be used to encode the original input file by replacing each input value by its code. Please note that the values are not ASCII characters, rather binary values. You can use "ios::binary" flag in C++, or OutputStream in Java.

#### Output Format-

Encoder program has two output files. One is encoded message in binary format. It must be saved as __*"encoded.bin".*__
Second output is the code table. Each line in this output file will contain value of a leaf node of Huffman tree, and its code separated by a space. It must be saved as __*"code_table.txt"*__. 

## Decoder

The decoder reads two input files - encoded message and code table. The decoder first constructs the decode tree using the code table. Then the decoded message can be generated from the encoded message using the decode tree.

#### Input Format- 

The decoder takes two input files - encoded message and code table. File names will be given as command line arguments. The format of these files is the same as the output format of the encoder, so that the output files of the encoder program can be directly used by the decoder program. Note that the input encoded message will be in binary format, not ASCII characters. You can use ios::binary flag for C++ or InputStream for Java. 

#### Output Format- 

Output of decoder program is the decoded message. It should be saved as __*"decoded.txt"*__. The format of this file is same as the input format for the encoder.

## Files Provided For Testing

* sample1/..             *[small inputs/outputs set]* 
  * i. sample_input_small.txt
  * ii. encoded.bin
  * iii. code_table.txt 
  * iv. decoded.txt

## Run environment 

Write a Makefile to build the code using following command at terminal:  `<$ make>` 

This command will produce two binary files: encoder and decoder. 

As mentioned before, encoder should take one input file. We will run it using following command:

`<$ ./encoder <input_file_name>>`      [For C++]  

`<$ java encoder <input_file_name>>`      [For Java] 

Running encoder program must produce the output files with exact name __*"encoded.bin"*__ and __*"code_table.txt"*__. 

On the other hand, decoder will take two input files. We will run it using following command:  

`<$ ./decoder <encoded_file_name> <code_table_file_name>>`  [For C++]  

`<$ java decoder <encoded_file_name> <code_table_file_name>>` [For Java] 

Running decoder program must produce output file with exact name __*"decoded.txt"*__. 
