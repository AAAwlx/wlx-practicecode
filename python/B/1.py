
import pandas as pd
from sympy import symbols, Eq, solve
import math

x, y = symbols('x y')
alpha = math.radians(1.5)
theta = math.radians(120)
distances = [-800, -600, -400, -200, 0, 200, 400, 600, 800]
results1 = []

for i, d in enumerate(distances):
    deep = 70 - d * math.tan(alpha)
    w = abs(2 * abs(deep) * math.cos(alpha) * math.sin(theta) / (math.cos(theta) + math.cos(math.radians(3))))
    line1 = Eq(math.tan(math.radians(30)) * x - y, 0)
    line2 = Eq(165.45 - math.tan(math.radians(30)) * x - y, 0)
    line3 = Eq(math.tan(alpha) * (d + 800 + x) - y, 0)

    solution1 = solve((line1, line3), (x, y))
    solution2 = solve((line2, line3), (x, y))
    solution3 = solve((line1, line2), (x, y))

    if solution1 and solution2 and solution3:
        x1, y1 = solution1[x], solution1[y]
        x2, y2 = solution2[x], solution2[y]
        y3 = solution3[y]

        if y3 > y1 or y3 > y2:
            f = 1
        else:
            f = -1

        if i == 0:
            n = 0
        else:
            distance1 = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
            n = f * distance1 / results1[i - 1][2]

        results1.append([d, deep, w, n])

df1 = pd.DataFrame(results1, columns=['测线距中心点处的距离/m', '距离中心的深度/m', '覆盖宽度/m', 'y'])
print(df1)

