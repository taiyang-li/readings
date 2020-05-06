#!/bin/bash

hadoop streaming -input /the/path/of/input -output /the/path/of/output -mapper ./mapper.sh -reducer ./reducer.sh -file mapper.sh -file reducer.sh -jobconf mapred.reduce.tasks=1 -jobconf mapre.job.name="calc_line_with_shell" 
