file_head="""#! /use/bin/env fish
# written by python script: script-generator.py
# SET THIS COUPLING VAR BEFORE RUNNING IT !!!
#       \__________________________________________________________________________________________
#                         \                                                                        \\
\n
"""

for c in range(50): # which couple
    file_ob = open('run_a_couple_%d.sh'%c, 'w')  # generate a script for each couple
    file_ob.write(file_head)
    for s in [0, 1, 2, 4, 8]: # shift 0,1,2,...
        for t in range(5,10): # 5 trials
            file_ob.write("cd /home/mwang/neo_decorr/%d/shift%d_trial%d; cp /home/mwang/neo_decorr/prc .; chmod +x prc; ./prc %d %d > output.txt &\n"%(c,s,t,s,c))
        file_ob.write("\n")
    file_ob.close()
