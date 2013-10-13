import random
import time
import slow
import fast

LIST_LENGTH = 100000
LIST_COUNT = 500
INT_RANGE = 1000

print("Création des listes...")
lists = []
for x in range(LIST_COUNT):
    lists.append([random.randrange(INT_RANGE) for x in range(LIST_LENGTH)])

print("On roule le pas vite...")
start_time = time.time()
res_slow1 = [slow.slow1(l) for l in lists]
slow1_time = time.time() - start_time
print("Temps %2.2f" % slow1_time)

print("On roule le moyen vite...")
start_time = time.time()
res_slow2 = [slow.slow2(l) for l in lists]
slow2_time = time.time() - start_time
print("Temps %2.2f" % slow2_time)
print("Ah, finalement, pas tellement plus vite...")

print("On roule le vite...")
start_time = time.time()
res_fast1 = [fast.fast1(l) for l in lists]
fast1_time = time.time() - start_time
print("Temps %2.2f" % fast1_time)

print("On roule le vite-mais-avec-les-checks...")
start_time = time.time()
res_fast2 = [fast.fast2(l) for l in lists]
fast2_time = time.time() - start_time
print("Temps %2.2f" % fast2_time)

assert res_slow1 == res_slow2 == res_fast1 == res_fast2
