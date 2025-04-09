# Test file for SB, LB, and ECALL 5 instructions
    .text
    .org 0

.main:
li x1, 0x3F		# Set x1 = 0x3F (base address for memory operations)
li x2, 0x30		# Set x2 = '0' (ASCII value for '0')
li x3, 0x31		# Set x3 = '1' (ASCII value for '1')
li x4, 0x32		# Set x4 = '2' (ASCII value for '2')

sb x2, 0(x1)		# Store '0' at memory address 0x3F
sb x3, 1(x1)		# Store '1' at memory address 0x40
sb x4, 2(x1)		# Store '2' at memory address 0x41

lb x5, 0(x1)		# Load byte from address 0x3F into x5 ('0')
lb x6, 1(x1)		# Load byte from address 0x40 into x6 ('1')
lb x7, 2(x1)		# Load byte from address 0x41 into x7 ('2')

li x6, 0x3F		# Set a0 (x6) to the base address of the string
ecall 5			# Print the string

exit:
    ecall 3		# End simulation

    .data
    .org 0x100