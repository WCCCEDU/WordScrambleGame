#include <iostream>
#include <stdlib.h>
#include <fstream>

using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;

string get_user_string();
unsigned long random_position(unsigned long size);
string scramble(string word);
void read_file(string* words, int size);
void write_file(string* scrambled, int size);
int word_count(string path);
void start(int size);
string get_input();
