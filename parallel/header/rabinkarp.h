#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rabin_karp(char *pat, char *txt, int rank, int rest);

int rabin_karp(char *pat, char *txt, int rank, int rest){

  int M = strlen(pat);
  int N = strlen(txt);
  int i,j;
  int txt_hash = 0, pat_hash = 0, freq = 0;
  int h = 1;

    // h = pow(D,M-1) % Q
    for (i = 0; i < M - 1; i++)
      h = (h * D) % Q;

    // Computing the hash value of pattern and first window of the text
    for(i = 0; i < M; i++){
      pat_hash = (D * pat_hash + *(pat + i)) % Q;
      txt_hash = (D * txt_hash + *(txt + i)) % Q;
    }

    for(i = 0; i <= N - M; i++){
      // Check the hash values of current window of text and pattern
      // If the hash values match then only check for characters one by one
      if(pat_hash == txt_hash){
        // Check for characters one by one
        for(j = 0; j < M; j++){
          if(*(txt + i + j) != *(pat + j))
            break;
        }

        if(j == M){
          fflush(stdout);
          //fprintf(stdout,"\033[0;32m Pattern found at index %d\n\033[0m", rank == 0 ? i : i+(N-(M-1)+rest)-M+1+((rank-1)*(N-M+1)));
          printf("\033[0;32m Pattern found at index %d\n\033[0m", rank == 0 ? i : i+(N-(M-1)+rest)-M+1+((rank-1)*(N-M+1)));
          freq++;
        }
      }

      // Calculate hash value for next window of text:
      // remove leading digit, add trailing digit
      if(i < N - M){
        txt_hash = (D * (txt_hash - *(txt + i) * h) + *(txt + i + M)) % Q;

        //We might get negative value of txt_hash so we convert it to positive
        if(txt_hash < 0)
          txt_hash = txt_hash + Q;
      }
    }

  return freq;
}
