# OS
Assignment
We have made a simple loader under some  basic assumptions. These assumptions are 1. Architecture is of 32 bit, and the ony executable type section present in the program header table is of the type "PT_LOAD". 
There is a test file, fib.c for checking the implementation of the loader.
The loader takes in input as the elf file of the testcase fib.c , which is fib.elf(the executable) and then first stores it in the heap memory by the means of open and read system calls. Then, it checks the entry inside the program header table which is of the type PT_LOAD and contains the entry_point address as mentioned in the ELF Header file. To check whether the segment contains the entry_point address we have used pointer based comparision. We compared the entry_point address with the current's pointer  p_vaddr and current pointer p_vaddr + {size_of_that_segment}. Then we copied that segment which contained the entry_point address to the memory using mmap function.
Then finally, we typecasted the entry_point address to a function pointer to run the test program(fib.c). 
