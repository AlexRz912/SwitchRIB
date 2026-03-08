# Windows Memory Management

**Source:** [Microsoft Docs - About Keyboard Input](https://learn.microsoft.com/en-us/windows/win32/memory/about-memory-management)


Each process on 32-bit Microsoft Windows has its own virtual address space that enables addressing up to 4 gigabytes of memory. Each process on 64-bit Windows has a virtual address space of 8 terabytes. 

All threads of a process can access its virtual address space. However, threads cannot access memory that belongs to another process, which protects a process from being corrupted by another process.

## Virtual Address Space (Memory Management)

A virtual address does not represent the actual physical location of an object in memory; instead, the system maintains a page table for each process, which is an internal data structure used to translate virtual addresses into their corresponding physical addresses. Each time a thread references an address, the system translates the virtual address to a physical address.

The virtual address space for 32-bit Windows is 4 gigabytes (GB) in size and divided into two partitions: one for use by the process and the other reserved for use by the system.

## Default Virtual Address Space for 32-bit Windows

Memory range	                                    Usage
Low 2GB (0x00000000 through 0x7FFFFFFF)	            Used by the process.
High 2GB (0x80000000 through 0xFFFFFFFF)	        Used by the system.

## Virtual Address Space for 32-bit Windows with 4GT

Enabling 4-GigaBytes tuning

Memory range	                                    Usage
Low 3GB (0x00000000 through 0xBFFFFFFF)	            Used by the process.
High 1GB (0xC0000000 through 0xFFFFFFFF)	        Used by the system.

After 4GT is enabled, a process that has the IMAGE_FILE_LARGE_ADDRESS_AWARE flag set in its image header will have access to the additional 1 GB of memory above the low 2 GB.

## Adjusting the Virtual Address Space for 32-bit Windows

You can use the following command to set a boot entry option that configures the size of the partition that is available for use by the process to a value between 2048 (2 GB) and 3072 (3 GB):

BCDEdit /set increaseuserva Megabytes

After the boot entry option is set, the memory range for each partition is as follows.

Memory range	                                    Usage
Low (0x00000000 through Megabytes)	                Used by the process.
High (Megabytes+1 through 0xFFFFFFFF)	            Used by the system.

## Virtual Address Space (Programming Guide for 64-bit Windows)

- A 2 GB address space is sufficient.
- The code has many pointer truncation warnings.
- Pointers and integers are freely mixed.
- The code has polymorphism using 32-bit data types.

All pointers are still 64-bit pointers, but the system ensures that every memory allocation occurs below the 2 GB limit, so that if the application truncates a pointer, no significant data is lost. Pointers can be truncated to 32-bit values, then extended to 64-bit values by either sign extension or zero extension.

To specify this memory limitation, use the /LARGEADDRESSAWARE:NO linker option. Note that /LARGEADDRESSAWARE:NO is ignored for an ARM64 binary. However, be aware that problems can occur when using this option. If you build a DLL that uses this option and the DLL is called by an application that does not use this option, the DLL could truncate a 64-bit pointer whose upper 32 bits are significant. This can cause application failure without any warning.


## Virtual Address Space and Physical Storage

The maximum amount of physical memory supported by Microsoft Windows ranges from 2 GB to 24 TB, depending on the version of Windows. For more information, see Memory Limits for Windows Releases. The virtual address space of each process can be smaller or larger than the total physical memory available on the computer. The subset of the virtual address space of a process that resides in physical memory is known as the working set. If the threads of a process attempt to use more physical memory than is currently available, the system pages some of the memory contents to disk. The total amount of virtual address space available to a process is limited by physical memory and the free space on disk available for the paging file.

Physical storage and the virtual address space of each process are organized into pages, units of memory, whose size depends on the host computer. For example, on x86 computers the host page size is 4 kilobytes.

To maximize its flexibility in managing memory, the system can move pages of physical memory to and from a paging file on disk. When a page is moved in physical memory, the system updates the page maps of the affected processes. When the system needs space in physical memory, it moves the least recently used pages of physical memory to the paging file. Manipulation of physical memory by the system is completely transparent to applications, which operate only in their virtual address spaces.

## Working Set

The working set of a process is the set of pages in the virtual address space of the process that are currently resident in physical memory. The working set contains only pageable memory allocations; nonpageable memory allocations such as Address Windowing Extensions (AWE) or large page allocations are not included in the working set.

Page fault :

A Page fault happens when a process tries to reference memory in working set, and it is not yet in the working set

Doesn't happen with non pageable data such as address windowing extension or large page allocation

Can be resolve with page fault handler
Two types of page fault
Soft page fault :
 - Can happen if page is in working set of other processes, already resident in memory
 - In transition from other processes's working set, not yet repurposed, or already resident as 
 a result of memory prefetch operation
 - (Demand zero fault)

Hard page fault :
 - reading process backing store : System paging file or memory mapped file created by process

