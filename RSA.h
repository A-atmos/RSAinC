
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
    long int array_e[15];
    int loop=2,elem=0;
    struct keys key;


    //generate 15 values of e --|
    while(elem<15){
            if(check_gcd(loop,phifunction)){
                array_e[elem]=loop;
                elem++;
            }
            loop++;
            if(loop>=phifunction){
                break;
            }
        }        

        //randomly allocate the value of e--|

        srand(time(NULL));
        int random_elem = rand() % elem;
        e=array_e[random_elem];
        

        //calculate value of d--|
        int i=1;
        while(i){
            d = (phifunction*i+1)/e;
            if(e*d==(phifunction*i+1)){
                i=0;
                break;
            }
            // printf("%d \n",i);
            i++;
        }

        if(e==d){
            e = generate_keys(phifunction).e;
            d = generate_keys(phifunction).d;
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