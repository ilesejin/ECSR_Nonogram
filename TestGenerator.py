import os
import random

n = 6

os.mkdir("DFSResults")
for i in range(0, 105, 5):
    os.mkdir(f"DFSResults/Result_{n}_{i}")
#
# for per in range(0, 105, 5):
#     for r in range(100):
#         a = [[0 for _ in range(n)] for _ in range(n)]
#         for i in range(n):
#             for j in range(n):
#                 a[i][j] = "1" if random.random()<=(per/100) else "0"
#
#         v = []
#         for i in range(n):
#             cnt = 0
#             arr = []
#             for j in range(n):
#                 if a[i][j] == "0":
#                     if cnt!=0: arr.append(cnt)
#                     cnt = 0
#                 else:
#                     cnt += 1
#             if cnt!=0: arr.append(cnt)
#             if arr==[]:
#                 arr = [0]
#             v.append(arr)
#
#         for i in range(n):
#             cnt = 0
#             arr = []
#             for j in range(n):
#                 if a[j][i] == "0":
#                     if cnt!=0: arr.append(cnt)
#                     cnt = 0
#                 else:
#                     cnt += 1
#             if cnt!=0: arr.append(cnt)
#             if arr==[]:
#                 arr = [0]
#             v.append(arr)
#
#         f = open(f"Testcases/Test_{n}_{per}/Test_{r}.txt", 'w')
#         f.write(f"{n} {n}\n")
#         for i in range(2*n):
#             f.write(" ".join(map(str, v[i])) + '\n')
#         for i in range(n):
#             f.write(" ".join(a[i]) + '\n')
#         f.close()
