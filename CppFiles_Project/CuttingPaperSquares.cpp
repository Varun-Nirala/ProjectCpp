/* HackerRank : Cutting Paper Squares */
#include <iostream>

using namespace std;

long int solve(long int n, long int m){
	return (n*m)-1;
}

int main() {
    long int n;
    long int m;
    cin >> n >> m;
    long int result = solve(n, m);
    cout << result << endl;
    return 0;
}