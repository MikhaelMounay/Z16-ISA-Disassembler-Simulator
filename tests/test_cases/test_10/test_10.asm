    .text
    .org 0
main:
    li a0, 17       # a0 = 17
    li a1, 0x22     # a1 = 0x22 (34)

    and a0, a1      # a0 = a0 AND a1: 17 AND 34 = 0
    ecall 1         # Print a0 -> 0

    li a0, 45       # Load immediate 45 into a0
    ecall 1         # Print a0 -> 45

    ori a0, 0x12    # a0 = a0 ORI 0x12: 45 OR 18 = 63
    ecall 1         # Print a0 -> 63

    xor a0, a1      # a0 = a0 XOR a1: 63 XOR 34 = 29
    ecall 1         # Print a0 -> 29

    andi a0, 0x1F   # a0 = a0 ANDI 0x1F: 29 AND 31 = 29
    ecall 1         # Print a0 -> 29

    xori a0, 0x3C   # a0 = a0 XORI 0x3C: 29 XOR 60 = 33
    ecall 1         # Print a0 -> 33

    or a0, a1       # a0 = a0 OR a1: 33 OR 34 = 51
    ecall 1         # Print a0 -> 35

    mv a0, a1       # Move a1 to a0 (a0 becomes 34)
    ecall 1         # Print a0 -> 34

    ecall 3         # Exit program

    .data
    .org 0x100
