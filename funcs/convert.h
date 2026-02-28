#ifndef convert_h
#define convert_h

void unsigned_to_str(unsigned long long num, char *str, unsigned char basis);
void int_to_str(long long num, char *str);
void to_oct(unsigned long long num, char *str);
void to_dec(unsigned long long num, char *str);
void to_hex(char *dest, unsigned long long value, unsigned short upper);
void reverse(char *str, int len);

#endif  // convert_h
