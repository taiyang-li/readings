#!/bin/awk -f

{
    if (NF < 4) 
    {
        print "Not all scores are available for",$1
    }
}

