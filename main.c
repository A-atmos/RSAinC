//custom header file
#include"RSA.h"




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

    printf("Enter the number to encrypt:\n");
    scanf(" %d", &input_number);
    if(input_number>n){
        printf("Since the value of modulo is less than entered number try another number or larger prime couples.\n\n-----------------------------------------------------------------------------\n\n");
        main();
    }
    else{
    encrypted_number = encrypt((long int)input_number,keyed.e,n);
    decrypted_number = decrypt(encrypted_number,keyed.d,n);
    printf("The encrypted form of %d is %li\n",input_number,encrypted_number);
    printf("The decrypted form of %li is %li\n",encrypted_number,decrypted_number);
    }

    return 0;
}