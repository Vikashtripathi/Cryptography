Example files are generated by using a = 17 and b = 3 in the following equations :
y (cipher_value) = (a * x (plain_text_value) + b) % 26                      // for encryption
x (plain_text_value) = ((a ^ -1) * ((y (cipher_value) - b + 26) % 26) )% 26              // for decryption

However c++ files can generate encrypted and decrypted output for any values of a and b