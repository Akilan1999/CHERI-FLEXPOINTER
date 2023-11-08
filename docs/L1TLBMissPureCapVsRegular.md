## Measuring CHERI current TLB performance
Before this experiment could begin benchmarks where can to improve that
running with CHERI with PureCap creates more TLB cache pressure than
running CHERI without PureCap (i.e 64 bit mode). The program ran was
simple Kmeans C program. The metrics measures where:
### Instruction TLB walk
The counter counts each access counted by L1I_TLB that causes a refill of
an instruction TLB
involving at least one translation table walk access.
This includes each complete or partial translation table walk that causes
an access to memory,
including to data or translation table walk caches.
![Instruction TLB
walk](https://github.com/Akilan1999/PhD-Research/assets/31743758/0070cf75-16b7-42f6-ba62-1d2cc0513832)
### Data TLB walk
The counter counts each access counted by L1D_TLB that causes a refill of
a data or unified TLB
involving at least one translation table walk access.
This includes each complete or partial translation table walk that causes
an access to memory,
including to data or translation table walk caches
![Data TLB
walk](https://github.com/Akilan1999/PhD-Research/assets/31743758/1822eada-410d-4f30-ad23-4db3fe09a254)
### L1 TLB data access
The counter counts each Memory-read operation or Memory-write operation
that causes a TLB
access to at least the Level 1 data or unified TLB.
![L1 TLB data
access](https://github.com/Akilan1999/PhD-Research/assets/31743758/5b8e24de-de3f-45c7-8d7a-764182b2a5fe)
### L1 TLB instruction access
The counter counts each Instruction memory access that causes a TLB access
to at least the Level 1
instruction TLB.
![L1 TLB Instruction
access](https://github.com/Akilan1999/PhD-Research/assets/31743758/3048d403-7965-41c8-98b3-525c570df9d9)
### L1 Data TLB read
if the L1D_TLB_RW event is implemented, the counter counts each access
counted by
L1D_TLB_RW that is a Memory-read operation.
![L1 Data TLB read
](https://github.com/Akilan1999/PhD-Research/assets/31743758/e0700431-7d31-4ed3-9ff4-d937e0f1729e)
### L1 Data TLB write
If the L1D_TLB_RW event is implemented, the counter counts each access
counted by
L1D_TLB_RW that is a Memory-write operation.
![L1 Data TLB
write](https://github.com/Akilan1999/PhD-Research/assets/31743758/8d2f4125-9e8d-4277-a947-8b5f24fe48da)
### STALL BACKEND
The counter counts each cycle counted by CPU_CYCLES where no Attributable
instruction or
operation was sent for execution and either:
• The backend is unable to accept any of the instruction operations
available for the PE.
• The backend is unable to accept any operations for the PE
![STALL
BACKEND](https://github.com/Akilan1999/PhD-Research/assets/31743758/e8b74bb0-46a0-4b2e-b3cd-64a51a3a1e3d)

### STALL FRONTEND
The counter counts each cycle counted by CPU_CYCLES where no Attributable
instruction or
operation was sent for execution and there was no Attributable instruction
or operation available to
dispatch for the PE from the frontend.
![STALL
FRONTEND](https://github.com/Akilan1999/PhD-Research/assets/31743758/6077895d-fb88-497a-863f-9e987ef1837a)
