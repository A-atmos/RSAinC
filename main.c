//custom header file
#include"RSA.h"


char input_txt[100]="Gaand Faddiya yeh RSA ne";
int ciphered_txt[100],decrypted_txt[100];

int p,q,input_number;
long int n,phifunction,encrypted_number,decrypted_number;
struct keys keyed;


int main(){
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
    phifunction = (long int)((p-1)*(q-1));
    n = (long int)(p * q);

    keyed = generate_keys(phifunction);
    printf("Public Key: %li\n",keyed.e);
    printf("Private Key: %li\n",keyed.d);
    printf("Modulo: %li\n",n);


    int i=0;
    while(input_txt[i]!='\0'){
    encrypted_number = encrypt((long int)input_txt[i],keyed.e,n);
    ciphered_txt[i] = (int)encrypted_number;
    i++;
    }


    printf("The ciphered text is:\n");
    for(int j=0;j<i;j++){
    printf("%c",ciphered_txt[j]);
    }

    printf("\n---------------------------------------------------------------\n");
   for(int j=0;j<i;j++){
    decrypted_number = decrypt(ciphered_txt[j],keyed.d,n);
    decrypted_txt[j] = (int)decrypted_number;
    }


    printf("The decrypted text is:\n");


    for(int j=0;j<i;j++){
    printf("%c",decrypted_txt[j]);
    }

    return 0;
}