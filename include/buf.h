#include <stdint.h>
#include <string.h>

#define MSG_BUF_SIZE 256

// stupid little buffer with its own index
struct buf_with_idx {
	int idx;
	char buf[MSG_BUF_SIZE];
};

#define DEFINE_MSG_BUF(name) struct buf_with_idx name = { 0 }

static inline bool buf_full(struct buf_with_idx *buf)
{
	return buf->idx == MSG_BUF_SIZE;
}

static inline bool buf_empty(struct buf_with_idx *buf)
{
	return buf->idx == 0;
}

static inline bool push_char(struct buf_with_idx *buf, const char c)
{
	if (buf_full(buf))
		return false;

	buf->buf[buf->idx++] = c;
	return true;
}

static inline char peek_char(struct buf_with_idx *buf)
{
	return buf->buf[buf->idx];
}

static inline void burn_char(struct buf_with_idx *buf)
{
  buf->idx++; 
}

static inline char next_char(struct buf_with_idx *buf)
{
	return buf->buf[buf->idx++];
}

static inline void clear_buf(struct buf_with_idx *buf)
{
	memset(buf->buf, 0, MSG_BUF_SIZE);
	buf->idx = 0;
}
