
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   int n, count=0;
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

   List result = newList();
   char tokenList[1000][MAX_LEN];
   while( fgets(line, MAX_LEN, in) != NULL)  {
      token = NULL;
      tokenList[count][0] = '\0';
      token = strtok(line, "\n");
      strcat(tokenList[count], token);

      if (count == 0){
         append(result, count);
      }
      else{
         //find the spot
         moveFront(result);
         while (index(result) >= 0 && strcmp(tokenList[count], tokenList[get(result)]) > 0){
            moveNext(result);
         }
         //are we at tail?
         if (index(result) < 0){
            append(result, count);
         }
         //insert normally
         else{
            insertBefore(result, count);
         }
      }
      count++;
      token = strtok(NULL, "\n");
   }

   for (moveFront(result); index(result) >= 0; moveNext(result)){
      fprintf(out, "%s\n", tokenList[get(result)]);
   }

   freeList(&result);

   /* close files */
   fclose(in);
   fclose(out);

   return(0);
}