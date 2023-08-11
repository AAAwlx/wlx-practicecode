import numpy as np
from scipy.optimize import linear_sum_assignment
def hungarian():
    c = np.array([[6,7,11,2],
                  [4,5,9,8],
                  [3,1,10,4],
                  [5,9,8,2]]);
    r_ind ,c_ind = linear_sum_assignment(c);
    x = np.zeros([4,4])
    x[r_ind ,c_ind]=1;
    res = sum(sum(c*x));
    print(res);
if __name__ == '__main__':
    hungarian()