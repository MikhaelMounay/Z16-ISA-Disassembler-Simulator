# the TEXT Section
    .text
    .org    0
main:

    # test j instruction
    li a0, 1		# A sample instruction
    j L1
    addi a0, 2		# should not be executed

L1:
    ecall 1		# should print 1
    # test jal instruction
    jal ra, print2
    li a0, 3
    ecall 1		# should print 3
    jal ra, print4

exit:
    li a0, 5
    ecall 1		# should print 5
    ecall 3

print2:
    li a0, 2
    ecall 1		# should print 2
    jalr t0, ra

print4:
    li a0, 4
    ecall 1		# should print 4
    jr ra

    .data
    .org    0x100
