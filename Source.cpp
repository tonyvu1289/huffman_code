﻿#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<bitset>
#include <cstdio> 
#include<sstream>
#define COUNT 10
using namespace std;
struct HuffMan_number {
	char character;
	int number;
	char code[128] = { '\0' };
};
struct HNode {
	char data[256];
	int number;
	//Gợi ý:
	//unsigned char character; //Lưu trữ ký tự cần lưu
	//int frequency; //Lưu trữ tần số xuất hiện của ký tự
	HNode* left; //Con trỏ chỉ sang nút trái của cây
	HNode* right; //Con trỏ chi sang nút phải của cây
};

int exist(vector<HuffMan_number> array, char x);
int exist(char* str, char x);
void sort(vector<HuffMan_number>& ar);
HNode* CreateHNode(vector<HuffMan_number> array);
void insertHNode(vector<HNode*>& array, HNode* x);
int BinarySearchHNode(vector<HNode*>& a, int left, int right, HNode* key);
void parent_data(HNode* parent, HNode* a, HNode* b);
void get_code(vector<HuffMan_number>& array);
int find_code(char x, vector<HuffMan_number> array);

void print_numberlist(vector<HuffMan_number> ar);
void print2D(HNode* root);
void print2DUtil(HNode* root, int space);
int check(vector<HNode*> a);
void print_HuffManCode(vector<HuffMan_number> ar);

void OnBit(unsigned char& byte, int position);
void OffBit(unsigned char& byte, int position);
void OnBit(char& byte, int position);
void OffBit(char& byte, int position);
void BinaryStringToChar(string str, char& ch);

void input_array(vector<HuffMan_number>& number, string FileName);
void writeHuffManTree(string FileName, vector<HuffMan_number> array);
void write_code(string FileName_out, vector<HuffMan_number> array, string FileName_in);
void write_code_2(string FileName_out, vector<HuffMan_number> array, string FileName_in);
void DeCode_HuffManFile(string inputFile, string outputFile);



//void inputNumber_of_char(vector<HuffMan_number>& number, char* sample)
//{
//	int i = 0;
//	while (sample[i] != '\0')
//	{
//		int pos;
//		if ((pos=exist(number, sample[i]))>=0)
//		{
//			number[pos].number++;
//		}
//		else
//		{
//			HuffMan_number temp;
//			temp.character = sample[i];
//			temp.number = 1;
//			number.push_back(temp);
//		}
//		i++;
//	}
//}

int exist(vector<HuffMan_number> array, char x)
{
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i].character == x)
			return i;
	}
	return -1;
}
int exist(char* str, char x)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (x == str[i])
			return 1;
	}
	return 0;
}
void sort(vector<HuffMan_number>& ar)
{
	for (int i = 0; i < ar.size() - 1; i++)
	{
		for (int j = i + 1; j < ar.size(); j++)
			if (ar[i].number > ar[j].number)
			{
				HuffMan_number temp = ar[i];
				ar[i] = ar[j];
				ar[j] = temp;
			}
	}
}
HNode* CreateHNode(vector<HuffMan_number> data_array)
{
	vector<HNode*> node_array(data_array.size());
	for (int i = 0; i < data_array.size(); i++)
	{
		node_array[i] = new HNode();
		node_array[i]->data[0] = data_array[i].character;
		node_array[i]->number = data_array[i].number;
	}

	while (node_array.size() > 1)
	{
		//Create parent node of 2 least appear node
		HNode* a = node_array[0];
		node_array.erase(node_array.begin());
		HNode* b = node_array[0];
		node_array.erase(node_array.begin());
		HNode* parent = new HNode();
		parent->left = a;
		parent->right = b;
		parent->number = a->number + b->number;
		parent_data(parent, a, b);
		insertHNode(node_array, parent);
	//	cout << check(node_array);
	}
	return node_array[0];
}
void insertHNode(vector<HNode*>& array, HNode* x)
{
	int pos = BinarySearchHNode(array, 0, array.size() - 1, x);
	vector<HNode*>::iterator nth = array.begin() + pos;

	array.insert(nth, x);
}
int BinarySearchHNode(vector<HNode*>& a, int left, int right, HNode* key)
{
	if (right<=0)
		return 0;
	if (right <= left)
		return (key->number > a[left]->number) ?
		(left + 1) : left;
	int mid = (left + right) / 2;
	if (key->number == a[mid]->number)
		return mid + 1;
	if (key->number > a[mid]->number)
		return BinarySearchHNode(a, mid + 1, right, key);
	return BinarySearchHNode(a, left, mid - 1, key);
}

void parent_data(HNode* parent, HNode* a, HNode* b)
{
	int i = 0;
	for (int j = 0; a->data[j] != '\0'; j++)
	{
		parent->data[i++] = a->data[j];
	}
	for (int j = 0; b->data[j] != '\0'; j++)
	{
		parent->data[i++] = b->data[j];
	}
}
void get_code(vector<HuffMan_number>& array)
{
	HNode* root = CreateHNode(array);
	for (int i = 0; i < array.size(); i++)
	{
		HNode* temp = root;
		while (strlen(temp->data) > 1)
		{
			if (exist(temp->left->data, array[i].character)) {
				temp = temp->left;
				strcat(array[i].code, "0");
			}
			else
			{
				temp = temp->right;
				strcat(array[i].code, "1");
			}
		}
	}
}
int find_code(char x, vector<HuffMan_number> array)
{
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i].character == x)
			return i;
	}
	cout << "find_code error !" << endl;
	return -1;
}

void print_numberlist(vector<HuffMan_number> ar)
{
	for (int i = 0; i < ar.size(); i++)
	{
		cout << ar[i].character << "	" << ar[i].number << endl;
	}
}
void print_HuffManCode(vector<HuffMan_number> ar)
{
	for (int i = 0; i < ar.size(); i++)
	{
		cout << ar[i].character << "	" << ar[i].code << endl;
	}
}
void print2D(HNode* root)
{
	// Pass initial space count as 0  
	print2DUtil(root, 0);
}
void print2DUtil(HNode* root, int space)
{
	// Base case  
	if (root == NULL)
		return;

	// Increase distance between levels  
	space += COUNT;

	// Process right child first  
	print2DUtil(root->right, space);

	// Print current node after space  
	// count  
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << "_" << root->number << "\n";

	// Process left child  
	print2DUtil(root->left, space);
}
int check(vector<HNode*> a)
{
	for (int i = 0; i < a.size()-1; i++)
	{
		if (a[i]->number > a[i + 1]->number)
			return 0;
	}
	return 1;
}

//position là vị trí 7-i với i là vị trí cần on/off bit
void OnBit(unsigned char& byte, int position)
{
	byte = byte | (1 << position);
}
void OffBit(unsigned char& byte, int position)
{
	byte = byte & ~(1 << position);
}
void OnBit(char& byte, int position)
{
	byte = byte | (1 << position);
}
void OffBit(char& byte, int position)
{
	byte = byte & ~(1 << position);
}
void BinaryStringToChar(string str,char& ch)
{
	for (int i = 0; i < 8; i++)
	{
		if (str[i] == '0')
			OffBit(ch, 7-i);
		else if (str[i] == '1')
			OnBit(ch, 7-i);
	}
}

void input_array(vector<HuffMan_number>& number, string FileName)
{
	fstream input;
	input.open(FileName, ios::in);
	char ch;
	while (input.get(ch))
	{
		int pos;
		if ((pos = exist(number, ch)) >= 0)
		{
			number[pos].number++;
		}
		else
		{
			HuffMan_number temp;
			temp.character = ch;
			temp.number = 1;
			number.push_back(temp);
		}
	}
	input.close();
} 
void writeHuffManTree(string FileName, vector<HuffMan_number> array)
{
	fstream output;
	output.open(FileName, ios::out | ios::trunc | ios::binary);
	output << array.size() << char(16);
	for (int i = 0; i < array.size(); i++){
		output << array[i].character << char(16) << array[i].number << char(16);
	}
	output.close();
}
void write_code(string FileName_out, vector<HuffMan_number> array, string FileName_in)
{
	fstream input;
	fstream output;
	input.open(FileName_in, ios::in);
	output.open("Binary.txt", ios::out | ios::trunc | ios::binary);
	// copy binary string to a file
	int binary_length = 0;
	while (!input.eof())
	{
		char ch;
		input.get(ch);
		int code_index = find_code(ch, array);
		output << array[code_index].code;
		binary_length += strlen(array[code_index].code);
	}
	if ((binary_length % 8) > 0) {
		for (int i = 8 - (binary_length % 8); i > 0; i--)
		{
			output << '0';
			binary_length++;
		}
	}
	output.close();
	input.close();
	output.open(FileName_out, ios::out | ios::app | ios::binary);
	input.open("Binary.txt");
	unsigned char temp;
	for (long j = 0; j < binary_length; )
	{
		for (int i = 0; i < 8; i++) //get 8 bits
		{
			char bin = input.get();

			if (bin == '0')
			{
				OffBit(temp, 7 - i);
			}
			else if (bin == '1')
			{
				OnBit(temp, 7 - i);
			}
			j++;
		}
		output << temp;
	}
	input.close();
	output.close();
}
void write_code_2(string FileName_out, vector<HuffMan_number> array, string FileName_in)
{
	fstream input;
	fstream output;
	input.open(FileName_in, ios::in);
	output.open(FileName_out, ios::out | ios::app | ios::binary);
	char ch;
	string binary_str="";
	while (!input.eof()){
		int index;
		while (binary_str.length() < 8){
			if (!input.get(ch)){
				for (int i = binary_str.length(); i < 8; i++){
					binary_str+='0';
				}
				break;
			}
			index = find_code(ch, array);
			binary_str += array[index].code;
		}
		while (binary_str.length() >= 8){
			BinaryStringToChar(binary_str, ch);
			output << ch;
			binary_str.erase(0, 8);
		}
	}
}
void DeCode_HuffManFile(string inputFile, string outputFile)
{
	fstream input;
	fstream output;
	output.open(outputFile, ios::trunc | ios::out | ios::binary);
	input.open(inputFile, ios::in | ios::binary);
	int size = output.tellg();
	vector<HuffMan_number> array;
	int n;
	long number_of_char = 0;
	input >> n;
	input.ignore();
	array.resize(n);
	for (int i = 0; i < n; i++)
	{
		input.get(array[i].character);
		input.ignore();
		input >> array[i].number;
		input.ignore();
		number_of_char += array[i].number;
	}
	HNode* root = CreateHNode(array);
	HNode* temp = root;
	for (int i = 0; (number_of_char > 0);)
	{
		char ch;
		input.get(ch);
		bitset<8> bin(ch);
		for (int j = 0; j < 8;)
		{
			while (!(temp->left == NULL && temp->right == NULL))
			{

				if (bin[7 - j] == 0) {
					temp = temp->left;
				}
				else {
					temp = temp->right;
				}
				j++;
				if (j >= 8)
					break;
			}
			if (j <= 7) // chua doc het day bit cua ch -> da doc duoc chu can output -> xuat ra file
			{
				output << temp->data;
				temp = root;
				number_of_char--;
				if (number_of_char == 0)
					break;
			}
		}
	}
	//test file binary
/*	fstream binary;
	binary.open("Binary.txt",ios::in);
	for (int i = 0; (number_of_char > 0);)
	{
		char ch_1;
		while (!(temp->left == NULL && temp->right == NULL))
		{
			binary.get(ch_1);
			if (ch_1=='0')
				temp = temp->left;
			else
				temp = temp->right;


		}
			cout << temp->data;
			output << temp->data;
			temp = root;
			number_of_char--;
			if (number_of_char == 0)
				break;
	}*/
	input.close();
	output.close();
}
void LNR(HNode* root)
{
	if (root == nullptr)
		return;
	LNR(root->left);
	LNR(root->right);
	cout << root->number << endl;
}
void main()
{
	string FileName = "Tieng Viet.txt";
	string FileName_out = FileName+".huf";
	string Filename_unzip = "unzip.txt";
	vector<HuffMan_number> number;
	HNode* root;
	input_array(number, FileName);
	sort(number);
	print_numberlist(number); //debug
	root = CreateHNode(number);
	//print2DUtil(root,10);
	//LNR(root);
	get_code(number);
	writeHuffManTree(FileName_out, number);
	write_code_2(FileName_out, number, FileName);
	cout << "Da nen xong! Bat dau giai nen...\n";
	DeCode_HuffManFile(FileName_out, "unzip.txt");//decode, neu khong co nhu cau decode thi xoa dong nay
	cout << "Giai nen thanh cong!\n";
}