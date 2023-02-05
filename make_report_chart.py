import subprocess
import argparse

"""
Usage example:
    # Make a report chart with the default n=10^6, comparing p=1, p=2, p=4, and p=8:
    $ python make_report_chart 1 2 4 8
    # Make a report chart with n=1k, comparing p=2, p=3, and p=4:
    $ python make_report_chart -n=1000 2 3 4
"""
parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('p', metavar='p', type=int, nargs='+',
    help='Number of parallel processes to use to compute the integral estimate')
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
    result = subprocess.run(["make", "run", "n={}".format(n), "p={}".format(p)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    result_str = result.stdout.decode().strip()
    s_t = result_str.split('\n')[-1].split(',')
    return tuple(float(value.strip()) for value in s_t)

args = parser.parse_args()
for p_i in args.p:
    print(execute(args.n, p_i))
