#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "scrambleheader.h"

using std::string;
using std::endl;
using std::cout;
using std::cin;
using std::ifstream;
using std::ofstream;

//#define TEST_READ_FILE
#ifdef TEST_READ_FILE
void test_read_file(std::string word_file_path, string* words, int size);
#endif

//long file paths again, ugh.
const string INPUT_PATH = "words.txt";
const string OUTPUT_PATH = "scrambled_words.txt";
int main() {
  #ifdef TEST_READ_FILE
  std::string *test = new std::string[6];
  test_read_file("words_fixture.txt", test, 6);
  #endif
  // get number of words in file
  int size = word_count(INPUT_PATH);

  // create empty array of size equal to count
  std::string *original = new std::string[size];

  // populate array by passing it into the read file function
  read_file(INPUT_PATH, original, size);

  // create empty array for scrambled words parallel to original
  // when scrambling, do not write over original array for comparisons
  // later on.
  std::string *scrambled = new std::string[size];

  // for each word in original array, scramble and store in new array
  for (int index = 0; index < size; index++) {
    scrambled[index] = scramble(original[index]);
  }

  // write contents of scrambled to file for viewing/testing
  write_file(scrambled, size);

  start(size);

  int i = 0;
  string input;
  bool correct = false;
  int strikes = 0;
  string guess[3];
  int index = 0;  // used to iterate through guess array
  int total_correct = 0;

  /*
   * Would like to break this next part down into some smaller functions :)
   */

  //iterate through each word while input given is not "exit"
  while(i < size && input != "exit"){
    cout << "WORD " << i + 1 << ": " << scrambled[i] << endl <<
      "Enter your guess or enter 'exit' to quit: ";
    input = get_input();
    while (correct != true && strikes < 3 && input != "exit") {
      guess[index] = input; // set guess at current index equal to input
      cout << endl << "Scrambled Word: " << scrambled[i] << endl;
      for (int x = 0; x < index + 1; x++) {  // prints each guess so far
        cout << "Guess " << x + 1 << ": " << guess[x] << endl;
      }
      // now test to see if correct
      if (guess[index] == original[i]) {
        correct = true;
      } else {
        strikes++;
        index++;
        cout << "Strikes: " << strikes << endl;
        cout << "Sorry! That was not correct." << endl << endl;
        // make sure strikes are not equal to three before prompting again.
        if (strikes < 3) {
          cout << "WORD " << i + 1 << ": " << scrambled[i] << endl;
          cout << "Enter your guess or enter 'exit' to quit: ";
          input = get_input();
        }
      }
    }
    // determine what caused the loop to end (exit or max strikes) and take action accordingly
    if(input != "exit") {
      if(correct) {
        total_correct++;
        cout << "You guessed correctly!" << endl << endl;
        cout << "Score: " << total_correct << endl;
      } else {
        cout << "You've used all of your guesses." << endl << endl;
        cout << "Score: " << total_correct << endl;
      }
      cout << "On to the next word!" << endl << endl;
      strikes = 0; // reset strikes
      index = 0; // reset index of guesses
      correct = false; // reset correct
      i++; // increase to access next word
    }
  }
  if(input == "exit") {
    cout << endl << "You opted to end the game early."<< endl;
  } else {
    cout << "You have finished the list of words." << endl;
    if(total_correct == 20) {
      cout << endl << "Congratulations! You guess them all correctly!" << endl;
    } else {
      cout << endl << "You did not guess all of the words correctly. Better luck next time!" << endl;
    }
  }
  cout << "Thanks for playing!" << endl;
  cout << "Final Score: " << total_correct << "/" << size << endl << endl;
  cout << "END OF PROGRAM";
  return 0;
}

// get random number that will be the new index to swap current character with
unsigned long random_position(unsigned long size) {
  int random = rand() % size;
  return random;
}

// mix up characters in word by swapping letters
string scramble(string word){
  unsigned long size = word.size();
  for (int i = 0; i < size; i++) {
    unsigned long temp_index = random_position(size);
    char temp = word[temp_index];
    word[temp_index] = word[i];
    word[i] = temp;
  }
  return word;
}

// read unscrambled words from file
void read_file(std::string word_file_path, string* words, int size){
  // open file and store each word in array
  // (Mental Note: do NOT use getline because it will read till line break)
  ifstream file(word_file_path);
  int index = 0;
  for(int index = 0; index < size; index++) {
    file >> words[index];
  }
  file.close();
}

#ifdef TEST_READ_FILE
void test_read_file(std::string word_file_path, string* words, int size){
  read_file(word_file_path, words, size);
  if(words->size() == 6){
    std::cout<< "read file test passed for size" << std::endl;
  }
  if(words[0] == "binary"){
    std::cout<< "read file test passed for read order" << std::endl;
  }
}
#endif

// write scrambled words to file for viewing
void write_file(string* scrambled, int size) {
  ofstream file(OUTPUT_PATH);
  for(int i = 0; i < size; i++){
    file << scrambled[i] << " ";
  }
  file.close();
}

// counts each individual WORD (not line)
int word_count(string path) {
  ifstream file(path);
  string line;
  int count = 0;
  while(file >> line){
    count++;
  }
  file.close();
  return count;
}

// get user input and convert to lower case before returning
string get_input(){
  string input = "";
  getline(cin, input);
  // if no input entered, prompt again
  if(input == ""){
    cout << "You did not enter a guess. Try again: ";
    cin >> input;
  }

  // make sure all entered characters are lower case
  for(int i = 0; i < input.size(); i++){
    input.at(i) = tolower(input.at(i));
  }
  return input;
}

void start(int size) {
  cout << "WORD (UN)SCRAMBLE GAME" << endl;
  cout << "\tInstructions: " << size << " programming-related terms have had their characters mixed up."
            "\n\tCan you unscramble all of them? You have 3 guesses before moving on to the next "
            "word." << endl << endl;
}
