
state_stack=[0]
input_buffer=['i','+','i','*','i','#']
symbol_stack=['#']

def action_table(s, c):
	if s==0 and c=='i': return ('s', 5)
	if s==0 and c=='(': return ('s', 4)

	if s==1 and c=='+': return ('s', 6)
	if s==1 and c=='#': return ('a', 0)

	if s==2 and c=='+': return ('r', 2)
	if s==2 and c=='*': return ('s', 7)
	if s==2 and c==')': return ('r', 2)
	if s==2 and c=='#': return ('r', 2)

	if s==3 and c=='+': return ('r', 4)
	if s==3 and c=='*': return ('r', 4)
	if s==3 and c==')': return ('r', 4)
	if s==3 and c=='#': return ('r', 4)
	
	if s==4 and c=='i': return ('s', 5)
	if s==4 and c=='(': return ('s', 4)
	
	if s==5 and c=='+': return ('r', 6)
	if s==5 and c=='*': return ('r', 6)
	if s==5 and c==')': return ('r', 6)
	if s==5 and c=='#': return ('r', 6)	

	if s==6 and c=='i': return ('s', 5)
	if s==6 and c=='(': return ('s', 4)
	
	if s==7 and c=='i': return ('s', 5)
	if s==7 and c=='(': return ('s', 4)	

	if s==8 and c=='+': return ('s', 6)
	if s==8 and c==')': return ('s',11)	

	if s==9 and c=='+': return ('r', 1)
	if s==9 and c=='*': return ('s', 7)
	if s==9 and c==')': return ('r', 1)
	if s==9 and c=='#': return ('r', 1)	

	if s==10 and c=='+': return ('r', 3)
	if s==10 and c=='*': return ('r', 3)
	if s==10 and c==')': return ('r', 3)
	if s==10 and c=='#': return ('r', 3)	

	if s==11 and c=='+': return ('r', 5)
	if s==11 and c=='*': return ('r', 5)
	if s==11 and c==')': return ('r', 5)
	if s==11 and c=='#': return ('r', 5)	

	return ('e', 0)

def goto_table(s, c):
	if s==0 and c=='E': return 1
	if s==0 and c=='T': return 2
	if s==0 and c=='F': return 3
	if s==4 and c=='E': return 8
	if s==4 and c=='T': return 2
	if s==4 and c=='F': return 3
	if s==6 and c=='T': return 9
	if s==6 and c=='F': return 3
	if s==7 and c=='F': return 10
	return -1

rule_list=[('', ''), ('E', 'E+T'), ('E', 'T'), ('T', 'T*F'), ('T', 'F'), ('F', '(E)'), ('F', 'i')]

def lr_parse():
    while True: #loop, until acc or err
        sss=state_stack[-1]
        aaa=input_buffer[0]
        action_temp=action_table(sss, aaa)
        print 'State    Stack:',state_stack
        print 'Symbol   Stack:',symbol_stack
        print 'Input   Buffer:',input_buffer
        print 'Current Action:',action_temp
        print
        if action_temp[0]=='a': return True
        if action_temp[0]=='e': return False #no err processing currently
        if action_temp[0]=='s':
            symbol_temp=input_buffer.pop(0)
            symbol_stack.append(symbol_temp)
            state_stack.append(action_temp[1])
        elif action_temp[0]=='r':
            rule_temp=rule_list[ action_temp[1] ]
            rule_length=len(rule_temp[1])
            for rrr in range(rule_length):
                symbol_stack.pop()
                state_stack.pop()
            symbol_stack.append(rule_temp[0])
            state_stack.append(goto_table(state_stack[-1], symbol_stack[-1]))
        else:
            return False
