#include <bits/stdc++.h>
using namespace std;

int cipher_matrix[5][5];

void initialize()
{
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			cipher_matrix[i][j] = -1;
		}
	}
}

void generate_matrix(string cipher_keyword)
{
	int present[26];
	int x = 0, y = 0;
	
	for (int i = 0; i < 26; i++){
		present[i] = -1;
	}

	for (int i = 0; i < cipher_keyword.length(); i++){
		char k = cipher_keyword[i];

		if (k == ' '){
			continue;
		}

		if (k >= 65 && k <= 90){
			
			int val = k - 'A';
			
			if (present[val] == -1){
				
				if (val == 9 && present[val - 1] == -1){	
					
					cipher_matrix[x][y++] = val - 1;
					present[val - 1] = 1;

				} else if (val == 9 && present[val - 1] == 1){
					continue;
				} else {
					cipher_matrix[x][y++] = val;
					present[val] = 1;
				}
			} 
		}

		if (k >= 97 && k <= 122){
			
			int val = k - 'a';
					
			if (present[val] == -1){
				
				if (val == 9 && present[val - 1] == -1){	
					
					cipher_matrix[x][y++] = val - 1;
					present[val - 1] = 1;

				} else if (val == 9 && present[val - 1] == 1){
					continue;
				} else {
					cipher_matrix[x][y++] = val;
					present[val] = 1;
				}
			} 
		}

		if (y > 4){
			y = 0;
			x++;
		}
	}

	if (y > 4){
		y = 0;
		x++;
	}

	if (x < 5){
		for (int j = 0; j < 26; j++){
			
			if (present[j] == -1 && j != 9){
					
				if (x < 5 && y < 5){
					cipher_matrix[x][y] = j;
					y++;
					if (y > 4){
						y = 0;
						x++;
					}
				} else {
					break;
				}	
			}
		}
	}
}

vector<int> word_search(int k)
{
	vector<int> v;

	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			if (cipher_matrix[i][j] == k){
				v.push_back(i);
				v.push_back(j);
				break;
			}	
		}
	}

	return v;
}

string two_letter_encryption(string word)
{
	
	int k1 = word[0];
	int k2 = word[1];

	string pair_word = "";
			
	int upper_1 = 0, upper_2 = 0;

	if (k1 >= 65 && k1 <= 90){
		k1 = k1 - 65;
		upper_1 = 1;
	} else {
		k1 = k1 - 97;
	}

	if (k2 >= 65 && k2 <= 90){
		k2 = k2 - 65;
		upper_2 = 1;
	} else {
		k2 = k2 - 97;
	}

	vector<int> dim_k1 = word_search(k1);
	vector<int> dim_k2 = word_search(k2);

	int f1, f2;

	if (dim_k1[0] != dim_k2[0] && dim_k1[1] != dim_k2[1]){

		f1 = cipher_matrix[dim_k1[0]][dim_k2[1]];
		f2 = cipher_matrix[dim_k2[0]][dim_k1[1]];
	}

	if (dim_k1[0] == dim_k2[0] && dim_k1[1] == dim_k2[1]){
				
		int row = dim_k1[0];
		row++;

		if (row > 4){
			row = 0;
		}

		f1 = cipher_matrix[row][dim_k1[1]];
		f2 = cipher_matrix[row][dim_k2[1]];
	}

	if (dim_k1[0] == dim_k2[0] && dim_k1[1] != dim_k2[1]){

		int col_1 = dim_k1[1];
		int col_2 = dim_k2[1];

		col_1++;
		col_2++;

		if (col_1 > 4)
			col_1 = 0;
		
		if (col_2 > 4)
			col_2 = 0;

		f1 = cipher_matrix[dim_k1[0]][col_1];
		f2 = cipher_matrix[dim_k2[0]][col_2];
	}	

	if (dim_k1[0] != dim_k2[0] && dim_k1[1] == dim_k2[1]){

		int row_1 = dim_k1[0];
		int row_2 = dim_k2[0];

		row_1++;
		row_2++;

		if (row_1 > 4)
			row_1 = 0;
		
		if (row_2 > 4)
			row_2 = 0;

		f1 = cipher_matrix[row_1][dim_k1[1]];
		f2 = cipher_matrix[row_2][dim_k2[1]];
	}	

	if (upper_1 == 1){
		f1 = f1 + 65;
	} else {
		f1 = f1 + 97;
	}

	if (upper_2 == 1){
		f2 = f2 + 65;
	} else {
		f2 = f2 + 97;
	}

	pair_word = pair_word + (char)(f1) + (char)(f2);
	return pair_word;	
}

int check_J(char value)
{
	if (value != 'J' && value != 'j')
		return 1;
	else
		return 0;
}

string playfair_encryption(string line)
{
	string word = "";
	string new_line = "";

	for (int i = 0; i < line.size(); i++){

		if (word.length() == 2){
			
			if (check_J(word[0]) == 1 && check_J(word[1]) == 1){
				new_line = new_line + two_letter_encryption(word) + " ";
			} else {
				new_line = new_line + word + " ";
			}	
			word = "";
		}
		
		if (line[i] == ' '){
			continue;
		} else {
			word = word + line[i];
		}
	}

	if (word.length() == 2 && check_J(word[0]) == 1 && check_J(word[1]) == 1){
		new_line = new_line + two_letter_encryption(word);
	} else {
		new_line = new_line + word;
	}

	return new_line;
}

int main()
{
	string line;
	string cipher_keyword;
	
	cout << "Enter Cipher Keyword String :";
	getline(cin, cipher_keyword);
	
	initialize();
	generate_matrix(cipher_keyword);

	ifstream myfile("plain_input_playfair.txt");
	ofstream myfile2("encrypted_output_playfair.txt");

	if (myfile.is_open() && myfile2.is_open()){
		
		while (getline(myfile, line)){
			string encrypted_line = playfair_encryption(line);
			myfile2 << encrypted_line << endl;
		}

		myfile.close();
		myfile2.close();
		
	} else {
		cout << "Unable to open file" << endl;
	}

	return 0;
}