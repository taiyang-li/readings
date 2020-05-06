#!/usr/local/bin/python

nums = []

while True:
    num = raw_input("Enter a number: ")
    if num == "done" : 
        break

    try:
        nums.append(int(num))
    except:
        print "Invalid input";

print "Maximum is ", max(nums)
print "Minimum is ", min(nums)
