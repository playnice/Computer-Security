#include<iostream>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<ctime>
#include <Windows.h>
using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}

double GetCounter()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double(li.QuadPart-CounterStart)/PCFreq;
}

int main()
{
	//Monoalphabetic Substitution (Additive Cipher) Time Complexity- O(n)
	system("CLS");
	FILE *in, *op;
	int key;
	int t1;
	char c;
	int byte = 0;
	int ope;
	in = fopen("anip.txt","r");//Load the plaintext txt file
	op = fopen("anop.txt","w");//Save the ciphertext into the txt file
	cout<<"\n Caesar Cipher"; 
	cout<<"\n What do you want to perform:";
	cout<<"\n 1. Encryption";
	cout<<"\n 2. Decryption";
	cout<<"\n==>";
	cin>>ope;
	 
	cout<<"\n Enter Key(0 until 25):";
	cin>>key;//Input key in integer
	if(ope == 1){
	    //Encryption
	    StartCounter();
	    while(!feof(in))//Get everything until the end of the line of txt file. 
	    {
	        c = fgetc(in);//Get the word or sentence from the txt file
	 
	        if(c==-1)
	        break;
	        if(isupper(c))//Check the character of the word is uppercase
	        {
		        t1 = (int) c-65;
		        t1 = (t1+key)%26;
		        t1 = t1 + 65;
		        fputc((char) t1,op);
	        }
	        else if(islower(c))//Check the character of the word is lowercase
	        {
		        t1 = (int) c-97;
		        t1 = (t1+key)%26;
		        t1 = t1 + 97;
		        fputc((char) t1,op);// Input all character of the word that encrypted into the txt file
	        }
	        else{
	        	fputc(c,op);
	        }
	        byte = byte + sizeof t1;
	    }
	    double interval = GetCounter();
		cout << "Time : " << interval << " microseconds\n"; 
		double byTi;
		cout << "Total bytes : " << byte << endl;
		byTi = byte/interval;
		cout << "Total plaintext in bytes encrypted/Encryption Time : " << byTi << "bytes/microseconds\n";	    
	}
	else{
	    //Decryption
	    StartCounter();
	    while(!feof(in))//Get everything until the end of the line of txt file. 
	    {
	        c = fgetc(in);//Get the word or sentence from the txt file
	 
	        if(c==-1)
	        break;
	        if(isupper(c))
	        {
		        t1 = (int) c-65;// Using the ASCii code value to find character position and the start of 'A' is 65 ASCii Code Value
		        t1 = ((t1-key)+26)%26;//Character need to minus the key value and add the 26(That is a-z position value), modulus the 26.
		       	t1 = t1 + 65;
		        fputc((char) t1,op);
	        }
	        else if(islower(c))
	        {
		        t1 = (int) c-97;// Using the ASCii code value to find character position and 'the start of 'a' is 97 ASCii Code Value
		        t1 = (t1-key+26)%26;
		        t1 = t1 + 97;
		        fputc((char) t1,op);// Input all character of the word that decrypted into the txt file
	        }
	        else{
	        	fputc(c,op);
	        }
	        byte = byte + sizeof t1;
	    }
	    double interval = GetCounter();
		cout << "Time : " << interval << " microseconds\n"; 
		double byTi;
		cout << "Total bytes : " << byte << endl;
		byTi = byte/interval;
		cout << "Total ciphertext in bytes decrypted/Decryption Time : " << byTi << "bytes/microseconds\n";
	}
	//ending
	fclose(in);//Close the file of input
	fclose(op);//Close the file of output 

	cout<<"\n Done";
	getch();//For console wait for some time to print out the output
	return 0;
}
