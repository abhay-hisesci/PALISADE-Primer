#include "palisade.h"

using namespace lbcrypto;

int main()
{

	int plaintextModulus = 65537;
	double sigma = 3.2;
	SecurityLevel seclvl = HEStd_128_classic;
	uint32_t depth = 2;

	CryptoContext<DCRTPoly> cryptoContext = CryptoContextFactory<DCRTPoly>::genCryptoContextBFVrns(plaintextModulus, seclvl, sigma, 0, depth, 0, OPTIMIZED);
	cryptoContext->Enable(ENCRYPTION);
	cryptoContext->Enable(SHE);

	LPKeyPair<DCRTPoly> keyPair;

	keyPair = cryptoContext->KeyGen();

	cryptoContext->EvalMultKeyGen(keyPair.secretKey);

	std::vector<int64_t> intList1 = {1,2,3,4,5,6,7,8,9,10,11,12};
	Plaintext plaintext1 = cryptoContext->MakePackedPlaintext(intList1);
	std::vector<int64_t> intList2 = {12,11,10,1,2,3,9,8,7,4,5,6};
	Plaintext plaintext2 = cryptoContext->MakePackedPlaintext(intList2);
	std::vector<int64_t> intList3 = {12,11,10,9,8,7,6,5,4,3,2,1};
	Plaintext plaintext3 = cryptoContext->MakePackedPlaintext(intList3);

	auto ciphertext1 = cryptoContext->Encrypt(keyPair.publicKey, plaintext1);
	auto ciphertext2 = cryptoContext->Encrypt(keyPair.publicKey, plaintext2);
	auto ciphertext3 = cryptoContext->Encrypt(keyPair.publicKey, plaintext3);

	auto add12 = cryptoContext->EvalAdd(ciphertext1,ciphertext2);
	auto add123 = cryptoContext->EvalAdd(add12, ciphertext3);

	auto mult12 = cryptoContext->EvalMult(ciphertext1, ciphertext2);
	auto mult123 = cryptoContext->EvalMult(mult12, ciphertext3);

	Plaintext plaintextAddResult;
	cryptoContext->Decrypt(keyPair.secretKey, add123, &plaintextAddResult);

	Plaintext plaintextMultResult;
	cryptoContext->Decrypt(keyPair.secretKey, mult123, &plaintextMultResult);

	cout << "Plaintext #1: " << plaintext1 << std::endl;
	cout << "Plaintext #2: " << plaintext2 << std::endl;
	cout << "Plaintext #3: " << plaintext3 << std::endl;

	cout << "plaintexts 1 2 and 3 added together = " << plaintextAddResult << std::endl;
	cout << "plaintexts 1 2 and 3 multiplied together = " << plaintextMultResult << std::endl;

	return 0;
        	

}
