#include <bits/stdc++.h>
using namespace std;

int main()
{
	double val = 1 / pow(10, 6);
	ofstream communication_delay("Diffie_Hellman_Delays.txt");

	if (communication_delay.is_open()){
		communication_delay << "When Key size is 128 bits, delay is " << val * 128 * 128 * 128 << " seconds\n"; 
		communication_delay << "When Key size is 256 bits, delay is " << val * 256 * 128 * 128 << " seconds\n"; 
		communication_delay << "When Key size is 512 bits, delay is " << val * 512 * 128 * 128 << " seconds\n"; 
		communication_delay << "When Key size is 1024 bits, delay is " << val * 1024 * 128 * 128 << " seconds\n"; 
	} else {
		cout << "Unable to open file" << endl;
	}
	return 0;
}