#include <iostream>
#include <string>

using namespace std;

int main(){

    for (int x = 0; x < 10 ; x++){

        cout << "x = " << x << endl;

    }
    int i = 0;
    while (i<10){

        cout << "i = " << i << endl;
        i++;

    // string, vectors, etc. (but not C style arrays) will have a "size" type... this is usually an unsigned int

    // What is the difference between signed int & unsigned int?
    // int(signed int) (1 bit gets used for sign, 31 bits get used for value)... -(2^31) -1 ... (2^31) -1
    // unsigned int (32 bits for value) ... 0 ... (2^32) -1

    // -Wall flag when compiling
    
    /*
    int size;
    cin >> size;
    double a[size]; // This won't work
    */

    /*
    -C++
    'hello' <-- won't compile, because '' is for one char
    
    char c1 = 'h';
    char c2 = 'hello'; <-- won't compile

    -C style string is an ARRAY of char, ending in '\0'
    char* s1 = "hello"; <-- correct , same as {'h','e','l','l','o','\0'}
    
    */

    //I/O files we'll use ifstream/ofstream

    /*
    std::string my_string_var2(10, ' ');
    cout << my_string_var2;
    Outputs 10 white space characters

    General Syntax--
    string my_string_var(size int x, char c);
    
    /*
    --How to convert a C-style string to a C++ string

    C Style -- 
    char c1[6] = "hello" -- 6th spot holds '\0'
    
    Converts to C++ --
    std::string s1(c1);

    What about the other direction --
    std::string s2 = "Another string here!";
    char c2[100] = s2.c_str()
    
    */

    /*
    In my terminal I type --
        t his a str
    ing
        wow
    
    Code -- 
    std::string temp;
    while (cin >> temp) {
        cout << temp.size();
    }
    
    -- Read in "t"    1
    -- Read in "his"  3
    -- Read in "a"    1
    -- Read in "str"  3
    -- Read in "ing"  3
    -- Read in "wow"  3 
    
    
    
    
    */

    }





    return 0;
}


