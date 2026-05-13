#include "instruction.h"
#include "buf.h"

int parse(struct buf_with_idx *buf, IList *list);
int emit(IList *list, const char *filename);
