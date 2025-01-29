#include<algorithm>
#include<iostream>
#include<string>
#include<vector>
using namespace std;

/**the main issue with this code relates to the std::for_each() operation within the main() function
 * What was happening on the original version of the problem given on the homework slide
 * is that each item in the names vector of strings is being fed to the maxf instance of maxlenftn
 * but since each of the strings is being input to maxf by value (as opposed to by reference)
 * the operations were happening to a copy of maxf's data, not the actual function
 * Once the std::for_each() operation was finished, the original maxf was untouched
 * Thus, the code prints 0 because maxlen is initialized to 0 in the maxlenftn struct
 * We can resolve this by utilized std::ref, which allows us to pass objects by reference instead
 * This means that every object that is operated on operates directly on the maxf instance of maxlenftn
 * 
 * I have also updated the maxlenftn.operator() function to also accept its input by reference
 * The script will run correctly if maxlenftn.operator() accepts input by value, but it would be less efficient
 */

struct maxlenftn {
    maxlenftn() { maxlen = 5; }
    void operator()(const string& s) {
        maxlen = max(maxlen, s.size());
    }
    string::size_type maxlen;
};

int main() {
vector<string> names{"Smith", "Jones", "Johnson", "Grant"};
maxlenftn maxf;
for_each(names.begin(), names.end(), maxf);
cout << maxf.maxlen << endl;
return 0;
}