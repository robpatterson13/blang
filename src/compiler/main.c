#include <stdio.h>

#include "compiler.h"

static size_t read_into_buf(struct buf_iter *buf, FILE *file)
{
	buf->idx = 0;
	size_t bytes_read =
		fread(buf->buf, sizeof(char), sizeof(buf->buf), file);
	buf->length = bytes_read;
	return bytes_read;
}

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

	struct buf_iter buf;
	size_t bytes_read = read_into_buf(&buf, file);
	while (bytes_read > 0) {
		result = parse(&buf, &list);
		if (result < 0) {
			fprintf(stderr,
				"blangc: unable to parse input (internal compiler error)\n");
			goto deinit_instr;
		}
		bytes_read = read_into_buf(&buf, file);
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
