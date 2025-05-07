//pic.c
#include <stdint.h>
#include "port_io.h"

#define PIC1         0x20
#define PIC2         0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA    (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA    (PIC2 + 1)
#define ICW1_INIT    0x10
#define ICW1_ICW4    0x01
#define ICW4_8086    0x01

void pic_remap(int offset1, int offset2) {
    uint8_t a1 = inb(PIC1_DATA);
    uint8_t a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    outb(PIC1_DATA, offset1); // PIC1 vector offset
    outb(PIC2_DATA, offset2); // PIC2 vector offset

    outb(PIC1_DATA, 4); // Tell PIC1 about PIC2 at IRQ2 (0000 0100)
    outb(PIC2_DATA, 2); // Tell PIC2 its cascade identity (0000 0010)

    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, a1); // Restore masks
    outb(PIC2_DATA, a2);
}
