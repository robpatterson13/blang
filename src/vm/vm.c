#include <stdio.h>
#include <unistd.h>

#include "buf.h"
#include "instruction.h"

#define SLEEP_TIME 1
#define PRINT_LAG 20000

static inline void flush(struct buf_with_idx *buf);
static inline void flush_then_push(struct buf_with_idx *buf, const char c);

uint8_t interpret(Instruction *insts)
{
	static void *dispatch_table[] = { &&do_add1,  &&do_add5,   &&do_add10,
					  &&do_sub1,  &&do_sub5,   &&do_sub10,
					  &&do_sleep, &&do_commit, &&do_flush,
					  &&do_halt };

#define DISPATCH() goto *dispatch_table[insts[pc++]]
#define INST insts[pc]

	uint16_t pc = 0;
	DEFINE_MSG_BUF(buf);
	char curr = 0;

	// clang-format off
  DISPATCH();
	while (true) {
    do_add1:
      curr += 1;
      DISPATCH();

    do_add5:
      curr += 5;
      DISPATCH();

    do_add10:
      curr += 10;
      DISPATCH();

    do_sub1:
      curr -= 1;
      DISPATCH();

    do_sub5:
      curr -= 5;
      DISPATCH();

    do_sub10:
      curr -= 10;
      DISPATCH();

    do_sleep:
      sleep(SLEEP_TIME);
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
      if (!buf_empty(&buf))
        flush(&buf);

      return 0;
	}
	// clang-format on
}

static inline void flush(struct buf_with_idx *buf)
{
  make_iter(buf);
  char c = next_char(buf);
  while (c) {
    printf("%c", c);
    fflush(stdout);
    usleep(PRINT_LAG);
    c = next_char(buf);
  }

	clear_buf(buf);
}

static inline void flush_then_push(struct buf_with_idx *buf, const char c)
{
	flush(buf);
	push_char(buf, c);
}
