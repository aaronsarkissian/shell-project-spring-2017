import sys
import pexpect

def test_iterate_shell():
    '''Kick off the test suite'''
    print("Testing the shell")
    iterate_shell = pexpect.spawnu('./iterate_shell')
    iterate_shell.logfile = sys.stdout
    iterate_shell.sendline('pwd')
    print(iterate_shell)



if __name__ == '__main__':
    test_iterate_shell()
