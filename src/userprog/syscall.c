#include "userprog/syscall.h"
#include "filesys/filesys.h"
#include "lib/kernel/list.h"
#include "threads/interrupt.h"
#include "threads/malloc.h"
#include "threads/thread.h"
#include "userprog/process.h"
#include <stdio.h>
#include <string.h>
#include <syscall-nr.h>

static void syscall_handler(struct intr_frame *);
bool create(const char *file, unsigned initial_size);
tid_t exec(const char *cmd_line);

void syscall_init(void) {
  intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void syscall_handler(struct intr_frame *f) {
  int syscall_num = *(int *)f->esp;
  switch (syscall_num) {

  case SYS_REMOVE:
    filesys_remove(*(char **)(f->esp + 4));
    break;

  case SYS_EXEC:
    process_execute(*(char **)(f->esp + 4));
    break;

  case SYS_CREATE:
    filesys_create(*(char**)(f->esp + 4), (unsigned)*(int *)(f->esp + 8));
    break;

  default:
    thread_exit();
  }
}
