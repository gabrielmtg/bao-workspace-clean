#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define IPC_BASE_ADDR 0x70000000
#define IPC_SIZE      0x10000

// IPC_Channel layout:
// offset 0 (0 bytes): signal_ready
// offset 1 (4 bytes): resume
// offset 2 (8 bytes): current_label

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <label_to_sync>\n", argv[0]);
        return 1;
    }

    uint32_t label = strtoul(argv[1], NULL, 0);

    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("open(/dev/mem)");
        return 1;
    }

    void *map = mmap(NULL, IPC_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, IPC_BASE_ADDR);
    if (map == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }

    volatile uint32_t *ptr = (volatile uint32_t *)map;

    // 1. Send the label
    ptr[2] = label;

    // 2. Notify VM0 that we are "paused" and ready
    ptr[0] = 1;

    // 3. Poll the resume signal from VM0
    while (ptr[1] == 0) {
        usleep(10000); // Wait 10ms (reduces CPU load)
    }

    // 4. Resume received: consume the signal (clear the flag for the next cycle)
    ptr[1] = 0;

    munmap(map, IPC_SIZE);
    close(fd);
    return 0;
}
