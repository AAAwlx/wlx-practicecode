import numpy as np

a = np.pi / 120
b = 2 * np.pi / 3

for i in np.arange(0, 2.2, 0.3):
    y = i * 1852
    degrees = 0
    radians = np.deg2rad(degrees)
    v = np.arctan(np.sin(radians) * np.tan(a))
    w = ((120 + y * np.cos(radians) * np.tan(a)) * np.sin(b) * np.cos(v)) / ((np.cos(b / 2) * np.cos(v)) ** 2 - (np.sin(b / 2) * np.sin(v)) ** 2)
    print("For i =", i)
    print("w =", w)
