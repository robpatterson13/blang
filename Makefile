CC     := clang
CFLAGS := -std=c23 -Wall -Wextra -Wpedantic -I include
LDFLAGS :=

BUILD ?= debug
ifeq ($(BUILD),release)
  CFLAGS += -O2 -DNDEBUG
else
  CFLAGS += -g -O0 -DDEBUG
endif

COMPILER_SRCS := $(shell find src/compiler -name '*.c' 2>/dev/null)
COMPILER_OBJS := $(COMPILER_SRCS:src/%.c=bin/obj/%.o)

VM_SRCS := $(shell find src/vm -name '*.c' 2>/dev/null)
VM_OBJS := $(VM_SRCS:src/%.c=bin/obj/%.o)

DEPS := $(COMPILER_OBJS:.o=.d) $(VM_OBJS:.o=.d)

.PHONY: all clean format compile_commands

all: bin/blangc bin/blang

bin/blangc: $(COMPILER_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@

bin/blang: $(VM_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@

bin/obj/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

compile_commands:
	bear -- $(MAKE) all

format:
	clang-format -i $(shell find src include -name '*.c' -o -name '*.h' 2>/dev/null)

clean:
	rm -rf bin
