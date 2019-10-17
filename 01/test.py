import subprocess

def check(expr, result):
    out = subprocess.run(['./calc', expr], stdout=subprocess.PIPE)
    
    if out.returncode == 0 and out.stdout.decode('ascii')!= result:
        print('test err: error {0} != {1}, got {2}'.format(expr, result, out.stdout))

check('abc*5+8', '0')
check('23+3+4/0', '0')
check('2 + 3 * 4 - -2', '16')
check('17 + 3', '20')
check('5*5/5*10', '50')
check('1-1--1--1','2')
check('14+9*17/5*0','14')
check('1 + 2 + 3 + 4 + 5 + 6', '21')
