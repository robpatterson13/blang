#include "buf.h"

void make_iter(struct buf_iter *i, const char *buf, int length)
{
	i->idx = 0;
	i->length = length;
	memcpy(i->buf, buf, length);
}

void make_iter_from(struct buf_with_idx *old, struct buf_iter *new)
{
	new->idx = 0;
	new->length = old->idx;
	memcpy(new->buf, old->buf, old->idx);
}

bool buf_full(struct buf_with_idx *buf)
{
	return buf->idx == MSG_BUF_SIZE;
}

bool buf_empty(struct buf_with_idx *buf)
{
	return buf->idx == 0;
}

bool push_char(struct buf_with_idx *buf, const char c)
{
	if (buf_full(buf))
		return false;

	buf->buf[buf->idx++] = c;
	return true;
}

void clear_buf(struct buf_with_idx *buf)
{
	memset(buf->buf, 0, MSG_BUF_SIZE);
	buf->idx = 0;
}

char peek_char(struct buf_iter *buf)
{
	return buf->buf[buf->idx];
}

void burn_char(struct buf_iter *buf)
{
	buf->idx++;
}

char next_char(struct buf_iter *buf)
{
	if (buf->idx == MSG_BUF_SIZE)
		return 0;

	return buf->buf[buf->idx++];
}
