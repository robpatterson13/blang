#include <stdint.h>

#include "opcode_mappings.h"

typedef enum Instruction : uint8_t {
	OP_ADD1,
	OP_ADD5,
	OP_ADD10,
	OP_SUB1,
	OP_SUB5,
	OP_SUB10,
	OP_SLEEP,
	OP_COMMIT,
	OP_FLUSH,
	OP_HALT
} Instruction;

typedef struct IList {
	int capacity;
	int length;
	Instruction *insts;
} IList;

bool init_instructions(IList *i);
void deinit_instructions(IList *i);
bool push_instruction(IList *is, Instruction i);
