#include <iostream>
using namespace std;

int main()
{
    int line = 1;
    while (true) {
        string s;
        cin >> s;
   	   if (s != "abcdefghijklmnopqrstuvwxyz")
            cout << line << ": " << s << endl;
   	   line++;
    }
}
