#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PAGE_SIZE 4096         
#define MEMORY_SIZE (256 * 1024) 
#define NUM_FRAMES (MEMORY_SIZE / PAGE_SIZE) 

typedef struct {
    int frame_number;
    bool valid;
} PageTableEntry;

char physical_memory[MEMORY_SIZE];

PageTableEntry page_table[NUM_FRAMES];

void initialize_page_table() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        page_table[i].valid = false;
        page_table[i].frame_number = -1;
    }
}

void load_page(int page_number) {
    if (!page_table[page_number].valid) {
        page_table[page_number].frame_number = page_number;
        page_table[page_number].valid = true;
        printf("Page %d loaded into frame %d.\n", page_number, page_number);
    }
}

int translate_address(int logical_address) {
    int page_number = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE;

    if (page_number >= NUM_FRAMES) {
        printf("Invalid logical address: %d (Page number out of range)\n", logical_address);
        return -1;
    }

    if (!page_table[page_number].valid) {
        load_page(page_number);
    }

    int frame_number = page_table[page_number].frame_number;
    int physical_address = (frame_number * PAGE_SIZE) + offset;

    return physical_address;
}

void access_memory(int logical_address) {
    int physical_address = translate_address(logical_address);
    if (physical_address != -1) {
        printf("Logical address %d -> Physical address %d\n", logical_address, physical_address);
        physical_memory[physical_address] = 'A'; // Simulate memory access
        printf("Value at physical address %d: %c\n", physical_address, physical_memory[physical_address]);
    }
}

int main() {
    initialize_page_table();
    printf("\nSimulating memory access:\n");
    access_memory(0);              
    access_memory(4100);           
    access_memory(8192);           
    access_memory(65536);          
    access_memory(262144);         

    return 0;
}