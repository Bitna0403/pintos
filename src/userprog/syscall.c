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

  // Get the syscall number from the stack
  int syscall_num = *(int *)f->esp;

  switch (syscall_num) {
  
  case SYS_REMOVE:
    // Print current syscall number
    printf("Syscall_handler() - %d!\n", syscall_num);
    filesys_remove(*(char **)(f->esp + 4));
    printf(*(char **)(f->esp + 4));
    break;

  case SYS_EXEC:
    // Print current syscall number
    printf("Syscall_handler() - %d!\n", syscall_num);
    printf("SYS_CALL : EXEC \n");
    exec(*(char **)(f->esp + 4));
    break;

  case SYS_CREATE:
    // Print current syscall number
    printf("Syscall_handler() - %d!\n", syscall_num);
    create(*(int *)(f->esp + 4), (unsigned)*(int *)(f->esp + 8));
    break;

  default:
    thread_exit();
  }
}


tid_t exec(const char *cmd_line) {
  // showing the arg/process in the command line
  printf(" \ncmd_line : '%s'\n", cmd_line);
  // executing whatever in cmd_line then return to the process id
  tid_t pid = process_execute(cmd_line);
  return pid;
}

bool create(const char *file, unsigned initial_size) {
  // This creates a new file but doesn't open it
  printf("File named '%s' created\n", file);
  return filesys_create(file, initial_size);
}