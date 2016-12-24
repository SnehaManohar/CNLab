#include <iostream>
using namespace std;

int main() {
	string data;
	cout << "Enter data in binary: ";
	cin >> data;
	int n = data.size(), code[20] = {}, i;
	for (i = 1; n > 0; i++) {
		if (i & (i - 1))
			code[i] = data[--n] - '0';
	}
	
	for (int j = 1; j < i; j <<= 1) {
		for(int k = j + 1; k < i; k++) {
			if (j & k)
				code[j] ^= code[k];
		}
	}
	/* can be hard coded as 
	code[1] = code[3] ^ code[5] ^ code[7] ^ code[9] ^ code[11] ^ code[13] ^ code[15];
	
	code[2] = code[3] ^ code[6] ^ code[7] ^ code[10] ^ code[11] ^ code[14] ^ code[15];
	
	code[4] = code[5] ^ code[6] ^ code[7] ^ code[12] ^ code[13] ^ code[14] ^ code[15];
	
	code[8] = code[9] ^ code[10] ^ code[11] ^ code[12] ^ code[13] ^ code[14] ^ code[15];
	/* */
	
	cout << "Code word: ";
    while (--i)
        cout << code[i];
    cout << endl;
    
    string cw;
    cout << "Enter received code in binary: ";
	cin >> cw;
	int error[5] = {};
	n = cw.size();
	for (i = 0; i < 20; i++)
	    code[i] = 0;
	
	i = 1;
	while (n--)
	    code[i++] = cw[n] - '0';
	
	n = 0;
	for (int j = 1; j < i; j <<= 1) {
		for(int k = j; k < i; k++) {
			if (j & k)
				error[n] ^= code[k];
		}
		n++;
	}
	/* can be hard coded as 
	error[0] = code[1] ^ code[3] ^ code[5] ^ code[7] ^ code[9] ^ code[11] ^ code[13] ^ code[15];
	
	error[1] = code[2] ^ code[3] ^ code[6] ^ code[7] ^ code[10] ^ code[11] ^ code[14] ^ code[15];
	
	error[2] = code[4] ^ code[5] ^ code[6] ^ code[7] ^ code[12] ^ code[13] ^ code[14] ^ code[15];
	
	error[3] = code[8] ^ code[9] ^ code[10] ^ code[11] ^ code[12] ^ code[13] ^ code[14] ^ code[15];
	/*
	*/
	
	n = 0;
	for (i = 0; i < 5; i++)
	    n += error[i] << i;
	if (n) {
	    cout << "Error in position " << n << endl;
	    cw[cw.size() - n] ^= 1;
	    // 48 and 49 are interchanged when xorred with 1, giving the same result as characters.
	    cout << "Corrected code word: " << cw << endl;
	}
	else
	    cout << "No error";
	return 0;
}
