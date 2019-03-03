#include <bits/stdc++.h>
using namespace std;

string affine_encryption(string line, int a, int b)
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
			
				int x = line[i] - 65;
				int value = x * a + b;
				value = value % 26;
				k = (char)(value + 65);

			} else {

				int x = line[i] - 97;
				int value = x * a + b;
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
	
	ifstream myfile("plain_input_affine.txt");
	ofstream myfile2("encrypted_output_affine.txt");

	if (myfile.is_open() && myfile2.is_open()){
		
		while (getline(myfile, line)){
			string encrypted_line = affine_encryption(line, a, b);
			myfile2 << encrypted_line << endl;
		}

		myfile.close();
		myfile2.close();
		
	} else {
		cout << "Unable to open file" << endl;
	}

	return 0;
}