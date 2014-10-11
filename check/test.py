import sys

__author__ = 'Snaipe'

import os
import argparse

from os import listdir, environ
from os.path import join
from subprocess import Popen, PIPE
from contextlib import contextmanager
from colors import Color


TEST_DIR = environ.get('TEST_DIR') or './check/tests'
TEST_BIN = environ.get('TEST_BIN')


@contextmanager
def process(*args, **kwargs):
    proc = None
    try:
        proc = Popen(*args, **kwargs)
        yield proc
    finally:
        if proc is not None:
            proc.wait()


def compare(actual, expected):
    try:
        with open(expected, 'rb') as f:
            expected_contents = f.read().decode('latin-1')
            return expected_contents == actual, expected_contents
    except IOError:
        return True, ""


def format_output(string):
    result = ''
    for line in string.splitlines():
        result += '\t\t"' + line + '"\n'
    return result


def test_output(base, filename, output):
    success, expected = compare(output, join(base, filename))
    if not success:
        sys.stdout.write(Color.fg.red + '\texpected: \n%s' % format_output(expected))
        sys.stdout.write(Color.fg.red + '\tactual: \n%s' % format_output(output) + Color.fg.reset)
    return success


def run_test(category, name):
    base_name = join(TEST_DIR, category, name)
    if not os.path.exists(join(base_name, 'in')):
        return

    print(Color.fg.green + '[ RUN      ]: %s::%s ' % (category, name))
    with process(['%s' % TEST_BIN, './check/test.iso'], stdin=PIPE, stdout=PIPE, stderr=PIPE) as proc:

        with open(join(base_name, 'in'), 'rb') as f:
            out, err = proc.communicate(f.read())
            out = out.decode('latin-1')
            err = err.decode('latin-1')

            success_out = test_output(base_name, 'out', out)
            success_err = test_output(base_name, 'err', err)
            success = success_out and success_err
            if success:
                print(Color.fg.green + '[       OK ]: %s::%s' % (category, name))
            else:
                print(Color.fg.red + '[     FAIL ]: %s::%s' % (category, name))
            return success

def test():
    print(Color.fg.green + '[==========]')
    success = fail = 0
    for d in listdir(TEST_DIR):
        tests = [t for t in listdir(join(TEST_DIR, d)) if os.path.isdir(join(TEST_DIR, d, t))]
        print(Color.fg.green + '[----------]: %s (%d tests)' % (d, len(tests)))
        for t in tests:
            if run_test(d, t):
                success += 1
            else:
                fail += 1
    print(Color.fg.green + '[==========]')
    print(Color.fg.green + '[==========]: Summary -- %d succeeded, %d failed' % (success, fail))


def gen_outputs():
    for d in listdir(TEST_DIR):
        tests = [t for t in listdir(join(TEST_DIR, d)) if os.path.isdir(join(TEST_DIR, d, t))]
        for t in tests:
            base_name = join(TEST_DIR, d, t)
            if not os.path.exists(join(base_name, 'in')):
                continue
            with process(['%s' % TEST_BIN, './check/test.iso'], stdin=PIPE, stdout=PIPE, stderr=PIPE) as proc:
                with open(join(base_name, 'in'), 'rb') as f:
                    out, err = proc.communicate(f.read())
                    with open(join(base_name, 'out'), 'wb') as fout:
                        fout.write(out)
                    with open(join(base_name, 'err'), 'wb') as ferr:
                        ferr.write(err)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--generate', action='store_const', const=True)
    parser.add_argument('binary', nargs='?')
    args = parser.parse_args()
    if args.binary:
        TEST_BIN = args.binary

    if args.generate:
        gen_outputs()
    else:
        test()