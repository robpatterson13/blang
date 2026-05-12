#include <stdio.h>
#include <unistd.h>

#include "message_buf.h"
#include "opcode.h"

static inline void flush(struct message_buf *buf);
static inline void flush_then_push(struct message_buf *buf, const char c);

uint8_t interpret(Instruction *insts) {
  static void *dispatch_table[] = {&&do_add,   &&do_sub,   &&do_double,
                                   &&do_halve, &&do_sleep, &&do_commit,
                                   &&do_flush, &&do_halt};

#define DISPATCH() goto *dispatch_table[insts[pc++].opcode]
#define INST insts[pc]

  uint16_t pc = 0;
  DEFINE_MSG_BUF(buf);
  char curr = 0;

  while (true) {
  do_add:
    curr += INST.val;
    DISPATCH();

  do_sub:
    curr -= INST.val;
    DISPATCH();

  do_double:
    curr <<= 1;
    DISPATCH();

  do_halve:
    curr >>= 1;
    DISPATCH();

  do_sleep:
    sleep(INST.time);
    DISPATCH();

  do_commit:
    bool did_push = push_char(&buf, curr);
    if (!did_push)
      flush_then_push(&buf, curr);

    DISPATCH();

  do_flush:
    flush(&buf);
    DISPATCH();

  do_halt:
    if (!msg_empty(&buf))
      flush(&buf);

    return 0;
  }
}

static inline void flush(struct message_buf *buf) {
  if (msg_full(buf)) {
    printf("%.*s", MSG_BUF_SIZE, buf->buf);
  } else {
    push_char(buf, '\0');
    printf("%s", buf->buf);
  }

  clear_buf(buf);
}

static inline void flush_then_push(struct message_buf *buf, const char c) {
  flush(buf);
  push_char(buf, c);
}
