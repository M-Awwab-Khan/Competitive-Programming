#include <iostream>
using namespace std;
 
int main() {
	int N;
	cin >> N;
	int sum = 0;
	for(int i = 0;i < N;++i) {
		int nextNumber;
		cin >> nextNumber;
		sum += nextNumber;
	}
	cout << sum << endl;
}