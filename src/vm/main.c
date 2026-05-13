#include <stdio.h>

#include "vm.h"

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: blang <input>\n");
		return -1;
	}

	FILE *file = fopen(argv[1], "r");
	if (file == NULL) {
		fprintf(stderr, "blang: file \"%s\" could not be opened\n",
			argv[1]);
		return -1;
	}

	int result = 0;
	IList list;
	if (!init_instructions(&list)) {
		fprintf(stderr,
			"blang: unable to create instruction list (internal compiler error)\n");
		result = -1;
		goto close_file;
	}

	char buf[4096];
	size_t bytes_read = fread(buf, sizeof(*buf), sizeof(buf), file);
	while (bytes_read > 0) {
		result = parse(buf, &list);
		if (result < 0) {
			fprintf(stderr,
				"blang: unable to parse input (internal compiler error)\n");
			goto deinit_instr;
		}
		bytes_read = fread(buf, sizeof(*buf), sizeof(buf), file);
	}

	interpret(list.insts);

deinit_instr:
	deinit_instructions(&list);

close_file:
	fclose(file);

	return result;
}
