#include <bits/stdc++.h>
using namespace std;

int modular_inverse(int a, int m)
{
	a = a % m;

	for (int i = 1; i < m; i++){
		if ((a * i) % m == 1){
			return i;
		}
	}
}

string affine_decryption(string line, int a, int b)
{
	string word = "";
	string new_line = "";

	for (int i = 0; i < line.size(); i++){

		if (line[i] == ' '){
			new_line = new_line + word + " ";
			word = "";
		} else {
			char k;
			
			if (line[i] >= 65 && line[i] <= 90){
			
				int y = line[i] - 65; 
				int value = modular_inverse(a, 26) * ((y - b + 26) % 26);
				value = value % 26;
				k = (char)(value + 65);

			} else {

				int y = line[i] - 97;
				int value = modular_inverse(a, 26) * ((y - b + 26) % 26);
				value = value % 26;
				k = (char)(value + 97); 
			}

			word = word + k;
		}
	}

	new_line = new_line + word;
	return new_line;
}

int main()
{
	string line;
	
	int a, b;

	cout << "Enter values of a and b : " << endl; 
	cin >> a >> b;
	
	ifstream myfile("encrypted_output_affine.txt");
	ofstream myfile2("plain_output_decrypted.txt");

	if (myfile.is_open() && myfile2.is_open()){
		
		while (getline(myfile, line)){
			string plain_output_line = affine_decryption(line, a, b);
			myfile2 << plain_output_line << endl;
		}

		myfile.close();
		myfile2.close();
		
	} else {
		cout << "Unable to open file" << endl;
	}

	return 0;
}