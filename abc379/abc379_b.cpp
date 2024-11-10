#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, K;
    cin >> N >> K;
    string S;
    cin >> S;
    
    int count = 0;
    // Convert string to mutable character array
    vector<char> teeth(S.begin(), S.end());
    
    for(int i=0; i <= N - K; ){
        bool ok = true;
        for(int j=0; j < K; ++j){
            if(teeth[i+j] != 'O'){
                ok = false;
                break;
            }
        }
        if(ok){
            // Eat a strawberry: set K teeth to 'X'
            for(int j=0; j < K; ++j){
                teeth[i+j] = 'X';
            }
            count++;
            // Move i to the next position after the current K teeth
            i += K;
        }
        else{
            i++;
        }
    }
    
    cout << count;
}
