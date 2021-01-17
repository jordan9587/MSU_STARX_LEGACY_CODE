/* Gets a list of numbers (buffer_read for example) as a string and separates values into an int array

Notes:
I didn't do anything to account for the \r at the end of the string.
It seems to work fine without removing it from the string, though.
*/

#include <iostream>
#include <string>
using namespace std;

int main () {
    
    string buffer_read = "11,22,13,34,5,6,73,156,9,10,1001,12\r";   // Example string
    string str = "";    // placeholder used for breaking apart buffer_read into it's components
    int values[12];     // integer array for storing our values
    int count = 0;      // count used for keeping track of position in integer array

    for(int i = 0; i < buffer_read.length(); i++) {     // loop for as long as there are characters
        if(buffer_read.substr(i, 1) != ",") {           // if read character is not a comma
            str +=  buffer_read.substr(i, 1);           // add it to our placeholder string str
            if(i+1 == buffer_read.length()) {               // special case for final value (no comma after last number)
                values[count] = stoi(str);                  // string to int. store value in the array
            }
        } else {                                        // for when we finally do reach a comma
            values[count] = stoi(str);                  // string to int. store value in the array
            count++;                                    // increase position for the next value to be stored in the array
            str = "";                                   // reset the placeholder
        }
    }

    cout << buffer_read << '\n';    //print to check values
    for(int i = 0; i < 12; i++) {
        cout << values[i] << ' ';
    }
}