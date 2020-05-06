#!/bin/bash

hadoop streaming -input /the/path/of/input -output /the/path/of/output -mapper ./mapper.py -reducer ./reducer.py -file mapper.py -file reducer.py -jobconf mapred.reduce.tasks=1 -jobconf mapre.job.name="calc_word_frequency" 
