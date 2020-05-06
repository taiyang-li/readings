#!/usr/bin/env python 
# coding: utf-8

import os
from hashlib import sha256
from hmac import HMAC

def encrypt_password(password, salt=None):
    """Hash password on the fly."""
    if salt is None:
        salt = os.urandom(8) # 64 bits.

    assert 8 == len(salt)
    assert isinstance(salt, str)

    if isinstance(password, unicode):
        password = password.encode('UTF-8')

    assert isinstance(password, str)

    result = password
    for i in xrange(10):
        result = HMAC(result, salt, sha256).digest()
    return salt + result.encode('hex')

def check_passwd(password, encrypted_password):
    salt = encrypted_password[0:8]
    return encrypted_password == encrypt_password(password, salt)

salt = 'aabbccdd'
password = 'hello world'
encrypted_password = encrypt_password(password, salt)
print check_passwd(password, encrypted_password)

