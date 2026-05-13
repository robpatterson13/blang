#include <stdlib.h>
#include <string.h>

#include "instruction.h"

#define INSTRUCTION_LIST_INIT_CAPACITY 256
#define INSTRUCTION_LIST_INCREASE_FACTOR 1.5

bool init_instructions(IList *i)
{
	i->insts = (Instruction *)malloc(sizeof(Instruction) *
					 INSTRUCTION_LIST_INIT_CAPACITY);
	if (i->insts == NULL)
		return false;

	i->capacity = INSTRUCTION_LIST_INIT_CAPACITY;
	i->length = 0;
	return true;
}

void deinit_instructions(IList *i)
{
	if (i->insts)
		free(i->insts);

	i->capacity = 0;
	i->length = 0;
	i->insts = NULL;
}

static inline bool _at_max(IList *i)
{
	return i->capacity == i->length;
}

static inline bool _realloc(IList *i)
{
	if (i->insts == NULL)
		return false;

	int new_capacity =
		(int)(i->capacity * INSTRUCTION_LIST_INCREASE_FACTOR);
	int new_size = sizeof(Instruction) * new_capacity;
	Instruction *new_list = (Instruction *)malloc(new_size);
	if (new_list == NULL)
		return false;

	memcpy(new_list, i->insts, sizeof(Instruction) * i->length);

	i->capacity = new_capacity;
	free(i->insts);
	i->insts = new_list;
	return true;
}

bool push_instruction(IList *is, Instruction i)
{
	if (_at_max(is)) {
		bool did_realloc = _realloc(is);
		if (!did_realloc)
			return false;
	}

	is->insts[is->length++] = i;
	return true;
}
