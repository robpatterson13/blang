#include <stdint.h>

typedef enum Opcode : uint8_t {
  OP_PUSH,
  OP_POP,
  OP_ADD,
  OP_SUB,
  OP_DOUBLE,
  OP_HALF,
  OP_SLEEP
} Opcode;

typedef struct Instruction {
  Opcode opcode;
  union {
    int8_t val;
    uint8_t time;
  };
} Instruction;
