#include<stdio.h>
#include<math.h>

int p,q,input_number;
long int n,e=1,d=1,phifunction,ed=1,encrypted_number,decrypted_number;
void generate_key();
int check_prime(long int);
void encrypt();
void decrypt();



int main(){
    p=1,q=1,e=1,d=1,ed=1;

    while(1){
        //Takes input if the numbers are prime else asks again for input
        printf("Enter the first prime number\n");
        scanf(" %li",&p);
        printf("Enter the second prime number\n");
        scanf(" %li", &q);

        if(check_prime(p)==1){
            if(check_prime(q)==1){
                break;
            }
            else{
                printf("The second input isnnot a prime number\n");
            }
        }
        else{
            printf("The first input isnot a prime number\n");
        }

    }

    n = (long int)(p * q);
    generate_key();
    printf("Public Key: %li\n",e);
    printf("Private Key: %li\n",d);
    printf("Modulo: %li\n",n);

    printf("Enter a number to encrypt:\n");
    scanf(" %d", &input_number);
    if(input_number>n){
        printf("Since the value of modulo is less than entered number try another number or larger prime couples.\n\n-----------------------------------------------------------------------------\n\n");
        main();
    }
    else{
    encrypt();
    decrypt();
    printf("The encrypted form of %d is %li\n",input_number,encrypted_number);
    printf("The decrypted form of %li is %li\n",encrypted_number,decrypted_number);
    }

    return 0;
}

//Check If the number is prime or not
int check_prime(long int n){
    
    if(n<=2){
        return 1;
    }
    if (n%2==0 || n<=1){
        return 0;
    }
    int sqr = (int)((int)sqrt(n)+1);
    for(int i = 3; i<sqr;i=i+2){
        if(n%i==0){
            return 0;
        }
    }
    return 1;
}


//Generate the keys
void generate_key(){
    phifunction = (long int)((p-1)*(q-1)+1);
    ed = e*d;
    
    while(ed!=phifunction){
        e+=1;
        d = (phifunction/e);
        ed = e *d;
    }
}


void encrypt(){
    long int temp_encrypt=1;
    for(long int i =0;i<e;i++){
        temp_encrypt *= input_number;
        temp_encrypt = temp_encrypt % n;
    }
    encrypted_number = temp_encrypt; 
}


void decrypt(){
    long int temp_decrypt=1;
    for(long int i =0;i<d;i++){
        temp_decrypt *= encrypted_number;
        temp_decrypt = temp_decrypt % n;
        
    }
    decrypted_number = temp_decrypt; 
}