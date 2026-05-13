#include <string.h>

#include "instruction.h"

int parse(char *buf, IList *insts)
{
	char *token = strtok(buf, " \n");
#define MATCHES(word) (strncmp(token, word, strlen(word)) == 0)

	int op = -1;
	while (token) {
		if (MATCHES(ADD1_WORD)) {
			op = OP_ADD1;

		} else if (MATCHES(ADD5_WORD)) {
			op = OP_ADD5;

		} else if (MATCHES(ADD10_WORD)) {
			op = OP_ADD10;

		} else if (MATCHES(SUB1_WORD)) {
			op = OP_SUB1;

		} else if (MATCHES(SUB5_WORD)) {
			op = OP_SUB5;

		} else if (MATCHES(SUB10_WORD)) {
			op = OP_SUB10;

		} else if (MATCHES(SLEEP_WORD)) {
			op = OP_SLEEP;

		} else if (MATCHES(COMMIT_WORD)) {
			op = OP_COMMIT;

		} else if (MATCHES(FLUSH_WORD)) {
			op = OP_FLUSH;

		} else if (MATCHES(HALT_WORD)) {
			op = OP_HALT;
		}

		if (op >= 0) {
			bool did_push = push_instruction(insts, op);
			if (!did_push)
				return -1;
		}
		op = -1;
		token = strtok(NULL, " \n");
	}

	return 0;
}
