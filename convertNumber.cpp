// convertNumber.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
In this kata we want to convert a string into an integer. The strings simply represent the numbers in words.

Examples:

"one" => 1
"twenty" => 20
"two hundred forty-six" => 246
"seven hundred eighty-three thousand nine hundred and nineteen" => 783919
Additional Notes:

The minimum number is "zero" (inclusively)
The maximum number, which must be supported is 1 million (inclusively)
The "and" in e.g. "one hundred and twenty-four" is optional, in some cases it's present and in others it's not
All tested numbers are valid, you don't need to validate them
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

long parse_int(string number)
{
    int numberInt = 0;
    //  vector name number 
    vector <string> stringNumbers = { "zero","one","two","three","four","five","six","seven","eight","nine","ten","eleven","twelve","thirteen","fourteen",
    "fifteen","sixteen","seventeen","eighteen","nineteen","twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    //  use map because it have key and value
    map<string, int> convertStringToInt;    

    //  inicilization map value, example (one = 1)
    for (int i = 0; i < 21; i++)    convertStringToInt[stringNumbers[i]] = i;
    for (int i = 21, j = 30; i < stringNumbers.size(); i++, j+=10)      convertStringToInt[stringNumbers[i]] = j;

    //  divide string number on one word, example (twenty-two hunderd)-> twenty-two(1), hunderd(2)
    vector <string> partStringInput;
    stringstream streamData(number);
    string partStringNumber;

    while(getline(streamData, partStringNumber, ' '))
        partStringInput.push_back(partStringNumber);

    if (number == "one million")                                            //  special option to million (max value)
        return 1000000;

    //  we determine the value in number
    for (int i = 0; i < partStringInput.size(); i++)
    {
        size_t found = partStringInput[i].find("-");
        if (found != string::npos)                                          //  option to example 22 (twenty-two)
        {
            stringstream streamData(partStringInput[i]);
            while (getline(streamData, partStringNumber, '-'))
                numberInt += convertStringToInt[partStringNumber];
        }
        else if (partStringInput[i] == "hundred")                           //  when find hunderd in string
        {
            numberInt -= convertStringToInt[partStringInput[i - 1]];
            numberInt += (convertStringToInt[partStringInput[i-1]]*100);
        }
        else if (partStringInput[i] == "thousand")  numberInt *= 1000;      //  when find thousand in string
        else numberInt += convertStringToInt[partStringInput[i]];           //  other case
    }
    return numberInt;
}

int main()
{
    cout << parse_int("seven hundred eighty-three thousand nine hundred and nineteen");
}

