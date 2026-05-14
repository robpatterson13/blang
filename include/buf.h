#include <stdint.h>
#include <string.h>

#define MSG_BUF_SIZE 256

#define DEFINE_MSG_BUF(name) struct buf_with_idx name = { 0 }

// stupid little buffer with its own index
struct buf_with_idx {
	int idx;
	char buf[MSG_BUF_SIZE];
};

bool buf_full(struct buf_with_idx *buf);
bool buf_empty(struct buf_with_idx *buf);
bool push_char(struct buf_with_idx *buf, const char c);
void clear_buf(struct buf_with_idx *buf);

struct buf_iter {
	int idx;
	char buf[MSG_BUF_SIZE];
	int length;
};

void make_iter(struct buf_iter *i, const char *buf, int length);
void make_iter_from(struct buf_with_idx *old, struct buf_iter *new);
char peek_char(struct buf_iter *buf);
void burn_char(struct buf_iter *buf);
char next_char(struct buf_iter *buf);
