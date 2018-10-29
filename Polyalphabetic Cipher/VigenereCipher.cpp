#include<iostream>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<ctime>
#include <fstream>
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
    //Polyalphabetic Substitution (Vigenere Cipher)
    system("CLS");
    FILE *in,*op;
    int k=0;
    int byte;
    double byTi;
    string Result,key,c;
    int ByR;
    int cho;
    in = fopen("vgi.txt","r"); //Load the plaintext txt file
    op = fopen("evgo.txt","r"); 
    cout<<"\n Vigenere Cipher";
    cout<<"\n What do you want to perform:";
    cout<<"\n 1. Encryption";
    cout<<"\n 2. Decryption";
    cout<<"\n 3. Encryption Time";
    cout<<"\n 4. Decryption Time";
    cout<<"\n==>";
    cin>>cho;
     
    cout<<"\n Enter Key:";
    cin>>key;// Input the key in word
     
    if(cho == 1){
        //Encryption Time complexity - O(26^k)
        ofstream myfile("evgo.txt");// Output the ciphertext file from the plaintext file
        while(!feof(in))
        {
            c = fgetc(in);
            for(int i = 0;i<c.length();i++)
            {
                if(isupper(c[i]))//Check the character of the word is uppercase
                {
                    Result[i] = (((c[i]-65)+(key[k]-97))%26)+65;// Using the ASCii code value to find character position and the start of 'A' is 65 ASCii Code Value
                }
                else if(islower(c[i]))//Check the character of the word is lowercase
                {
                    Result[i] = (((c[i]-97)+(key[k]-97))%26)+97;// Using the ASCii code value to find character position and 'the start of 'a' is 97 ASCii Code Value
                }
                k++;
                if(k==key.length())
                    k=0;
            }
            for(int i=0;i<c.length();i++){
                ByR = Result[i];
                byte = byte + sizeof ByR; //Calculate bytes of the each characater in word       
            }
            for(int i=0;i<c.length();i++){
                myfile << Result[i];   
            }    
        }
        myfile.close();
    }
    else if(cho == 2){
        //Decryption
        StartCounter();
        ofstream myoutfile("dvgo.txt");// Output the decrypyte ciphertext to plaintext
        while(!feof(op))
        {
            c = fgetc(op);
            for(int i = 0;i<c.length();i++)
            {
                if(isupper(c[i]))//Check the character of the word is uppercase
                {
                    Result[i] = (((c[i]-65+26)-(key[k]-97))%26)+65;// Using the ASCii code value to find character position and the start of 'A' is 65 ASCii Code Value
                }
                else if(islower(c[i]))//Check the character of the word is lowercase
                {
                    Result[i] = (((c[i]-97+26)-(key[k]-97))%26)+97;// Using the ASCii code value to find character position and 'the start of 'a' is 97 ASCii Code Value
                }
                k++;
                if(k==key.length())
                    k=0;
            }
            for(int i=0;i<c.length();i++){
                ByR = Result[i];
                byte = byte + sizeof ByR;//Calculate bytes of the each characater in word     
            }
            for(int i=0;i<c.length();i++){
                myoutfile << Result[i];   
            }    
        }
        myoutfile.close();
    }
    else if(cho == 3){
        StartCounter();
        while(!feof(in))
        {
            c = fgetc(in);
            for(int i = 0;i<c.length();i++)
            {
                if(isupper(c[i]))//Check the character of the word is uppercase
                {
                    Result[i] = (((c[i]-65)+(key[k]-97))%26)+65;// Using the ASCii code value to find character position and the start of 'A' is 65 ASCii Code Value
                }
                else if(islower(c[i]))//Check the character of the word is lowercase
                {
                    Result[i] = (((c[i]-97)+(key[k]-97))%26)+97;// Using the ASCii code value to find character position and 'the start of 'a' is 97 ASCii Code Value
                }
                k++;
                if(k==key.length())
                    k=0;
            }
            for(int i=0;i<c.length();i++){
                ByR = Result[i];
                byte = byte + sizeof ByR;//Calculate bytes of the each characater in word   
            }
        }
        double interval = GetCounter();
        cout << "Time : " << interval << " microseconds\n";
        byTi = byte/interval;
        cout << "Total bytes : " << byte << " bytes" << endl;
        cout << "Total plaintext in bytes encrypted/Encryption Time : " << byTi << "bytes/microseconds\n";
    }
    else if(cho == 4){
        StartCounter();
        while(!feof(op))
        {
            c = fgetc(op);
            for(int i = 0;i<c.length();i++)
            {
                if(isupper(c[i]))//Check the character of the word is uppercase
                {
                    Result[i] = (((c[i]-65+26)-(key[k]-97))%26)+65;// Using the ASCii code value to find character position and the start of 'A' is 65 ASCii Code Value
                }
                else if(islower(c[i]))//Check the character of the word is lowercase
                {
                    Result[i] = (((c[i]-97+26)-(key[k]-97))%26)+97;// Using the ASCii code value to find character position and 'the start of 'a' is 97 ASCii Code Value
                }
                k++;
                if(k==key.length())
                    k=0;
            }
            for(int i=0;i<c.length();i++){
                ByR = Result[i];
                byte = byte + sizeof ByR;//Calculate bytes of the each characater in word     
            }
        }
        double interval = GetCounter();
        cout << "Time : " << interval << " microseconds\n";
        byTi = byte/interval;
        cout << "Total bytes : " << byte << " bytes" << endl;
        cout << "Total ciphertext in bytes decrypted/Decryption Time : " << byTi << "bytes/microseconds\n";
    }
    // Total plaintext or ciphertext divide by encryption time or decryption time
    //ending
    fclose(in);
    fclose(op);
    cout<<"\n Done";
    return 0;
}
