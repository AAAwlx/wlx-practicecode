import numpy as np
from scipy.optimize import leastsq
import matplotlib.pyplot as plt

# Define the target function
def func(x, p):
    a, b, c = p
    return a*np.sin(b*x) + c

# Define the error function
def err_func(p, x, y):
    return y - func(x, p)

# Generate some noisy data to fit
xdata = np.linspace(0, 2*np.pi, 50)
ydata = func(xdata, [3, 1.5, 2]) + np.random.normal(scale=0.1, size=len(xdata))

# Fit the data using leastsq()
p0 = [1, 1, 1] # Initial guess for the parameters
popt, pcov = leastsq(err_func, p0, args=(xdata, ydata))

# Plot the results
plt.plot(xdata, ydata, 'bo', label='data')
plt.plot(xdata, func(xdata, popt), 'r-', label='fit')
plt.legend()
plt.show()
