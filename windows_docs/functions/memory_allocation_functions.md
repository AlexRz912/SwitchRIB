# Windows Memory Allocation Methods Comparison

**Source:** [Microsoft Docs - Comparing Memory Allocation Methods](https://learn.microsoft.com/en-us/windows/win32/memory/comparing-memory-allocation-methods)

## Overview

Windows provides multiple APIs for memory allocation, each with distinct characteristics and performance implications.

## GlobalAlloc and LocalAlloc

- **Wrappers**: Built on top of HeapAlloc with additional overhead
- **Return Type**: Return handles rather than direct pointers
- **Memory Mobility**: Memory location can be moved in physical memory
- **Exception Handling**: Cannot raise exceptions (unlike HeapAlloc)

## HeapAlloc

- **Return Type**: Returns direct memory addresses (no handles)
- **Memory Mobility**: Fixed memory location that cannot be moved
- **Exception Handling**: Can raise exceptions on allocation failure

## VirtualAlloc

- **Granularity**: Operates at page-level granularity for finer control
- **Memory Usage**: Higher overhead due to page allocation
- **Use Cases**: Best for large memory blocks or when page-level control is needed

## Critical Requirement

⚠️ **Always use the corresponding free function for the allocation API used** (GlobalFree, LocalFree, HeapFree, or VirtualFree)
