//custom header file
#include "RSA.h"

#include<string.h>


char input_txt[100];
int ciphered_txt[100],decrypted_txt[100];

int p,q,input_number;
long int n,phifunction,encrypted_number,decrypted_number;
struct keys keyed;


int main(){
    int loop=1;
    while(loop == 1){
        //Takes input if the numbers are prime else asks again for input
        printf("Enter the first prime number\n");
        scanf("%d",&p);
        fflush(stdin);
        printf("Enter the second prime number\n");
        scanf("%d", &q);
        fflush(stdin);
        int is_prime_p,is_prime_q;
        is_prime_p = check_prime(p);
        is_prime_q = check_prime(q);
        // printf("%d %d", is_prime_p,is_prime_q);
        if( is_prime_p && is_prime_q){
            break;
        }
        else{
            printf("Enter the pair of prime numbers\n");
        }

        printf("%d",p);
        printf("%d",q);
        printf("y");
        
    }
    phifunction = (long int)((p-1)*(q-1));
    n = (long int)(p * q);

    keyed = generate_keys(phifunction);
    printf("Public Key: %li\n",keyed.e);
    printf("Private Key: %li\n",keyed.d);
    printf("Modulo: %li\n",n);

    printf("Enter the text to be encrypted:\n");
    gets(input_txt);

    for(int i=0;i<strlen(input_txt);i++){
        printf("%d\t",input_txt[i]);
    }
    printf("\n\n");

    int i=0;
    while(input_txt[i]!='\0'){
    encrypted_number = encrypt((long int)input_txt[i],keyed.e,n);
    ciphered_txt[i] = (int)encrypted_number;
    i++;
    }
    // int i =0;
    // for(i=0;i<strlen(input_txt);i++){
    //     encrypted_number = encrypt((long int)input_txt[i],keyed.e,n);
    //     ciphered_txt[i] = (int)encrypted_number;
    // }


    printf("The ciphered text is:\n");
    for(int j=0;j<i;j++){
    printf("%d\n",ciphered_txt[j]);
    }

    printf("\n---------------------------------------------------------------\n");
   for(int j=0;j<i;j++){
    decrypted_number = decrypt(ciphered_txt[j],keyed.d,n);
    decrypted_txt[j] = (int)decrypted_number;
    }


    printf("The decrypted text is:\n");


    for(int j=0;j<i;j++){
    printf("%d \n",decrypted_txt[j]);
    }

    return 0;
}