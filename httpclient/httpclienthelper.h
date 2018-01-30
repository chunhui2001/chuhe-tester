#ifndef httpclienthelper_h__
#define httpclienthelper_h__

struct string {
  char *ptr;
  size_t len;
};

extern void init_string (struct string *s);
extern size_t curl_completed (void *ptr, size_t size, size_t nmemb, struct string *s);
extern void foo(void);

#endif // httpclienthelper_h__
