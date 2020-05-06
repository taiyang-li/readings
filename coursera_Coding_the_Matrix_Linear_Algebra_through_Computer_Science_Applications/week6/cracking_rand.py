# Copyright 2013 David Eisenstat
"""
Computes the tempering matrix from the MT19937 pseudorandom number generator.

>>> from cracking_rand import *
>>> import random
>>> prng = random.Random()
>>> n = 624
>>> data = [prng.getrandbits(32) for k in range(n)]
>>> seed = prng.getstate()[1][:n]
>>> T = tempering_mat()
>>> data == [int_from_vec(T * vec_from_int(x)) for x in seed]
True
"""


from mat import Mat
from vec import Vec

#This module should use GF2.one but doesn't yet

one = 1


def format_bit(b):
    """
    Converts a bit to a string.

    >>> format_bit(0)
    '0'
    >>> format_bit(one)
    '1'
    """
    return '0' if b == 0 else '1'


def print_vec(v):
    """
    Prints a bit vector compactly.

    >>> print_vec(Vec({0, 1, 2, 3, 4, 5, 6, 7}, {1: one, 3: one, 5: one}))
    01010100
    >>> print_vec(Vec({0, 1, 2, 3}, {0: one, 2: one, 3: one}))
    1011
    """
    print(''.join(format_bit(v[k]) for k in sorted(v.D)))


def print_mat(m):
    """
    Prints a bit matrix compactly.

    >>> print_mat(Mat(({0, 1, 2}, {0, 1, 2}), {(0, 1): one, (1, 2): one}))
    010
    001
    000
    """
    D0, D1 = map(sorted, m.D)
    for i in D0:
        print(''.join(format_bit(m[(i, j)]) for j in D1))


def vec_from_int(m, n=32):
    """
    Returns the n-bit vector specified by the integer m.

    >>> print_vec(vec_from_int(0b00101010, 8))
    01010100
    >>> print_vec(vec_from_int(0b1101, 4))
    1011
    """
    return Vec(set(range(n)), {k: one for k in range(n) if (2 ** k) & m})


def int_from_vec(v):
    """
    Returns the integer specified by the bit vector v.

    >>> int_from_vec(vec_from_int(42, 8))
    42
    >>> int_from_vec(vec_from_int(13, 4))
    13
    """
    # TODO(david): use GF2
    return sum(2 ** k for k in v.D if v[k] & 1)


def left_shift(k, n=32):
    """
    Returns the n*n matrix corresponding to the operation

        lambda v: vec_from_int(int_from_vec(v) << k, n)

    >>> print_mat(left_shift(2, 6))
    000000
    000000
    100000
    010000
    001000
    000100
    >>> int_from_vec(left_shift(2) * vec_from_int(42)) == 42 << 2
    True
    """
    D = set(range(n))
    return Mat((D, D), {(j + k, j): one for j in range(n - k)})


def right_shift(k, n=32):
    """
    Returns the n*n matrix corresponding to the operation

        lambda v: vec_from_int(int_from_vec(v) >> k, n)

    >>> print_mat(right_shift(1, 4))
    0100
    0010
    0001
    0000
    >>> int_from_vec(right_shift(1) * vec_from_int(13)) == 13 >> 1
    True
    """
    D = set(range(n))
    return Mat((D, D), {(i, i + k): one for i in range(n - k)})


def diag(v):
    """
    Returns the diagonal matrix specified by the vector v.

    >>> print_mat(diag(vec_from_int(13, 4)))
    1000
    0000
    0010
    0001
    """
    return Mat((v.D, v.D), {(k, k): v[k] for k in v.D})


def bitwise_and(m, n=32):
    """
    Returns the matrix for masking an n-bit vector by the integer m.

    >>> print_mat(bitwise_and(13, 4))
    1000
    0000
    0010
    0001
    """
    return diag(vec_from_int(m, n))


def identity_mat(n=32):
    """
    Returns the n*n identity matrix.

    >>> print_mat(identity_mat(4))
    1000
    0100
    0010
    0001
    """
    D = set(range(n))
    return Mat((D, D), {(k, k): one for k in range(n)})


def tempering_mat():
    """
    Returns the matrix corresponding to the MT19937 tempering transform.

    >>> print_mat(tempering_mat())
    10010000000100100010001000000100
    01000000000010000001000100000010
    00100000000001000000100000000001
    00010000000000100000010001000000
    10001001000100010010001000000000
    00000100100000001001000100000000
    00100010010001000100100010001000
    10010001001100100010010001000000
    00000000100100000001001000100010
    00100100010011001000100100010001
    00010000001000100000010000001000
    00000001000100100010001001000100
    00000100000010011000000100100010
    00000000000001001000000010010001
    00000001000000100010000001000000
    00000000000000010000000000100000
    00000000000000001000000000010000
    00100000000001000100000000001000
    00010000000100100010001000000100
    00000000000010000001000100000010
    00000000000000000000100000000001
    00000000000000100000010001000000
    10000001000100000010001000000000
    00000000100000000001000100000000
    00100000010001000100100010001000
    00010000001000100000010001000000
    00000000000100000001001000100010
    00000100000010001000100100010001
    00000000000000000000010000001000
    00000001000000100010000001000100
    00000000000000010000000000100010
    00000000000000001000000010010001
    """
    m = identity_mat()
    m += right_shift(11) * m
    m += bitwise_and(0x9d2c5680) * left_shift(7) * m
    m += bitwise_and(0xefc60000) * left_shift(15) * m
    m += right_shift(18) * m
    return m


if __name__ == '__main__':
    from doctest import testmod
    testmod()
