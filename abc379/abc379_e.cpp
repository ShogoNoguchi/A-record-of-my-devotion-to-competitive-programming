#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    ll N;
    cin >> N;
    string S;
    cin >> S;
    
    // Compute prefix_sum[k] = sum_{m=1}^k S[m] * m
    // Using 1-based indexing for prefix_sum
    vector<ll> prefix_sum(N + 1, 0);
    for(ll k =1; k <=N; k++){
        ll digit = S[k-1] - '0';
        prefix_sum[k] = prefix_sum[k-1] + digit * k;
    }
    
    // Create sum_digits[p] = prefix_sum[N -p] for p=0 to N-1
    // sum_digits[0] is least significant digit
    // We will store digits in a vector, least significant first
    vector<ll> sum_digits;
    sum_digits.reserve(N + 10); // Reserve extra space for carries
    for(ll p=0; p <N; p++){
        sum_digits.push_back(prefix_sum[N - p]);
    }
    
    // Perform carry over
    for(ll p=0; p <sum_digits.size(); p++){
        if(sum_digits[p] >=10){
            ll carry = sum_digits[p] /10;
            sum_digits[p] %=10;
            if(p +1 == sum_digits.size()){
                sum_digits.push_back(0);
            }
            sum_digits[p +1] += carry;
        }
    }
    
    // Remove any trailing zeros after carry over
    while(sum_digits.size() >1 && sum_digits.back() ==0){
        sum_digits.pop_back();
    }
    
    // Convert sum_digits to string, most significant digit first
    string result = "";
    for(ll p = sum_digits.size()-1; p >=0; p--){
        result += to_string((int)sum_digits[p]);
    }
    
    cout << result;
}
