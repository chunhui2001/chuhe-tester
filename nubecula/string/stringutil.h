#ifndef stringutil_h__
#define stringutil_h__

struct string {
  char *ptr;
  size_t len;
};

extern void init_string (struct string *s);

/**
 * @brief string_lower 将传入的字符转成大写并存储到 dest 中
 * @param str
 * @param dest
 */
extern void string_upper(char* str, char* dest);

/**
 * @brief string_toupper 将传入的字符转成大写
 * @param str
 */
extern char* string_toupper(char str[]);

#endif //
