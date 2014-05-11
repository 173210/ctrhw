# argv1 = pc
# argv2 = target
# prints branch offset
# NewPC = (PC + 8) + (offset * 4)
import sys

def tohex(val, nbits):
  return hex((val + (1 << nbits)) % (1 << nbits))


target = sys.argv[2]
pc = sys.argv[1]

print tohex((target-pc-8),24) / 4;
