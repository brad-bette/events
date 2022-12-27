#include <iostream>
#include <unordered_map>  // for fast calculations
#include <ctime> // for month calc
#include <cstdlib>
#include <cctype>
#include <fstream>
#include <algorithm>

using std::time;
using std::cout;
using std::endl;
using std::localtime;
using std::string;
using std::toupper;
using std::isalpha;
using std::exit;
using std::ifstream;
using std::pair;
using std::unordered_multimap;

/**
 *  - Created as a learning project in November 2019: Version 1.0
 *
 *  - Added support for color highlighting in December 2019. Version 1.1
 *
 *  - Added support for reading the data file in the users home directory 
 *   in December 2022. Version 1.2
 *
 **/


// translates an integer to a month
string getMonth() {

 time_t t = time(NULL);
 tm* timePtr = localtime(&t);

 string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

 // cout << "month of year = " << 1 + timePtr->tm_mon << endl;
 int month = timePtr->tm_mon;
 return months[month];
}

// checks if the month is there before searching through the map
bool isMonth(string month) {

  string months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  for ( int i = 0; i < 12; i++) {
     if ( month == months[i] ) {
        return true;
     }
  }
  return false;
}

// MOD
// Creates highlighting for special events
void highlighting(string &date) {

// MODS for highlighting
  string highlight = "\e[7m";
  string normal = "\e[27m";

// MODS for background highlighting
  string normalBack = "\e[49m";
  string red = "\e[41m";
  string green = "\e[42m";
  string yellow = "\e[43m";
  string blue = "\e[44m";

  string blink = "\e[5m";
  string dontBlink = "\e[25m";

  char colors[4] = {'R', 'B', 'G', 'Y'};


  // BLINK!
  if ( date.back() == '*' && date[date.size() - 4] == '*') {
     if (date[date.size() - 2] == 'L' && date[date.size() - 3] == 'B') {
	 date.insert(0, blink);
         date.erase(date.size() - 5, date.size());
	 date.append(dontBlink);
     }

  // *color letter* adds a color highlight 
  } else if ( date.back() == '*' && date[date.size() - 3] == '*') {
    //cout << "Special highlight detected" << endl;

    // Test cases for highlight colors
    // Red
    if ( date[date.size() - 2] == colors[0] ) {
	 date.insert(0, red);
    // Blue
    } else if ( date[date.size() - 2] == colors[1] ) {
	 date.insert(0, blue);
    // Green
    } else if ( date[date.size() - 2] == colors[2] ) {
	 date.insert(0, green);
    // Yellow
    } else if ( date[date.size() - 2] == colors[3] ) {
	 date.insert(0, yellow);
    }

    // Clean up the special highlight remarks
    date.erase(date.size() - 4, date.size());

    // Make the output normal
    date.append(normalBack);

  // * by its self creates a inverted highlight
  } else if ( date.back() == '*') {
     date.pop_back();
     date.insert(0, highlight);
     date.append(normal);
  }
}

// Reads the file into the multimap
// excludes coments in the textfile
void readFile(unordered_multimap<string, string> &bday) {

  // get file from the env var $HOME
  // found here: https://stackoverflow.com/questions/35570698/accessing-linux-user-home-directory-with-fstream
  const char* homeDir = std::getenv("HOME");

  // transform the char pointer to a string
  string file = homeDir; file += "/events.txt";

  ifstream in_file(file);
  string month;

  for (string birthday; in_file >> month >> birthday;) {
    // Exclude comments in the file
     if ( month != "#" ) {
       highlighting(birthday);
       std::replace(birthday.begin(), birthday.end(), '_', ' ');  // from <algorithm>
      // This is the same as bellow bday.insert( pair<string,string>(month, birthday) );
      bday.insert( {month, birthday} );
    }
  }
}

// Based on this I found on c++.com
// http://www.cplusplus.com/reference/unordered_map/unordered_multimap/
//
// Searches the map for the matching key values of Month
void searchMap(unordered_multimap<string, string> &bday, string month) {
  // Get the iterator pair made
  pair <unordered_multimap<string, string>::iterator, unordered_multimap<string, string>::iterator> ret;
  ret = bday.equal_range(month);

  // Now get the iterator find what your looking for
  for ( unordered_multimap<string, string>::iterator it=ret.first; it !=ret.second; ++it ) {
      cout << month << " " << it->second << endl;
  }
}

void help(char **argc) {

 string b="\e[1m";
 string nb="\e[0m";

 cout << b << "NAME" << nb << endl
      << "\t" << argc[0] << endl << endl;

 cout << b << "SYNOPSIS" << nb << endl
      << "\t" << b << argc[0] << nb << " [month] or [-h, --help]" << endl << endl;
      
 cout << b << "DESCRIPTION" << nb << endl
      << "\t" << b << argc[0] << nb << " Displays important dates according to the specific month. If there are no arguments, todays month will be used." << endl << endl
      << "The month may be specified as a 3 letter month name, such as Jun or Apr. The months are case sensitive, however you can capitalize the first letter. A full list of months are displayed bellow under " << b << "MONTHS" << nb << "." << endl << endl
      << "There a special color codes that you can customize your date file with, see " << b << "CODES" << nb << " for more information." << endl << endl;

 cout << b << "MONTHS" << nb << endl << endl
      << "Accepted 3 letter months are as follows: " << endl
      << "[jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec]" << endl << endl;

 cout << b << "FILE FORMAT" << nb << endl << endl
      << "To add a date to the program, simply edit the bday.txt file. " << endl
      << "Ex: " << endl
      << "Dec    25th_Xmas" << endl 
      << "Mnth   string^^^" << endl << endl
      << "The first letter of the month must be a capitalized letter." << endl << endl;

 cout << b << "CODES" << nb << endl << endl
      << "These are special highlight codes that allow you to highlight special events under different colors. These color codes should be added at the very end of the string in the date file. The supported color codes are as follows:" << endl << endl
      << "*\tInverted highlight" << endl
      << "*B*\tBlue color highligt" << endl
      << "*Y*\tYellow color highligt" << endl
      << "*G*\tGreen color highligt" << endl
      << "*R*\tRed color highligt" << endl << endl
      << "*BL*\tBlink!" << endl << endl
      << "Ex." << endl
      << "Jul   4th_of_July_*R*" << endl 
      << "Output> Jul  " << "\e[41m" << "4th_of_July" << "\e[49m" << endl;

 exit(-1);
}


// Throw this if it user error
void error() {
 cout << "Expected: a 3 letter month. Ex: Nov" << endl
      << "See --help for more information" << endl;
 exit(-1);
}

int main(int argv, char **argc) {

  string month;

  // Define the map
  //map<string, string> bday;
  unordered_multimap<string, string> bday;

   if (argv == 1) {
       month = getMonth();
   } else if (argv == 2) {
     month = argc[1];

     // Test if month is -h or --help
     if ( month == "-h" || month == "--help") {
	help(argc);
     
     // else test the month
     } else {
        month[0] = toupper(month[0]);
        if ( !isMonth(month) ) {
           error();
        }
     }
   }

  readFile(bday);
  searchMap(bday, month);
}

