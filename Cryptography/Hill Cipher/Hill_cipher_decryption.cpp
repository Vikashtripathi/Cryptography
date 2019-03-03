#include <bits/stdc++.h>
using namespace std;

int key_matrix[3][3] = {{6, 24, 1}, {13, 16, 10}, {20, 17, 15}}; // keyword used is GYBNQKURP
//float key_matrix_inverse[3][3];
#define m 3
int key_matrix_inverse[3][3] = {{8, 5, 10}, {21, 8, 21}, {21, 12, 8}}; 
 
void getCofactor(int A[m][m], int temp[m][m], int p, int q, int n) 
{ 
    int i = 0, j = 0; 
  
    for (int row = 0; row < n; row++){ 
        for (int col = 0; col < n; col++){ 
            
            if (row != p && col != q) 
            { 
                temp[i][j++] = A[row][col]; 
  
                if (j == n - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
} 
  
int determinant(int A[m][m], int n) 
{ 
    int Det = 0; 
   
    if (n == 1) 
   		return A[0][0]; 
  
    int temp[m][m]; 
  
    int sign = 1;  
  
    for (int f = 0; f < n; f++){

        getCofactor(A, temp, 0, f, n); 
        Det = Det + sign * A[0][f] * determinant(temp, n - 1); 
  
        sign = -sign; 
    } 
  
    return Det; 
} 
  
void adjoint(int A[m][m],int adj[m][m]) 
{ 
    if (m == 1){ 
        adj[0][0] = 1;  
    } 
  
    int sign = 1, temp[m][m]; 
  
    for (int i = 0; i < m; i++){ 
        for (int j = 0; j < m; j++){ 
            
            getCofactor(A, temp, i, j, m); 
 
            if ((i + j) % 2 == 0){
            	sign = 1;
            } else {
            	sign = -1;
            }
  
            adj[j][i] = sign * determinant(temp, m - 1); 
        } 
    } 
} 
  
void inverse_op() 
{ 
    int det = determinant(key_matrix, m); 
    
    if (det == 0){ 
        cout << "Inverse does not exist" << endl; 
    } else {
  
    	int adj[m][m]; 
    	adjoint(key_matrix, adj); 
  
    	for (int i = 0; i < m; i++){ 
        	for (int j = 0; j < m; j++){ 
            	key_matrix_inverse[i][j] = adj[i][j] / float(det); 
  			}
  		}	
  	}
}

vector<int> result(vector<int> v)
{
	vector<int> resultant;

	for (int i = 0; i < m; i++){
		
		int sum = 0;
		for (int j = 0; j < m; j++){
			sum = sum + key_matrix_inverse[i][j] * v[j];
		}

		sum %= 26; 
		resultant.push_back(sum);
	}

	return resultant;
}

string plain_word(vector<int> v)
{
	string word = "";
	
	for (int i = 0; i < v.size(); i++){
		int k = v[i] + 65;
		word = word + (char)k;
	}

	return word;
}

string hill_decryption(string line)
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
				new_line = new_line + plain_word(value) + " ";

				v.clear();
				
				count = 1;
				v.push_back(k);
			}
		}
	}

	if (v.size() == m){
		vector<int> value = result(v);
		new_line = new_line + plain_word(value);
		
	} else if (v.size() < m && v.size() > 0){
		new_line = new_line + plain_word(v);
	}

	return new_line;
}

int main()
{
	string line;
	
	ifstream myfile("encrypted_output_hill.txt");
	ofstream myfile2("decrypted_output_hill.txt");

	if (myfile.is_open() && myfile2.is_open()){
		
		while (getline(myfile, line)){
			string decrypted_line = hill_decryption(line);
			myfile2 << decrypted_line << endl;
		}

		myfile.close();
		myfile2.close();
		
	} else {
		cout << "Unable to open file" << endl;
	}

	return 0;
}