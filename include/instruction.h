#include <stdint.h>

typedef enum Opcode : uint8_t {
  OP_ADD,
  OP_SUB,
  OP_DOUBLE,
  OP_HALVE,
  OP_SLEEP,
  OP_COMMIT,
  OP_FLUSH,
  OP_HALT
} Opcode;

typedef struct Instruction {
  Opcode opcode;
  union {
    int8_t val;
    uint8_t time;
  };
} Instruction;
