#include <stdlib.h>
#include <stdio.h>

typedef struct keys{
    long int e;
    long int d;
}keys;

int check_gcd(long int n1,long int n2){
    int gcd;
    for(int i=1; i <= n1 && i <= n2; ++i)
    {
        // Checks if i is factor of both integers
        if(n1%i==0 && n2%i==0)
            gcd = i;
    }
    if(gcd==1){
        return 1;
    }
    else{
        return 0;
    }
}

struct keys generate_keys(long int phifunction){
    long int e=2,d;
    struct keys key;
    while(1){
        if(check_gcd(e,phifunction)){
            
            d = (phifunction+1)/e;
            if(e*d==(phifunction+1)){

                printf("\n");
                if(d==1){
                    printf("Enter the other pair of prime numbers as there pairs wont give you keys as integers!");
                    exit(1);
                }
                else{
                break;
                }
            }
        }
        e++;
    }
    key.e = e;
    key.d = d;
    return key;
}

long int encrypt(long int in_num,long int e,long int n){
    long int temp_encrypt=1;
    for(long int i =0;i<e;i++){
        temp_encrypt *= in_num;
        temp_encrypt = temp_encrypt % n;
    }
    return temp_encrypt;
}

long int decrypt(long int encrypted_number,long int d,long int n){
    long int temp_decrypt=1;
    for(long int i =0;i<d;i++){
        temp_decrypt *= encrypted_number;
        temp_decrypt = temp_decrypt % n;
        
    }
    return temp_decrypt;
}


int check_prime(int n){
    fflush(stdin);
    if(n%2==0){
        return 0;
    }
    
    for (int i = 2; i <= n / 2; ++i) {
    // condition for non-prime
    if (n % i == 0) {
      return 0;
    }
  }
    return 1;
}