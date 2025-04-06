# Test file for SW, LW, ECALL 5, and LBU instructions
    .text
    .org 0

.main:
li x1, 0x3F		# Set x1 = 0x3F (base address for memory operations)
li x2, 0x2A		# Set x2 = 0x12 (word value to store)
addi x2, 0x2A		# Add another 0x2A to x2 == 54
li x3, 0x2B		# Set x3 = 0x2B (byte value to store)
li a0, 4
ecall 1

sw x2, 0(x1)		# Store word  at memory address 0x3F
sb x3, 2(x1)		# Store byte at memory address 0x41

lw x4, 0(x1)		# Load word from address 0x3F into x4

li x6, 0x3F		# Set a0 (x6) to the base address of the string
ecall 5			# Print the string 
exit:
    ecall 3		# End simulation

    .data
    .org 0x100
