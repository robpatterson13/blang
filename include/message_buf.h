#include <stdint.h>
#include <string.h>

#define MSG_BUF_SIZE 256

// stupid little buffer with its own index
struct message_buf {
  int idx;
  char buf[MSG_BUF_SIZE];
};

#define DEFINE_MSG_BUF(name) struct message_buf name = {0}

static inline bool msg_full(struct message_buf *buf) {
  return buf->idx == MSG_BUF_SIZE;
}

static inline bool msg_empty(struct message_buf *buf) { return buf->idx == 0; }

static inline bool push_char(struct message_buf *buf, const char c) {
  if (msg_full(buf))
    return false;

  buf->buf[buf->idx++] = c;
  return true;
}

static inline void clear_buf(struct message_buf *buf) {
  memset(buf->buf, 0, MSG_BUF_SIZE);
  buf->idx = 0;
}
