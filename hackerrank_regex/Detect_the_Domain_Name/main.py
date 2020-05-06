#!/usr/bin/python 

import sys
import re

domains = set()
final_domains = set()
cases = int(sys.stdin.readline().strip())
for i in range(cases):
    line = sys.stdin.readline()
    if not line:
        break

    line = line.strip()
    match_iter = re.finditer(r'(https?://([\w\-]+\.)+[a-zA-Z]+)/?', line)
    for match in match_iter:
        domains.add(match.group(1))

# print domains

for domain in domains:
    new_domain = re.sub(r'https?://(ww[2w]\.)?', r'', domain)
    final_domains.add(new_domain)

print ';'.join(sorted(list(final_domains)))


