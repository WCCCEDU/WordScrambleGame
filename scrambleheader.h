
std::string get_user_string();
unsigned long random_position(unsigned long size);
std::string scramble(std::string word);
void read_file(std::string word_file_path, std::string* words, int size);
void write_file(std::string* scrambled, int size);
int word_count(std::string path);
void start(int size);
std::string get_input();
