#include "loader.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

typedef int (*StartFunction)();

Elf32_Ehdr *ehdr;
int fd;

void loader_cleanup() {
    
}

void load_and_run_elf(char** exe_path) {
    fd = open(exe_path[1], O_RDONLY);
  
    if(fd == -1) {
        printf("ERROR IN OPENING THE ELF FILE\n");
        return;
    }

    off_t size_elf = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    void* elf_content = malloc(size_elf);
    int read_status = read(fd, elf_content, size_elf);
    if(read_status == -1) {
        printf("ERROR: NOT ABLE TO READ THE ELF_FILE\n");
        return;
    }
  
    ehdr = (Elf32_Ehdr*)elf_content;
    unsigned short tot_entries_phdr = ehdr->e_phnum;
    unsigned short size_one_entry = ehdr->e_phentsize;
    int i;
    int flg = 0;
    for(i = 0; i < tot_entries_phdr; i++) {
        Elf32_Phdr* curr_entry = (Elf32_Phdr*)((char*)ehdr + ehdr->e_phoff + i * size_one_entry);
        if(curr_entry->p_type == PT_LOAD && (curr_entry->p_vaddr<=(void*)ehdr->e_entry && (void*)ehdr->e_entry<= curr_entry->p_vaddr+curr_entry->p_memsz)) {
            void* virtual_mem = mmap((void*)curr_entry->p_vaddr, curr_entry->p_memsz,
                                     PROT_READ | PROT_WRITE | PROT_EXEC,
                                     MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);
          
            if(virtual_mem == MAP_FAILED) {
                printf("ERROR: NOT ABLE TO ALLOCATE MEMORY FOR THE PROGRAM HEADER SEGMENTS\n");
                return;
            }
          
            lseek(fd, (off_t)curr_entry->p_offset, SEEK_SET);
            int status = read(fd, virtual_mem, curr_entry->p_filesz);
            if(status == -1) {
                printf("ERROR: IN COPYING THE SEGMENTS CONTENT TO THE ELF_FILE\n");
                return;
            }
          
            if(curr_entry->p_filesz < curr_entry->p_memsz) {
                
                memset((void*)((char*)virtual_mem + curr_entry->p_filesz), 0,
                       curr_entry->p_memsz - curr_entry->p_filesz);
            }
          
            void* entry_point_address = (void*)((char*)virtual_mem + (ehdr->e_entry - curr_entry->p_vaddr));
            StartFunction _start = (StartFunction)entry_point_address;
            int result = _start();
            printf("User _start return value = %d\n", result);
          
            
            munmap(virtual_mem, curr_entry->p_memsz);
            free(elf_content);
        }
    }
}
