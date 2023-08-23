#include "loader.h"

Elf32_Ehdr *ehdr;
Elf32_Phdr *phdr;
int fd;

/*
 * release memory and other cleanups
 */
void loader_cleanup() {
  free (ehdr);
  free (phdr);
}

/*
 * Load and run the ELF executable file
 */
void load_and_run_elf(char** exe) {
  fd = open(exe[1], O_RDONLY);
  ehdr = (Elf32_Ehdr*)malloc(sizeof(Elf32_Ehdr));
  phdr = (Elf32_Phdr*)malloc(sizeof(Elf32_Phdr));

  if (fd==-1){
    printf("ERROR IN OPENING THE ELF FILE\n");
    return;
  }

  // 1. Load entire binary content into the memory from the ELF file.
  if (read(fd, ehdr, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr)) {
        printf("ERROR IN READING ELF HEADER");
        free(ehdr);
        close(fd);
        return;
    }

  lseek(fd,ehdr->e_phoff,SEEK_SET);
  read(fd,phdr,sizeof(Elf32_Phdr));
  

  // 2. Iterate through the PHDR table and find the section of PT_LOAD 
  //    type that contains the address of the entrypoint method in fib.c
  for (int i = 0; i < ehdr->e_phnum; ++i) {
        
    if (phdr->p_type == PT_LOAD && phdr->p_vaddr <= ehdr->e_entry && ehdr->e_entry < (phdr->p_vaddr + phdr->p_memsz)) {
        break;
    }
    lseek(fd, ehdr->e_phoff + i * sizeof(Elf32_Phdr), SEEK_SET);
    read(fd,phdr,sizeof(Elf32_Phdr));
  }

  // 3. Allocate memory of the size "p_memsz" using mmap function 
  //    and then copy the segment content
  void* virtual_mem = mmap((void*) phdr->p_vaddr,phdr->p_memsz,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_PRIVATE|MAP_FIXED,fd,phdr->p_offset);   
  // if (segment_addr == MAP_FAILED) {
  //   perror("ERROR IN MAPPING SEGMENT");
  //   free(ehdr);
  //   close(fd);
  //   return;
  // }

  // 4. Navigate to the entrypoint address into the segment loaded in the memory in above step
  int (*_start)() = (int(*)())(ehdr->e_entry); 
  // 5. Typecast the address to that of function pointer matching "_start" method in fib.c.
  // 6. Call the "_start" method and print the value returned from the "_start"
  _start();
  int result = _start();
  printf("User _start return value = %d\n",result);
}