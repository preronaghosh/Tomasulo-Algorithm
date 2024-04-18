# Tomasulo-Algorithm


## Issue Stage:

Get the next instruction from the head of the instruction queue, which is
maintained in FIFO order to ensure the maintenance of correct data flow. If there
is a matching reservation station that is empty, issue the instruction to the station
with the operand values, if they are currently in the registers. If there is not an
empty reservation station, then there is a structural hazard, and the instruction
issue stalls until a station or buffer is freed. If the operands are not in the registers,
keep track of the functional units that will produce the operands. This step
renames registers, eliminating WAR and WAW hazards


## Execute Stage:

If one or more of the operands is not yet available, monitor the common
data bus while waiting for it to be computed. When an operand becomes
available, it is placed into any reservation station awaiting it. When all the operands
are available, the operation can be executed at the corresponding functional
unit. By delaying instruction execution until the operands are available, RAW
hazards are avoided.

Loads and stores require a two-step execution process. The first step computes the effective address 
when the base register is available, and the effective address is then placed in the load or store buffer. 
Loads in the load buffer execute as soon as the memory unit is available. Stores in the store buffer wait for
the value to be stored before being sent to the memory unit. Loads and stores are
maintained in program order through the effective address calculation, which
will help to prevent hazards through memory.


## Writeback Stage:

When the result is available, write it on the CDB and from there
into the registers and into any reservation stations (including store buffers) waiting
for this result. Stores are buffered in the store buffer until both the value to be
stored and the store address are available; then the result is written as soon as the
memory unit is free.

#### PS: This implementation does not support Reorder Buffers, commit and retire stages.
