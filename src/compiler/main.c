#include <stdio.h>

#include "compiler.h"

// this will just be the number of char but I stole it from man...
// because
#define NITEMS(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(int argc, char **argv)
{
	if (argc > 3 || argc < 2) {
		fprintf(stderr, "Usage: blangc <input> [output]\n");
		return -1;
	}

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		fprintf(stderr, "blangc: file \"%s\" could not be opened\n",
			argv[1]);
		return -1;
	}

	int result = 0;
	IList list;
	if (!init_instructions(&list)) {
		fprintf(stderr,
			"blangc: unable to create instruction list (internal compiler error)\n");
		result = -1;
		goto close_file;
	}

	DEFINE_MSG_BUF(buf);
	size_t bytes_read =
		fread(buf.buf, sizeof(*buf.buf), sizeof(buf.buf), file);
	while (bytes_read > 0) {
		result = parse(&buf, &list);
		if (result < 0) {
			fprintf(stderr,
				"blangc: unable to parse input (internal compiler error)\n");
			goto deinit_instr;
		}
		bytes_read =
			fread(buf.buf, sizeof(*buf.buf), sizeof(buf.buf), file);
	}

	bool did_push = push_instruction(&list, OP_HALT);
	if (!did_push) {
		fprintf(stderr,
			"blangc: unable to add to instruction list (internal compiler error)\n");
		result = -1;
		goto deinit_instr;
	}

	if (argc > 2) {
		result = emit(&list, argv[2]);
	} else {
		result = emit(&list, "a.out");
	}

	if (result < 0) {
		fprintf(stderr,
			"blangc: unable to emit compiler output (internal compiler error)\n");
	}

deinit_instr:
	deinit_instructions(&list);

close_file:
	fclose(file);

	return result;
}
