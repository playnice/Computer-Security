#include <openssl/aes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//AES_BLOCK_SIZE is defined to be 16 bytes(128-bits) in openssl/aes.h

unsigned char indata[AES_BLOCK_SIZE]; //input data
unsigned char outdata[AES_BLOCK_SIZE]; //output data
unsigned char decrypt_data[AES_BLOCK_SIZE]; //decrypted data

//Key size are categorize into 128-bit, 192-bit and 256-bit
unsigned char userkey128[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F";
unsigned char userkey192[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17";
unsigned char userkey256[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F";

//Our initialization vector
unsigned char IV[] = "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F";

//Create key class
AES_KEY key;

void encrypt(){
    FILE *in_file_path, *out_file_path;
    in_file_path = fopen("plaintext", "r+");  //Read from plaintext
    out_file_path = fopen("ciphertext", "w+");//Write to ciphertext
    int postion = 0;
    int bytes_read;

	//Recursively perform Cipher Feedback Mode Encryption
    while (1) {
        unsigned char ivec[AES_BLOCK_SIZE];

		//Copy our GLobal Initialization Vector(IV) into ivec with respect to AES block size (16-bytes)
        memcpy(ivec, IV, AES_BLOCK_SIZE);

		//Read 128-bits of plaintext file into indata and records number of bytes read into bytes_read
        bytes_read = fread(indata, 1, AES_BLOCK_SIZE, in_file_path);

		//CFB encrypt function requires:
		//@PARAMETER: indata	   - Data to be encrypted, in this case it is our plaintext message
		//			  outdate 	   - Encrypted data, in this case it is our ciphertext
		//			  bytes_read   - Information of our plaintext size
		//			  &key		   - AES keys
		//			  ivec		   - Initialization Vector 
		//			  &position    - To record how much of the 128-bit block we have used
		//			  &AES_ENCRYPT - Our encryption type	
        AES_cfb128_encrypt(indata, outdata, bytes_read, &key, ivec, &postion, AES_ENCRYPT);

		//Write outdata into ciphertext file
        fwrite(outdata, 1, bytes_read, out_file_path);

		//Detect if it is the last block for encryption, end if last block
        if (bytes_read < AES_BLOCK_SIZE)
            break;
    }
	//Closes file
    fclose(in_file_path);
    fclose(out_file_path);
}


void decrypt(){
    FILE *in_file_path, *out_file_path;
    in_file_path = fopen("ciphertext", "r+"); //Read from ciphertext
    out_file_path = fopen("decrypted-plaintext", "w+"); //Write to decrypted-plaintext
    int postion = 0;
    int bytes_read;

	//Recursively perform Cipher Feedback Mode Decryption
    while (1) {
        unsigned char ivec[AES_BLOCK_SIZE];

		//Copy our GLobal Initialization Vector(IV) into ivec with respect to AES block size (16-bytes)
        memcpy(ivec, IV, AES_BLOCK_SIZE);

		//Read 128-bits of ciphertext file into outdata and records number of bytes read into bytes_read
        bytes_read = fread(outdata, 1, AES_BLOCK_SIZE, in_file_path);

		//CFB encrypt function requires:
		//@PARAMETER: outdata	   - Encrypted data, in this case it is our ciphertext
		//			  decrypt_data - Decrypted data, in this case it is our decrypted plaintext
		//			  bytes_read   - Information of our plaintext size
		//			  &key		   - AES keys
		//			  ivec		   - Initialization Vector 
		//			  &position    - To record how much of the 128-bit block we have used
		//			  &AES_ENCRYPT - Our encryption type	
        AES_cfb128_encrypt(outdata, decrypt_data, bytes_read, &key, ivec, &postion, AES_DECRYPT);

		//Write decrpyt_data into decrypted-plaintext file
        fwrite(decrypt_data, 1, bytes_read, out_file_path);
        if (bytes_read < AES_BLOCK_SIZE)
            break;
    }
	//Closes file
    fclose(in_file_path);
    fclose(out_file_path);
}


void banner(){
	printf("+------------------------------------+\n");
    printf("|    Advanced Encryption Standard    |\n");
    printf("|                with                |\n");
    printf("|      Cipher Feedback Mode          |\n");
    printf("+------------------------------------+\n");
}

int main() {
	banner();
    printf("Please choose your AES key size:\n");
    printf("1. 128-bit\n");
    printf("2. 192-bit\n");
    printf("3. 256-bit\n");
    int input;
	int cont = 1;
    scanf("%d", &input);
    do{
		switch(input){

		    case 1:
		        AES_set_encrypt_key(userkey128, 128, &key); //Perform Key Expansion to generate round keys based on key-size
		        cont = 0;
		        break;

		    case 2:
		        AES_set_encrypt_key(userkey192, 192, &key); //Perform Key Expansion to generate round keys based on key-size
		        cont = 0;
		        break;

		    case 3:
		        AES_set_encrypt_key(userkey256, 256, &key); //Perform Key Expansion to generate round keys based on key-size
		        cont = 0;
		        break;

		    default:
		        printf("Invalid value, please input again:\n");
		        scanf("%d", &input);
		        continue;
		}
	}while(cont == 1);
	system("clear");
	
	banner();
    printf("Please choose one of the following:\n");
    printf("1. Encryption only\n");
    printf("2. Decryption only\n");
    printf("3. Encryption & Decryption\n");   

	cont = 0;
	scanf("%d", &input);
	system("clear");
	do{
		switch(input){

			case 1:
				encrypt();
	   			printf("Finished encrypting......\n");
				cont = 0;
				break;

			case 2:
				decrypt();
				printf("Finished decrypting......\n");
				cont = 0;
				break;

			case 3:
				encrypt();
				decrypt();
				printf("Finished both encryption and decryption......\n");
				cont = 0;
				break;

			default:
		        printf("Invalid value, please input again:\n");
		        scanf("%d", &input);
		        continue;		
		}
	}while(cont == 1);
    return 0;
}
