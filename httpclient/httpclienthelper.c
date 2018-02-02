#include <stdio.h>			// printf
#include <stdlib.h> 		// EXIT_FAILURE, exit, realloc
#include <string.h> 		// memcpy

#include "httpclienthelper.h"

void foo(void) {
	printf("foo");
}


size_t curl_completed(void *ptr, size_t size, size_t nmemb, struct string *s) {
	size_t new_len = s->len + size*nmemb;
    s->ptr = realloc(s->ptr, new_len+1);

    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }

    memcpy(s->ptr+s->len, ptr, size*nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size*nmemb;

}
