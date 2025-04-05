# Test file for BLT, BGE, BLTU, and BGEU instructions
    .text
    .org 0

.main:
li x1, 5         # Set x1 = 5
li x2, 10        # Set x2 = 10
li x3, -5        # Set x3 = -5 (used for signed comparison)
li x4, 0xFFFF    # Set x4 = 0xFFFF (used for unsigned comparison)

blt x1, x2, label_blt   # Branch to label_blt if x1 < x2 (signed)
addi x5, 100            # Increment x5 

bge x2, x1, label_bge   # Branch to label_bge if x2 >= x1 (signed)
addi x6, 200            # Increment x6 

bltu x3, x4, label_bltu # Branch to label_bltu if x3 < x4 (unsigned)
addi x7, 300            # Increment x7 

bgeu x4, x3, label_bgeu # Branch to label_bgeu if x4 >= x3 (unsigned)
addi x0, 400            # Increment x0 

label_blt:
    addi x5, 500       # If BLT is successful, set x5 = 500

label_bge:
    addi x6, 600       # If BGE is successful, set x6 = 600

label_bltu:
    addi x7, 700       # If BLTU is successful, set x7 = 700

label_bgeu:
    addi x0, 800       # If BGEU is successful, set x0 = 800

ecall 1                # Print value of register a0 (x6)
exit:
    ecall 3               # End simulation

    .data
    .org 0x100