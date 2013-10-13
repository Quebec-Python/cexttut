import random
import time
import amountc
import amountpy
from currency import CAD

LIST_LENGTH = 100000
LIST_COUNT = 50
INT_RANGE = 1000

def process(l, amountclass):
    result = 0
    for x in l:
        result += amountclass(x, CAD)
    return result

print("Création des listes...")
lists = []
for x in range(LIST_COUNT):
    lists.append([random.randrange(INT_RANGE) for x in range(LIST_LENGTH)])

print("On roule le pas vite...")
start_time = time.time()
res_slow = [process(l, amountpy.Amount).value for l in lists]
slow_time = time.time() - start_time
print("Temps %2.2f" % slow_time)

print("On roule le vite...")
start_time = time.time()
res_fast = [process(l, amountc.Amount).value for l in lists]
fast_time = time.time() - start_time
print("Temps %2.2f" % fast_time)

assert res_slow == res_fast
