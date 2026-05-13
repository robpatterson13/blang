#include <_static_assert.h>
#include <string.h>

#define MAX_WORD_SIZE 32

// update these for local setup
#define ADD1_WORD "add1"
#define ADD5_WORD "add5"
#define ADD10_WORD "add10"
#define SUB1_WORD "sub1"
#define SUB5_WORD "sub5"
#define SUB10_WORD "sub10"
#define SLEEP_WORD "sleep"
#define COMMIT_WORD "commit"
#define FLUSH_WORD "flush"
#define HALT_WORD "halt"

#define CHECK_LEN(str) \
  static_assert(strlen(str) <= MAX_WORD_SIZE, "string for " #str " is too long")

CHECK_LEN(ADD1_WORD);
CHECK_LEN(ADD5_WORD);
CHECK_LEN(ADD10_WORD);
CHECK_LEN(SUB1_WORD);
CHECK_LEN(SUB5_WORD);
CHECK_LEN(SUB10_WORD);
CHECK_LEN(SLEEP_WORD);
CHECK_LEN(COMMIT_WORD);
CHECK_LEN(FLUSH_WORD);
CHECK_LEN(HALT_WORD);
