#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define PAGE_SIZE 1024
#define NUM_PAGES 256
#define VIRTUAL_MEMORY_SIZE (NUM_PAGES * PAGE_SIZE)
#define NUM_FRAMES 128
#define PHYSICAL_MEMORY_SIZE (NUM_FRAMES * PAGE_SIZE)
#define TLB_SIZE 16

typedef struct {
    int frame_number;
    int valid;
    int modified;
    int referenced;
} PageTableEntry;

typedef struct {
    int virtual_page;
    int frame_number;
    int valid;
    int time_of_use; 
} TLBEntry;

int physical_memory[NUM_FRAMES][PAGE_SIZE];
PageTableEntry page_table[NUM_PAGES];
TLBEntry tlb[TLB_SIZE];
int tlb_index = 0;
int tlb_hits = 0, tlb_misses = 0, page_faults = 0;
int clock_time = 0;
int memory_accesses;
char tlb_policy[4];

void init_memory() {
    for (int i = 0; i < NUM_PAGES; i++) {
        page_table[i].valid = 0;
        page_table[i].modified = 0;
        page_table[i].referenced = 0;
        page_table[i].frame_number = -1;
    }
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].valid = 0;
    }
}

int extract_page_number(int virtual_address) {
    return (virtual_address / PAGE_SIZE) % NUM_PAGES;
}

int extract_offset(int virtual_address) {
    return virtual_address % PAGE_SIZE;
}

int check_tlb(int page_number) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].virtual_page == page_number) {
            tlb_hits++;
            tlb[i].time_of_use = clock_time++;
            return tlb[i].frame_number;
        }
    }
    tlb_misses++;
    return -1;
}

void update_tlb(int page_number, int frame_number) {
    int replace_index = 0;
    if (strcmp(tlb_policy, "LRU") == 0) {
        int oldest_time = tlb[0].time_of_use;
        for (int i = 1; i < TLB_SIZE; i++) {
            if (tlb[i].time_of_use < oldest_time) {
                oldest_time = tlb[i].time_of_use;
                replace_index = i;
            }
        }
    } else {
        replace_index = tlb_index % TLB_SIZE;
        tlb_index++;
    }
    
    tlb[replace_index].virtual_page = page_number;
    tlb[replace_index].frame_number = frame_number;
    tlb[replace_index].valid = 1;
    tlb[replace_index].time_of_use = clock_time++;
}

int translate_address(int virtual_address) {
    int page_number = extract_page_number(virtual_address);
    int offset = extract_offset(virtual_address);
    int frame_number = check_tlb(page_number);

    if (frame_number == -1) {
        if (!page_table[page_number].valid) {
            page_faults++;
            page_table[page_number].frame_number = page_number % NUM_FRAMES;
            page_table[page_number].valid = 1;
        }
        frame_number = page_table[page_number].frame_number;
        update_tlb(page_number, frame_number);
    }
    return (frame_number * PAGE_SIZE) + offset;
}

void generate_memory_accesses() {
    srand(42); // Fixed seed for consistent results
    for (int i = 0; i < memory_accesses; i++) {
        int access_type = rand() % 3;
        int virtual_address;
        if (access_type == 0) {
            virtual_address = i * PAGE_SIZE % VIRTUAL_MEMORY_SIZE;
        } else if (access_type == 1) {
            virtual_address = rand() % VIRTUAL_MEMORY_SIZE;
        } else {
            virtual_address = (rand() % (PAGE_SIZE * 10)) % VIRTUAL_MEMORY_SIZE;
        }
        translate_address(virtual_address);
    }
}

void print_statistics() {
    printf("TLB Hits: %d\n", tlb_hits);
    printf("TLB Misses: %d\n", tlb_misses);
    printf("Page Faults: %d\n", page_faults);
    printf("TLB Hit Rate: %.2f%%\n", (tlb_hits * 100.0) / memory_accesses);
}

int main() {
    printf("Enter number of memory accesses: ");
    scanf("%d", &memory_accesses);
    printf("Enter TLB replacement policy (FIFO/LRU): ");
    scanf("%s", tlb_policy);
    
    init_memory();
    generate_memory_accesses();
    print_statistics();
    return 0;
}