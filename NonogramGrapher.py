import pandas as pd

n = 6
res = [[] for _ in range(0, 105, 5)]

def checkLine(boardline, cons):
    realCons = []
    cnt = 0
    for i in boardline:
        if i==0:
            if cnt!=0:
                realCons.append(cnt)
            cnt = 0
        else:
            cnt += 1
    if cnt!=0:
        realCons.append(cnt)
    if len(realCons)==0:
        realCons.append(0)
    return realCons == cons

def checkBoard(board, constraints):
    rightRes = 0
    for k in range(n):
        newLine = [board[k][l] for l in range(n)]
        if checkLine(newLine, constraints[k]):
            rightRes += 1
    for k in range(n):
        newLine = [board[l][k] for l in range(n)]
        if checkLine(newLine, constraints[k + n]):
            rightRes += 1

    return rightRes

for i in range(0, 105, 5):
    bpsumsim = 0
    bptime = 0
    bpsumright = 0
    totalsumright = 0
    for j in range(100):

        f = open("Testcases/Test_6_"+str(i)+"/Test_"+str(j)+".txt", 'r')
        lines = f.readlines()
        f.close()
        if len(lines)==0:
            print("???")
            continue
        constraints = [list(map(int, lines[k].split())) for k in range(1, n*2+1)]
        ans = [list(map(int, lines[k+13].split())) for k in range(n)]

        f = open("Results/Result_6_"+str(i)+"/Result_"+str(j)+".txt", 'r')
        lines = f.readlines()
        f.close()
        if len(lines)==0:
            print("???")
            continue
        bpans = [list(map(int, lines[k+n*2+1].split())) for k in range(n)]
        bpsim = 0
        for k in range(n):
            for l in range(n):
                if ans[k][l] == bpans[k][l]:
                    bpsim+=1
        bpsumsim += bpsim/n/n

        totalsumright += checkBoard(ans, constraints)/(2*n)
        bpsumright += checkBoard(bpans, constraints)/(2*n)


    bpsumsim /= 100

    res[i//5].append(bpsumsim)
    res[i // 5 ].append(bpsumright/100)
    print(bpsumsim, bpsumright/100)

df = pd.DataFrame(res, columns=['sim', 'right'])
df.to_csv("BPResult8.csv")
# write_wb = Workbook()
# write_ws = write_wb.create_sheet('Result')
# for i in range(n):
#     for j in range(len(res[0])):
#         write_ws.cell(j+2, i+5, res[i][j])
# write_wb.save("Graph_15.xlsx")
