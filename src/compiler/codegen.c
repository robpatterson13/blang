#include "instruction.h"

#include <stddef.h>
#include <stdio.h>

#define BUF_SIZE 4096

static void add_to(char *buf, const char *word, size_t *off, FILE *file)
{
	size_t word_len = strlen(word);
	if (word_len > BUF_SIZE - *off - 1) {
		buf[*off] = '\0';
		fprintf(file, "%s", buf);
		*off = 0;
	}

	char *nb = stpcpy(&buf[*off], word);
	*nb = ' ';
	*off += word_len + 1;
}

int emit(IList *list, const char *filename)
{
	FILE *file = fopen(filename, "w+");
	if (file == NULL)
		return -1;

	char buf[BUF_SIZE];
	size_t off = 0;
	for (int i = 0; i < list->length; i++) {
		switch (list->insts[i]) {
		case OP_ADD1:
			add_to(buf, ADD1_WORD, &off, file);
      break;

		case OP_ADD5:
			add_to(buf, ADD5_WORD, &off, file);
      break;

		case OP_ADD10:
			add_to(buf, ADD10_WORD, &off, file);
      break;

		case OP_SUB1:
			add_to(buf, SUB1_WORD, &off, file);
      break;

		case OP_SUB5:
			add_to(buf, SUB5_WORD, &off, file);
      break;

		case OP_SUB10:
			add_to(buf, SUB10_WORD, &off, file);
      break;

		case OP_COMMIT:
			add_to(buf, COMMIT_WORD, &off, file);
      break;

		case OP_FLUSH:
			add_to(buf, FLUSH_WORD, &off, file);
      break;

		case OP_SLEEP:
			add_to(buf, SLEEP_WORD, &off, file);
      break;

		case OP_HALT:
			add_to(buf, HALT_WORD, &off, file);
      break;
		}
	}

	buf[off] = '\0';
	fprintf(file, "%s", buf);

	fclose(file);
	return 0;
}
