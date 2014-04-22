#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>

#include <openssl/md5.h>

#define THREADS 4
#define MAX_COMBO 100000000

const char* chars="0123456789";

// tests if a hash matches a candidate password
int test(const char* passhash, const char* passcandidate) {
    unsigned char digest[MD5_DIGEST_LENGTH];
    
    MD5((unsigned char*)passcandidate, strlen(passcandidate), digest);
    
    char mdString[34];
    mdString[33]='\0';
    for(int i=0; i<16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned char)digest[i]);
    }
    return strncmp(passhash, mdString, strlen(passhash));
}

// maps a PIN to a string
void genpass(long passnum, char* passbuff) {
    passbuff[8]='\0';
    int charidx;
    int symcount=strlen(chars);
    for(int i=7; i>=0; i--) {
        charidx=passnum%symcount;
        passnum=passnum/symcount;
        passbuff[i]=chars[charidx];
    }
}

int main(int argc, char** argv) {
    omp_set_num_threads(THREADS);
    int threadNum=0;
    int threadWork = MAX_COMBO/THREADS;

    if(argc != 2) {
        printf("Usage: %s <password hash>\n",argv[0]);
        return 1;
    }
    char passguess[9];
    char passmatch[9];
    long currpass=0;
    int notfinished=1;
    int notfound=1;
    #pragma omp parallel private(threadNum) private(notfound) private(currpass) private(passguess)
    {
        threadNum=omp_get_thread_num();
        currpass = threadNum*threadWork;
        while(notfinished && notfound && currpass < (threadNum+1)*threadWork) {
            genpass(currpass,passguess);
            notfound=test(argv[1], passguess);
            currpass++;
        }
        if(notfound == 0) {
            notfinished = 0;
            memcpy(passmatch,passguess,9);
        }
    }
    printf("found: %s\n",passmatch);
    return 0;
}
