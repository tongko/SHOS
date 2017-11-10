#ifndef		__ARCH_X86_BOOT_H_
#define		__ARCH_X86_BOOT_H_

#include <stdint.h>

// These functions are from the official GNU stdarg.h file 
typedef char *va_list;

// Amount of space required in an argument list for an arg of type TYPE.
// TYPE may alternatively be an expression whose type is used.  

#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#define va_start(AP, LASTARG) \
 (AP = ((char *) &(LASTARG) + __va_rounded_size(LASTARG)))

extern void va_end (va_list);
#define va_end(AP) //  Does Nothing 

#define va_arg(AP, TYPE) (AP += __va_rounded_size (TYPE), \
  *((TYPE *) (AP - __va_rounded_size (TYPE))))

#define MILLISECONDS_PER_TICK 10

#define freq 100


//	Defines a GDT entry. Use packed, because it prevents the compiler from doing things that it thinks
//	is best: Prevent compiler "optimization" by packing
typedef struct _gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} gdt_entry __attribute__((packed));

//	Special pointer which includes the limit: The max bytes taken up by the GDT, minus 1. Again, this
//	NEEDS to be packed
typedef struct _gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} gdt_ptr __attribute__((packed));

//	Defines an IDT entry.
typedef struct _idt_entry {
	uint16_t	lower_func_ptr;
	uint16_t	cs_offset;
	uint8_t		reserved;
	uint8_t		flags;
	uint16_t	upper_func_ptr;
} idt_entry __attribute__((packed));

//	Our GDT, with 3 entries, and finally our special GDT pointer
gdt_entry gdt[4];
gdt_ptr gp;
idt_entry idt[256];

//	This will be a function in multiboot.asm. We use this to properly reload the new segment registers
extern void gdt_flush(gdt_ptr* ptr);
//	Setup a descriptor in the GDT.
void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
//	Initialize GDT.
void gdt_init(void);

//	Initialize IDT.
void idt_init(void);

// inb: Get a byte from the selected port
uint32_t inb(uint32_t port);
// outb: Send the selected byte to the selected port
void outb(uint32_t port, uint32_t val);
// write_nmi: Write Non Maskable Interrupt
//void write_nmi(uint8_t nmi);
// enable_nmi: Enable Non Maskable Interrupt
//void enable_nmi(void);
// sti: Enable Interrupts:
void sti();
// cli: Disable Interrupts:
void cli();
// hlt: Halt the CPU:
void hlt();
// idle: Freeze the Computer:
void idle();
// reboot: Reboot the Computer:
void reboot();

//	Initialize timer
void init_timer(void);
//	Timer handler
void timer_handler(uint32_t hz);
//	Delay
void delay(uint32_t milliseconds);

//	Compute the length of the given str
uint32_t strlen(const uint8_t *str);
//	Concatenate src to the end of dest.
uint32_t *strcat(uint8_t *dest, const uint8_t *src);


//	Set console color
void _set_color(uint8_t fg, uint8_t bg);
//	Clear console
void _clear(void);
//	print c to console at current cursor position
//	using console fg and bg.
void _putc(uint8 c):
//	Print string with format to console at current cursor position.
uint32_t _printf(const uint8_t *format, ...);
//	Print string with format to dest buffer.
uint32_t _vsprintf(uint8_t *dest, const uint8_t *format, va_list);




#endif	//	__ARCH_X86_BOOT_H_