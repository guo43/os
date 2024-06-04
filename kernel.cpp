#include "types.h"
#include "gdt.h"

void printf(char* str)
{
	static uint16_t* VideoMemory = (uint16_t*)0xb8000;

	static uint8_t x = 0, y = 0;

	for(int i = 0; str[i] != '\0'; ++i)
	{
		switch(str[i])
		{
			case '\n':
				y++;
				x = 0;
				break;
			default:
				VideoMemory[y*80+x] =  (VideoMemory[y*80+x] & 0xFF00) | str[i];
				x++;
		}

		if(x >= 90)
		{
			y++;
			x = 0;
		};

		if (y >= 25)
		{
			for(y = 0; y < 25; y++)
			{
				for (x = 0; x < 80; x++)
				{
					VideoMemory[y*80+x] =  (VideoMemory[y*80+x] & 0xFF00) | ' ';
				}
			}
			x = 0;
			y = 0;
		}
	}
}

typedef void (*constructor)();

extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
	for(constructor* i = &start_ctors; i != &end_ctors; i++)
	{
		(*i)();
	}
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t)
{
	printf("Hello World! --- https://baidu.com\n");
	printf("Hello World! --- https://baidu.com");
	GlobalDescriptorTable gdt;
	while(1);
}