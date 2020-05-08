# PALISADE-Primer
PALISADE Primer for CS485

# Primer Tutorial

        This tutorial will guide you through development of your very own applications which can take advantage of homomorphic encryption.  We will demonstrate the ability to encrypt and decrypt given phrases. These phrases can be simple such as a word or it can be operations such as multiplication or addition. This guide assumes you have gained an understanding of the basic Palisade Library, build your own projects using cmake, and how to implement some basic programs. If you need some assistance, please refer to the Palisade Documentation for further information. Follow these links for more information: 
        Official Documentation: https://palisade-crypto.org/documentation/
        GitLab Wiki: https://gitlab.com/palisade/palisade-release/-/wikis/home
# Primer Program #1: Homomorphic Addition and Multiplication
        To create a program that can perform encrypted operations, we need to first create a cryptocontext to be able to call the EvalAdd and EvalMult methods to add and multiply ciphertexts. These methods enable encrypted plaintexts called ciphertexts to be used in mathematical operations. The steps to create the program is to start with creating a cryptocontext. To do this simply establish the parameters first. In this cryptocontext, we will be using DCRTPoly for the underlying lattice layer element.

        We will use a simple plaintext modulus parameter. This signifies the maximum size of the data type to perform a modulus operation, in this case it is an unsigned 32 bit integer:
        	int plaintextModulus = 65537;
        Next we will establish sigma which will be as follows:
                double sigma = 3.2;
        Then we determine the security level which can be 128, 192, or 256 bit security. In this case it is 128 bit. This is shown below:
                SecurityLevel seclvl = HEStd_128_classic;
        Next we determine the maximum key-switching depth for the computation using an unsigned integer that is 32 bits long and defined as follows:
                uint32_t depth = 2;
        Finally we can create the cyrptocontext using our chosen lattice layer, DCRTPoly, and the parameters we have established. We also have to enable encryption and SHE which is somewhat homomorphic encryption which allows for limited computation on encrypted data.
                CryptoContext<DCRTPoly> cryptoContext = CryptoContextFactory<DCRTPoly>::genCryptoContextBFVrns(plaintextModulus, seclvl, sigma, 0, depth, 0, OPTIMIZED);
        	cryptoContext->Enable(ENCRYPTION);
        	cryptoContext->Enable(SHE);
        We then establish our keypair so that we can encrypt our plaintext into ciphertext.  To do this we need to use the KeyGen method provided by the cryptocontext.
                LPKeyPair<DCRTPoly> keyPair;
        	keyPair = cryptoContext->KeyGen();
        Then we use the EvalMultKeyGen method to enable the EvalAdd and EvalMult operations.
        	cryptoContext->EvalMultKeyGen(keyPair.secretKey);
        Now we can declare our plaintext. In this case, we are using an integer list using a vector array. We will declare three separate plaintexts to perform operations on. We will call the method MakePackedPlaintext to create an efficient encoder packing multiple integers into a single plaintext polynomial.
                std::vector<int64_t> intList1 = {1,2,3,4,5,6,7,8,9,10,11,12};
        	Plaintext plaintext1 = cryptoContext->MakePackedPlaintext(intList1);
        	std::vector<int64_t> intList2 = {12,11,10,1,2,3,9,8,7,4,5,6};
        	Plaintext plaintext2 = cryptoContext->MakePackedPlaintext(intList2);
        	std::vector<int64_t> intList3 = {12,11,10,9,8,7,6,5,4,3,2,1};
        	Plaintext plaintext3 = cryptoContext->MakePackedPlaintext(intList3);
        Next we create the ciphertext by using the Encrypt method and the keypair public key we generated earlier along with the plaintext we want to encrypt as parameters.
                auto ciphertext1 = cryptoContext->Encrypt(keyPair.publicKey, plaintext1);
        	auto ciphertext2 = cryptoContext->Encrypt(keyPair.publicKey, plaintext2);
        	auto ciphertext3 = cryptoContext->Encrypt(keyPair.publicKey, plaintext3);
        We can finally perform the operations on the ciphertext using the EvalAdd and EvalMult methods.  The parameters are the ciphertexts we generated or a result of a previous EvalAdd or EvalMult result.
        	auto add12 = cryptoContext->EvalAdd(ciphertext1,ciphertext2);
        	auto add123 = cryptoContext->EvalAdd(add12, ciphertext3);
        	auto mult12 = cryptoContext->EvalMult(ciphertext1, ciphertext2);
        	auto mult123 = cryptoContext->EvalMult(mult12, ciphertext3);
        We can decrypt the results of the previous step using the Decrypt method along with the keypair secret key, the ciphertext addition or multiplication result, and the plaintext variable to save the decrypted result into as parameters.
        	Plaintext plaintextAddResult;
        	cryptoContext->Decrypt(keyPair.secretKey, add123, &plaintextAddResult);
        	Plaintext plaintextMultResult;
        	cryptoContext->Decrypt(keyPair.secretKey, mult123, &plaintextMultResult);
        Finally we display the results along with the original plaintexts.
        	cout << "Plaintext #1: " << plaintext1 << std::endl;
        	cout << "Plaintext #2: " << plaintext2 << std::endl;
        	cout << "Plaintext #3: " << plaintext3 << std::endl;
        	cout << "plaintexts 1 2 and 3 added together = " << plaintextAddResult << std::endl;
        	cout << "plaintexts 1 2 and 3 multiplied together = " << plaintextMultResult << std::endl;
        	return 0;

# Primer Program #2: Input Phrase Encryption and Decryption


# Distribution of Primer Programs

 


