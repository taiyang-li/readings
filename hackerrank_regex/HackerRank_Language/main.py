#!/usr/bin/python 

import sys
import re


LANGUAGES = 'C:CPP:JAVA:PYTHON:PERL:PHP:RUBY:CSHARP:HASKELL:CLOJURE:BASH:SCALA:ERLANG:CLISP:LUA:BRAINFUCK:JAVASCRIPT:GO:D:OCAML:R:PASCAL:SBCL:DART:GROOVY:OBJECTIVEC'
LANGUAGE_SET = set(LANGUAGES.split(':'))

cases = int(sys.stdin.readline())
for i in range(cases):
    line = sys.stdin.readline().strip()
    match = re.search(r'^[1-9]\d{4} ([A-Z]+)$', line)
    if not match or not match.group(1) in LANGUAGE_SET:
        print "INVALID"
        continue

    print "VALID"
    

