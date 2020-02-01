#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t getSize(char * str) {
  size_t ans = 0;
  if (str != 0) {
    while (str[ans] != '\0') {
      ans++;
    }
    return ans;
  }
  return 0;
}

void reverse(char * str) {
  //WRITE ME!
  if (str == 0) {
    return;
  }
  size_t size = getSize(str);
  char temp[size];
  strncpy(temp, str, size);
  for (size_t i = 0; i < size; i++) {
    str[i] = temp[size - 1 - i];
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be "
                "no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  //new tests
  //char * strx = {0};
  //size_t a = getSize(strx);
  //printf("%lu\n", a);

  return EXIT_SUCCESS;
}
