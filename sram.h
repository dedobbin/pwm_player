#ifndef __SRAM_H__
#define __SRAM_H__

#define SS_PIN 10

/* SRAM operation */
#define WRSR  1
#define WRITE 2
#define READ  3
#define RDSR  5

void ram_init();
void ram_write(char* input, long addr, long len);
void ram_read(char* output, long addr, long len);

#endif
