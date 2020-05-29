/****************************************************************************************
*  Lex.c
*  Client for Dictionary ADT
*  Pierson Bian
*  CSE101 Spring 2020
*  PA5
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dictionary.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   char* token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   Dictionary result = newDictionary(0);
   static char tokenList[194434][MAX_LEN];
   while( fgets(line, MAX_LEN, in) != NULL)  {
      token = '\0';
      tokenList[count][0] = '\0';
      token = strtok(line, "\n");
      strcat(token, "\0");
      if (strcmp(line, "\n") == 0){
         insert(result, "", count);
      }
      else {
         strcat(tokenList[count], token);
         insert(result, tokenList[count], count);
      }
      count++;
      token = strtok(NULL, "\n");
   }

   printDictionary(out, result);

   freeDictionary(&result);

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}