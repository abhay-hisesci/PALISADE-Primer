#include "palisade.h"
#include <string>

using namespace lbcrypto;

int main()
{

	int plaintextModulus = 256;
	double sigma = 3.2;
	SecurityLevel seclvl = HEStd_128_classic;
	uint32_t depth = 2;

	CryptoContext<DCRTPoly> cryptoContext = CryptoContextFactory<DCRTPoly>::genCryptoContextBFVrns(plaintextModulus, seclvl, sigma, 0, depth, 0, OPTIMIZED);
	cryptoContext->Enable(ENCRYPTION);
	cryptoContext->Enable(SHE);

	LPKeyPair<DCRTPoly> keyPair;

	keyPair = cryptoContext->KeyGen();

	cryptoContext->EvalMultKeyGen(keyPair.secretKey);

	string phrase1, phrase2, phrase3;
	cout << "Please enter Phrase #1 to encrypt: ";
  	cin >> phrase1;

	cout << "Please enter Phrase #2 to encrypt: ";
  	cin >> phrase2;

	cout << "Please enter Phrase #3 to encrypt: ";
  	cin >> phrase3;

	Plaintext plaintext1 = cryptoContext->MakeStringPlaintext(phrase1);
	Plaintext plaintext2 = cryptoContext->MakeStringPlaintext(phrase2);
	Plaintext plaintext3 = cryptoContext->MakeStringPlaintext(phrase3);

	auto ciphertext1 = cryptoContext->Encrypt(keyPair.publicKey, plaintext1);
	auto ciphertext2 = cryptoContext->Encrypt(keyPair.publicKey, plaintext2);
	auto ciphertext3 = cryptoContext->Encrypt(keyPair.publicKey, plaintext3);

	cout<< "Successfully encrypted!" << std::endl;

	Plaintext plaintextDecrypted1;
	Plaintext plaintextDecrypted2;
	Plaintext plaintextDecrypted3;

	cout << "Now running decryption!" << std::endl;

	DecryptResult result = cryptoContext->Decrypt(keyPair.secretKey,ciphertext1,&plaintextDecrypted1);

	if (!result.isValid) {
		cout << "Decryption failed" << endl;
		return 1;
	}

	if( plaintext1 != plaintextDecrypted1 ) {
		cout << "First decrypted plaintext does not match original plaintext!" << endl;
		cout << "Original Plaintext: " << plaintext1 << endl;
		cout << "Decrypted Plaintext: " << plaintextDecrypted1 << endl;
		return 1;
	}
	else{
		cout << "Decryption successful! Phrase #1:" << plaintextDecrypted1 << endl;
	}

	DecryptResult result2 = cryptoContext->Decrypt(keyPair.secretKey,ciphertext2,&plaintextDecrypted2);

	if (!result2.isValid) {
		cout << "Decryption failed" << endl;
		cout << "Original Plaintext: " << plaintext2 << endl;
		cout << "Decrypted Plaintext: " << plaintextDecrypted2 << endl;
		return 1;
	}

	if( plaintext2 != plaintextDecrypted2 ) {
		cout << "Second decrypted plaintext does not match original plaintext!" << endl;
		return 1;
	}
	else{
		cout << "Decryption successful! Phrase #2:" << plaintextDecrypted2 << endl;
	}

	DecryptResult result3 = cryptoContext->Decrypt(keyPair.secretKey,ciphertext3,&plaintextDecrypted3);

	if (!result3.isValid) {
		cout << "Decryption failed" << endl;
		cout << "Original Plaintext: " << plaintext3 << endl;
		cout << "Decrypted Plaintext: " << plaintextDecrypted3 << endl;
		return 1;
	}

	if( plaintext3 != plaintextDecrypted3 ) {
		cout << "Third decrypted plaintext does not match original plaintext!" << endl;
		return 1;
	}
	else{
		cout << "Decryption successful! Phrase #3:" << plaintextDecrypted3 << endl;
	}

	return 0;
        	

}
