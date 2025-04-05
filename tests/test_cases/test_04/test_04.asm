# Test file for beq, bz, bne, and bnz instructions
    .text
    .org 0

.main:
li x1, 5         # Initialize x1 = 5
li x2, 5         # Initialize x2 = 5
li x3, 0         # Initialize x3 = 0 
li x4, -1        # Initialize x4 = -1 

beq x1, x2, label_eq   # Branch if x1 == x2
bne x1, x3, label_ne   # Branch if x1 != x3
bz x3, label_zero      # Branch if x3 == 0
bnz x4, label_nonzero  # Branch if x4 != 0

label_eq:
    li a0, 100       # If BEQ is successful, set x5 = 100
    ecall 1

label_ne:
    li a0, 200       # If BNE is successful, set x6 = 200
    ecall 1

label_zero:
    li a0, 300       # If BZ is successful, set x7 = 300
    ecall 1

label_nonzero:
    li a0, 400       # If BNZ is successful, set x0 = 400
    ecall 1
exit:
    ecall 3               # End simulation

    .data
    .org 0x100