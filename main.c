#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

//custom header file
#include "RSA.h"
#include "render.h"

//function declarations

void key_generation();
void encryption_algo(long int, long int);
void decryption_algo(long int, long int);



int ciphered_txt[100];
long int n,phifunction;
struct keys keyed;
char ch;
int temp[100]= { 0 },temp_num;

int save (int *a, int check)
{
    FILE *file;
        int i;
        char name[99];
        printf("Name of file:");
        scanf("%s",name);
        file=fopen(name,"w");
        if(file==NULL)
            printf("No file found");
        
        if(check==0){
        for (i=0;a[i]!='\0';i++)
            fprintf(file,"%d ",a[i]);
        }
        else if(check==1){
        for (i=0;a[i]!='\0';i++)
            fprintf(file,"%c",a[i]);
        }
        
    fprintf(file,"\0");
    print_exit();
    exit(0);
    return 0;
}

int read(int check)
{
    FILE *file;
    temp_num=0;
    memset(temp,0,sizeof(temp));
    char fn[99];
    printf("Enter the name of file to open:");
    scanf("%s",fn);
    file=fopen(fn,"r");
    if(file==NULL)
        exit(0);
    
    if(check == 0){
        for (temp_num=0;temp[temp_num]!=EOF;temp_num++)
        {
        fscanf(file,"%c",&temp[temp_num]);
        }
        temp[temp_num]=0;
    }
    else if(check==1){
        for (temp_num=0;temp[temp_num]!=EOF;temp_num++)
        {
        fscanf(file,"%d ",&temp[temp_num]);
        }
        temp[temp_num]=0;
    }
    // int j=0;
    // while(temp[j]!=0){
    //     printf("%d\t",temp[j]);
    //     j++;
    // }
    return 1;
}


int main(){
    
    int choose=0,choose_1=0,choose_2=0;
    long int pub_key=0,pri_key=0,mod_n=0;

    welcome();
    by_cryptics();
    while(1){
    printf("Enter:\n1 to generate keys.\n2 to encrypt.\n3 to decrypt\n0 to exit\n\n");
    scanf(" %d", &choose);

    if(choose == 0){
        print_exit();
        break;
    }
    else if(choose == 1){
        print_generate_keys();
        key_generation();
        pub_key = keyed.e;
        pri_key = keyed.d;
        mod_n = n;
    }
    else if(choose == 2){
        print_encrypting();
        if(pub_key==0){
            printf("Enter public key(e) and modulo(n):\n");
            scanf(" %ld %ld", &pub_key, &mod_n);
        }
        else{
            printf("Would you like to encrypt using custom encryption keys?\n If yes, press 1 \nElse to encrypt using recently generated keys, Enter any key\n");
            scanf(" %d", &choose_1);
            if(choose_1 == 1){
                printf("Enter public key(e) and modulo(n):\n");
                scanf(" %ld %ld", &pub_key, &mod_n);
            }
        }
        encryption_algo(pub_key,mod_n);
    }

    else if(choose == 3){
        print_decrypting();
        if(pri_key==0){
            printf("Enter private key(d) and modulo(n):\n");
            scanf(" %ld %ld", &pri_key, &mod_n);
        }
        else{
            printf("Would you like to decrypt using custom encryption keys?\n If yes, press 1 \nElse to encrypt using recently generated keys, Enter any key\n");
            scanf(" %d", &choose_2);
            if(choose_2 == 1){
                printf("Enter private key(d) and modulo(n):\n");
                scanf(" %ld %ld", &pri_key, &mod_n);
            }
        }
        decryption_algo(pri_key,mod_n);
    }
    else{
        printf("\n\n........Enter a valid number...........\n\n");
    }
    printf("\n---------------------------------------------------------------\n");
    
    }
    return 0;
}


void key_generation(){

    int p,q,loop=1;

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
        
    }
    
    phifunction = (long int)((p-1)*(q-1));
    n = (long int)(p * q);

    keyed = generate_keys(phifunction);
    printf("Public Key: %li\n",keyed.e);
    printf("Private Key: %li\n",keyed.d);
    printf("Modulo: %li\n",n);
}

void encryption_algo(long int public_key, long int modulo_n){
    char input_txt[100];
    long int encrypted_number= { 0 };


    //ask for file input
    char cha;
    int num;
    fflush(stdin);
    printf("Press r to read from a text file, else press any other key to continue:\n");
    cha = getchar();

    if(cha=='r' || cha=='R'){
        read(0);
        // for(int nu = 0; nu < temp_num;nu++){
        //     encrypted_numbers[nu] = temp[nu];
        // }
        int loop=0;
        while(temp[loop]!=0){
            input_txt[loop] = temp[loop];
            loop++;
        }
        input_txt[loop] = 0;
        num = loop;
    }else{
        printf("Enter the text to be encrypted:\n");
        // scanf("%[^\n]s",input_txt);
        fflush(stdin);
        gets(input_txt);
        num = strlen(input_txt);
    }

    for(int i=0;i<num;i++){
        printf("%d\t",input_txt[i]);
    }
    printf("\n\n");

    int i=0;
    while(input_txt[i]!='\0'){
    encrypted_number = encrypt((long int)input_txt[i],public_key,modulo_n);
    ciphered_txt[i] = (int)encrypted_number;
    i++;
    }
    


    printf("The ciphered text is:\n");
    for(int j=0;j<i;j++){
    printf("%d\n",ciphered_txt[j]);
    }

    fflush(stdin);
    printf("\n\nWould you like to save the encrypted data in a file?\nPress y for yes or any other character for No!\n");
    ch = getchar();

    if(ch=='y' || ch == 'Y'){
        save(ciphered_txt,0);
    }

}


void decryption_algo(long int private_key, long int modulo_n){
    int encrypted_numbers[100],num=1,decrypted_txt[100];
    encrypted_numbers[0]=1;
    long int decrypted_number;

    //ask for file input
    char cha;
    fflush(stdin);
    printf("Press r to read from a text file, else press any other key to continue:\n");
    cha = getchar();

    if(cha=='r' || cha=='R'){
        read(1);
        // for(int nu = 0; nu < temp_num;nu++){
        //     encrypted_numbers[nu] = temp[nu];
        // }
        int loop=0;
        while(temp[loop]!=0){
            encrypted_numbers[loop] = temp[loop];
            loop++;
        }
        encrypted_numbers[loop] = 0;
        num = loop;
    }
    else{
        printf("Enter the ciphered numbers and press 0 to End:\n");
        fflush(stdin);
        scanf(" %d",&encrypted_numbers[0]);
        while(encrypted_numbers[num-1]!=0){
            scanf(" %d",&encrypted_numbers[num]);
            num++;
        }
    }

    for(int j=0;j<num;j++){
    decrypted_number = decrypt(encrypted_numbers[j],private_key,modulo_n);
    decrypted_txt[j] = (int)decrypted_number;
    }

    printf("The decrypted text is:\n");
    for(int j=0;j<num;j++){
    printf("%c",decrypted_txt[j]);
    }

    //save or not!
    fflush(stdin);
    printf("\n\nWould you like to save the derypted data in a file?\nPress y for yes or any other character for No!\n");
    ch = getchar();

    if(ch=='y' || ch == 'Y'){
        save(decrypted_txt,1);
    }
}