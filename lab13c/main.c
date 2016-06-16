/*
* y = y1-y2;
* y1 = |x| if x < 0; x - a if x>= 0/////-2
* y2 = a + x if x % 3 = 1, else y2 = 7/////-9
* */
#include <stdio.h>
//usage: lab13c.exe <x_arg> <a_arg>
int find_y1(int x, int a)
{
	if (x < 0)
	{
		x = abs(x);
	}
	else
	{
		x -= a;
	}
	return x;
}
int find_y2(int x, int a)
{
	if (abs(x) % 3 == 1)
	{
		x += a;
	}
	else
	{
		x = 7;
	}
	return x;
}
int find_y1_ASM(int x, int a)
{
	__asm
	{
		mov eax,x
		test eax,eax
		js absolute
		jge subtract
		absolute:
			neg eax
			jmp end
		subtract:
			mov ecx,a
			sub eax,ecx
		end:
			mov x,eax
	}
	return x;
}
int find_y2_ASM(int x, int a)
{
	//modified for handling negative values
	__asm
	{
		mov eax,x
		test eax,eax
		js absolute
		jns cont
		absolute:
			neg eax
		cont:
		push eax
		mov eax,ecx
		cwd
		mov edx,0
		mov ebx,3
		idiv ebx	
		imul ebx
		mov ecx,eax
		pop eax
		sub eax,ebx
		cmp eax,1
		je add_a
		jne equal_7
		add_a:
			mov eax, x
			mov ecx, a
			add eax, ecx
			jmp end
		equal_7:
			mov eax,7
		end:
			mov x,eax
	}
	return x;
}
int main(int argc, char **argv)
{
	int x = 0;
	int a = 0;
	int y = 0;
	//x = debugValue1;
	//a = debugValue2;
	sscanf(argv[1], "%d", &x);
	sscanf(argv[2],"%d",&a);
	//C
	printf("Input values: x = %d, a = %d",x,a);
	puts("");
	//straight C
	y = find_y1(x, a) - find_y2(x, a);
	//y  = find_y1(x, a);
	//y  = find_y2(x, a);
	printf("Result computed with C: %d\n",y);
	//embedded ASM
	y = find_y1_ASM(x, a) - find_y2_ASM(x, a);
	//y = find_y1_ASM(x, a);
	//y = find_y2_ASM(x, a);
	printf("Result computed with ASM: %d\n", y);
	return 0;
}
