#include <bits/stdc++.h>
using namespace std;

int key_matrix[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}}; // keyword used is GYBNQKURP
int m = 3;

vector<int> result(vector<int> v)
{
	vector<int> resultant;

	for (int i = 0; i < m; i++){
		
		int sum = 0;
		for (int j = 0; j < m; j++){
			sum = sum + key_matrix[i][j] * v[j];
		}

		sum %= 26; 
		resultant.push_back(sum);
	}

	return resultant;
}

string cipher_word(vector<int> v)
{
	string word = "";
	
	for (int i = 0; i < v.size(); i++){
		int k = v[i] + 65;
		word = word + (char)k;
	}

	return word;
}

string hill_encryption(string line)
{
	string new_line = "";

	int count = 0;
	vector<int> v;

	for (int i = 0; i < line.size(); i++){

		if (line[i] == ' '){
			continue;
		} else {
			
			int k = line[i] - 65;
			
			if (count < m) {	
				v.push_back(k);
				count++;
			} else {
				vector<int> value = result(v);
				new_line = new_line + cipher_word(value) + " ";

				v.clear();
				
				count = 1;
				v.push_back(k);
			}
		}
	}

	if (v.size() == m){
		vector<int> value = result(v);
		new_line = new_line + cipher_word(value);
		
	} else if (v.size() < m && v.size() > 0){
		new_line = new_line + cipher_word(v);
	}

	return new_line;
}

int main()
{
	string line;
		
	ifstream myfile("plain_input_hill.txt");
	ofstream myfile2("encrypted_output_hill.txt");

	if (myfile.is_open() && myfile2.is_open()){
		
		while (getline(myfile, line)){
			string encrypted_line = hill_encryption(line);
			myfile2 << encrypted_line << endl;
		}

		myfile.close();
		myfile2.close();
		
	} else {
		cout << "Unable to open file" << endl;
	}

	return 0;
}