#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <bits/stdc++.h>
#include <iterator>
#include <time.h>
#include <string.h>
#include "stdio.h"
using namespace std;

class Tweet{  //the big ol' tweet generator
  
  protected:
  
    string msg; //message is protected, no editing outside of the function

  public:

    Tweet(string fname){  //tweet takes in a file that will be opened
      string line;  //read line by line
      ifstream inputfile(fname);  //handles the input file with the given filename

      if(inputfile.is_open()){  //if the file input exists

        while(getline(inputfile, line)){  //while there is still more text

          msg.append(line + " "); //add that line to the message
          
        }

        inputfile.close();  //close file when all is said and done

      }

      else{ //file input does NOT exist

        cout << "No file found." << endl; //let the user know the file could not be found
        exit(EXIT_FAILURE); //exits the program with failure status

      }

    };

    string getMsg(){  //getter for the message

      return msg;
      
    };

    void newMsg(){  //created a new message
      vector<string> parsedmsg = parse(msg);  //parses the message word by word
      string masterarr[2][parsedmsg.size() - 1];  //2D array that stores the current and next word, used for markov chain
      
      for(int i = 0; i < parsedmsg.size() - 1; i++){  //places word and next word in proper locations, does this for every line in the array
        masterarr[0][i] = parsedmsg[i];
        masterarr[1][i] = parsedmsg[i+1];
      }

      int match = 1;  //loops through until the end of the message
      vector<string> newtweet;  //new tweet is stored in a vector, easiest to manipulate the data in this case
      int start = (rand() % (parsedmsg.size()/2));  //starting point is random within the first half of the message, helps with sentence variety

      newtweet.push_back(masterarr[0][start]);  //adds the starting point to the new tweet

      vector<string> compare; //adds the next word for all matches of the first word

      vector<string> choice;  //picks one of the matching pairs

      while(match){ //while there are still pairs
        for(int i = 0; i < parsedmsg.size() - 1; i++){  //look through the entire array
          if(newtweet.back() == masterarr[0][i]){ //for each match
            compare.push_back(masterarr[1][i]); //add the potential next word
          }
        }

        if(compare.size() == 0){  //if there are no matches, stop looping
          match = 0;
        }
        else{ //while there are matches
          choice.clear(); //clear the choice each loop
          choice.push_back(compare[(rand() % compare.size())]); //and it becomes a random next word from all the comparisons
          newtweet.insert(newtweet.end(), choice.begin(), choice.end());  //adds the choice word to the tweet
          compare.erase(compare.begin(), compare.end());  //resets the comparison value for the next loop
        }
      }

      for(int i = 0; i < newtweet.size(); i++){ //loops through the final tweet
        cout << newtweet[i] << ' '; //and prints the randomly generated sentence
      }
    };

    vector<string> parse(string filteredmsg){ //function for parsing the initial input file

      vector<string> tokens;  //tokens is the parsed vector
      stringstream check1(filteredmsg); //copies string contents
      string intermediate;  //holds each word

      while(getline(check1, intermediate, ' ')){  //checks at each space

        tokens.push_back(intermediate); //adds each word to the parsed vector

      }

      return tokens;  //returns the parsed vector
      
    }
};


int main() {  //where everything comes together
  srand(time(NULL));  //random initialization (time based)
  string fname; //file to be input
  cout << "Enter a file: "; //user inputs a file
  cin >> fname; //takes in the user input
  Tweet markovTweet(fname); //creates the new tweet with the input file
  markovTweet.newMsg(); //and generates a random message based off of it!
}