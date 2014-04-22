#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>

#include <openssl/md5.h>

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

/*helper function to call test and genpass to cilk spawn*/
void gentest(int *notfound, int currpass, char* arg) {
    char passmatch[9];
    int found;
    genpass(currpass,passmatch);
    found=test(arg, passmatch);
    if(found==0) {
        *notfound=0;
        printf("found: %s\n",passmatch);
    }
    //printf("currpss: %i\n",currpass);
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: %s <password hash>\n",argv[0]);
        return 1;
    }
    long currpass=0;
    int notfound=1;
    while(notfound) {
        /* 4 threads, each running a test per loop
         * easier to keep track of when a thread finds code 
         * allowing early termination
         * probably better performance if work was divided into chunks
         */
        cilk_spawn(gentest(&notfound,currpass,argv[1]));
        cilk_spawn(gentest(&notfound,currpass+1,argv[1]));
        cilk_spawn(gentest(&notfound,currpass+2,argv[1]));
        cilk_spawn(gentest(&notfound,currpass+3,argv[1]));
        //cilk_sync;
        //printf("notfound: %i\n",notfound);
        currpass+=4;
    }
    return 0;
}
