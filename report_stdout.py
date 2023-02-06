import subprocess
import argparse

parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('-p', type=int, default=10,
    help='Specify the max numper of processors, and test all num_processors in [1:p]')
parser.add_argument('-n', type=int, default=10**6,
    help='Total number of sum terms used to estimate the integral')

"""
Arguments:
    - `n`: Total number of sum terms used to estimate the integral, across all processes
    - `p`: Number of parallel processes to use to compute the integral estimate
Output: A tuple `(s, t)` of floats.
        - `s` (first element): The integral estimate result
        - `t` (second element): The wall-clock time, in seconds, taken to compute the integral estimate
"""
def execute(n=1000, p=4):
    result = subprocess.run(['make', 'run', 'n={}'.format(n), 'p={}'.format(p)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    result_str = result.stdout.decode().strip()
    s_t = result_str.split('\n')[-1].split(',')
    return tuple(float(value.strip()) for value in s_t)

args = parser.parse_args()

ps = range(1, args.p + 1)
P_I = [(p_i, execute(args.n, p_i)[-1]) for p_i in ps] # List of tuples `[(p1, t1), (p2, t2), ...]`

print(P_I)
