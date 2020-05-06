#!/usr/bin/python 

id2salary = {0:1000.0, 3:990, 1:1200.50}
names = ['Larry', 'Curly', '', 'Moe']

salaries = id2salary.values()
names2salary = {name:salary for name in names for salary in salaries}
print names2salary
