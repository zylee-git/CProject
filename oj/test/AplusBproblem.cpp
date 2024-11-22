#include <iostream>
#include <string>
using namespace std;
int main()
{
    int i, carry = 0;
    string n1, n2, result;
    cin >> n1 >> n2;
    int l = max(n1.length(), n2.length());
    for (i = n1.length(); i < l; i++)
        n1 = '0' + n1;
    for (i = n2.length(); i < l; i++)
        n2 = '0' + n2;
    for (i = l - 1; i >= 0; i--)
    {
        int sum = (n1[i] - '0') + (n2[i] - '0') + carry;
        result = to_string(sum % 10) + result;
        carry = sum / 10;
    }
    if(carry)
        result = to_string(carry) + result;
    cout << result << endl;
}