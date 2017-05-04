#include<bits/stdc++.h>
#define MAX 10000

using namespace std;

int m[MAX][MAX];

int lps(string &text);   
void printMatrix(int n);

int main() {
    int t;
    string text;
    

    cin >> t;
    for(int i = 0; i < t; ++i) {
        cin >> text;
        cout << lps(text) << endl;
    }

    return 0;
}

// Print matrix from DP
void printMatrix(int n) {
    for(int i = 0; i < n; ++i ) {
        for( int j = 0; j < n; ++j )
            cout << m[i][j] << " ";
        cout << endl;
    }
}
 
// Find Largest Palindrome Subsequence
// Returns its size
int lps(string &text) {
    int n = text.length();
    //cout << "LENGHT: " << n << endl;
   
    memset(m, 0, sizeof(m[0][0]) * n * n);

    // Palindrome of 1 letter only has size 1
    for(int i = 0; i < n; ++i)
        m[i][i] = 1;
   
    // cout << "Got here!" << endl;
    // printM(n);

    // Substring length varies from 2 to size of text string
    int sub_len;
    for(int sub_len = 2; sub_len <= n; ++sub_len)
        // Index for left most letter: i
        for( int i = 0; i <= n - sub_len; ++i) {   
           // Index for the right most letter: j
           
           int j = i + sub_len - 1;
           // cout << "I and J are " << i << " " << j << endl;
           
           // Only two equal letters in substring
           if ( text[i]==text[j] && sub_len==2 )
                m[i][j] = 2;
            
           // More than 2 letters, with right and leftmost equal
           else if ( text[i]==text[j] )
               m[i][j] = m[i+1][j-1] + 2;

           // More than 2 letters, with right and leftmost different
           else
               m[i][j] = max( m[i+1][j], m[i][j-1] );
        }

    // printMatrix(n);

    return m[0][n-1];
}
