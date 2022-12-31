
import math
from scipy.optimize import linprog
import sys
#定义分支界定法的函数
def integerPro(c, A, b, Aeq, beq, t=1.0E-8):#t的作用为判断x是否为整数
    res = linprog(c, A_ub=A, b_ub=b, A_eq=Aeq, b_eq=beq)
    if(type(res.x) is float or res.status!=0):
        bestX=[sys.maxsize]*len(c)
    else:#如果不是小数求出最优解的值
        bestX = res.x
    bestVal=sum([x * y for x, y in zip(c, bestX)])#求最优解对应的结果
    if all(((x - math.floor(x)) <= t or (math.ceil(x) - x) <= t) for x in bestX):#判断bestX中的每个x是否满足为整数的条件
        return bestVal, bestX#若满足条件则返回最终结果
    else:
        ind = [i for i, x in enumerate(bestX) if (x - math.floor(x)) > t and (math.ceil(x) - x) > t][0]#当x为小数时，取该x对应的行数
        newCon1 = [0] * len(A[0])
        newCon2 = [0] * len(A[0])
        newCon1[ind] = -1#向上取值分界
        newCon2[ind] = 1#向下取值分届
        newA1 = A.copy()#将原始矩阵分别赋值给分出来的2个矩阵
        newA2 = A.copy()
        newA1.append(newCon1)
        newA2.append(newCon2)
        newB1 = b.copy()
        newB2 = b.copy()
        newB1.append(-math.ceil(bestX[ind]))
        newB2.append(math.floor(bestX[ind]))
        r1 = integerPro(c, newA1, newB1, Aeq, beq)
        r2 = integerPro(c, newA2, newB2, Aeq, beq)
        #递归调用
        if r1[0] < r2[0]:
            return r1
        else:
            return r2
#主函数
if __name__ == '__main__':

    c = [3, 4, 1]
    A = [[-1, -6, -2], [-2, 0, 0]]
    b = [-5, -3]
    Aeq = [[0, 0, 0]]
    beq = [0]
    print(integerPro(c, A, b, Aeq, beq))