#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stringutil.h"

void init_string (struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}


static char* upper_string(char s[]) {
   int c = 0;

   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }

   return s;

}


void string_upper(char* str, char* dest) {
    fprintf(stdout, "string upper: %s\n", str);
}

char* string_toupper(char* s) {

    return upper_string(s);

}

