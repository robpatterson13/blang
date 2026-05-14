#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "buf.h"
#include "instruction.h"

#define PUSH_OR_RETURN_FAILURE(list, inst)         \
	do {                                       \
		if (!push_instruction(list, inst)) \
			return -1;                 \
	} while (0)

typedef enum Mul { M_ONE, M_FIVE, M_TEN } Mul;

static inline Instruction parity_op(int diff, Mul mul)
{
	switch (mul) {
	case M_ONE:
		return diff > 0 ? OP_ADD1 : OP_SUB1;

	case M_FIVE:
		return diff > 0 ? OP_ADD5 : OP_SUB5;

	case M_TEN:
		return diff > 0 ? OP_ADD10 : OP_SUB10;
	}
}

static inline int push_ops_for_char(const char last, const char curr,
				    IList *list)
{
	int diff = abs(curr - last);
	int parity = curr < last ? -1 : 1;
	int tens_inside = diff / 10;
	if (tens_inside) {
		for (int i = 0; i < tens_inside; i++)
			PUSH_OR_RETURN_FAILURE(list, parity_op(parity, M_TEN));
	}

	diff %= 10;
	int fives_inside = diff / 5;
	if (fives_inside) {
		for (int i = 0; i < fives_inside; i++)
			PUSH_OR_RETURN_FAILURE(list, parity_op(parity, M_FIVE));
	}

	diff %= 5;
	for (int i = 0; i < abs(diff); i++)
		PUSH_OR_RETURN_FAILURE(list, parity_op(parity, M_ONE));

	return 0;
}

int parse(struct buf_iter *buf, IList *list)
{
	char last = 0;
	char curr = next_char(buf);
	while (curr) {
		if (curr == ';') {
			if (peek_char(buf) == ';') {
				PUSH_OR_RETURN_FAILURE(list, OP_SLEEP);
				burn_char(buf);
				goto inc;
			} else if (peek_char(buf) == '>') {
				PUSH_OR_RETURN_FAILURE(list, OP_FLUSH);
				burn_char(buf);
				goto inc;
			}
		}

		if (push_ops_for_char(last, curr, list) != 0)
			return -1;

		PUSH_OR_RETURN_FAILURE(list, OP_COMMIT);

inc:
		last = curr;
		curr = next_char(buf);
	}

	PUSH_OR_RETURN_FAILURE(list, OP_FLUSH);
	PUSH_OR_RETURN_FAILURE(list, OP_HALT);

	return 0;
}
