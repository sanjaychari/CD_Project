import sys
from datetime import datetime

#global variable declarations
data_section = []
registers = {}
main_assembly = []
variables = []
prev_line = ""

#function definitions
def is_numeric(string):
	try:
		num = int(string)
		return True
	except:
		return False

def is_temp(vname):
	return("T" in vname and is_numeric(vname[1:]))

def is_arithmetic_expression(statement):
	return ("+" in statement or "/" in statement or "*" in statement or "/" in statement)

def is_relational_expression(statement):
	return ("==" in statement or ">" in statement or "<" in statement)

def setup_registers():
	global registers
	for i in range(12):
		registers[i] = [0,0]

def find_LRU_register():
	global registers
	LRUtime = datetime.now()
	LRUreg = 0
	for i in range(12):
		if(registers[i] != [0,0]):
			if(registers[i][0] < LRUtime):
				LRUtime = registers[i][0]
				LRUreg = i
	return LRUreg

def check_if_variable_present(variable):
	global registers
	for i in range(12):
		if(registers[i] != [0,0]):
			if(registers[i][1] == variable):
				return i
	return -1

def select_register(variable,value):
	global registers
	global main_assembly
	for i in range(12):
		if(registers[i] == [0,0]):
			registers[i] = [datetime.now(), variable, value]
			return i
	register = find_LRU_register()
	if(not(is_temp(registers[register][1])) and "addr" not in registers[register][1]):
		address_register = check_if_variable_present("addr_"+registers[register][1])
		if(address_register != -1):
			main_assembly.append("STR R"+str(register)+",[R"+str(address_register)+"]")
		else:
			address_register = (find_LRU_register()+1)%12
			registers[address_register] = [datetime.now(), "addr_"+str(registers[register][1]), "0"]
			main_assembly.append("LDR R"+str(address_register)+",addr_"+str(registers[register][1]))
			main_assembly.append("STR R"+str(register)+",[R"+str(address_register)+"]")
	registers[register] = [datetime.now(), variable, value]
	return register

def teardown():
	global registers
	for i in range(12):
		if(not(is_temp(registers[i][1])) and "addr" not in registers[i][1]):
			address_register = check_if_variable_present("addr_"+registers[i][1])
			if(address_register != -1):
				main_assembly.append("STR R"+str(i)+",[R"+str(address_register)+"]")
			else:
				address_register = select_register("addr_"+registers[i][1],"0")
				main_assembly.append("LDR R"+str(address_register)+",addr_"+str(registers[i][1]))
				main_assembly.append("STR R"+str(i)+",[R"+str(address_register)+"]")

def print_assembly():
	global main_assembly
	global data_section
	print(".data")
	for variable in data_section:
		print(variable+": .word 0")
	print("\n.text")
	print(".global _start")
	print("\n_start:")
	for line in main_assembly:
		if(":" not in line):
			print("\t"+line)
		else:
			print(line)
	print()
	for variable in data_section:
		print("addr_"+variable+": .word "+variable)

def handle_assignment_statement(line):
	global main_assembly
	global data_section
	global prev_line
	li_line = line.split(' = ',1)
	if(check_if_variable_present(li_line[0]) == -1):
		variables.append(li_line[0])
		if(not(is_arithmetic_expression(li_line[1])) and not(is_relational_expression(li_line[1]))):
			if(li_line[1] not in variables and is_temp(li_line[0])):
				reg_no = select_register(li_line[0],li_line[1])
				main_assembly.append("MOV R"+str(reg_no)+",#"+li_line[1])
			elif(check_if_variable_present(li_line[1])!=-1 and is_temp(li_line[0])):
				reg_no1 = select_register(li_line[0],li_line[1])
				reg_no2 = check_if_variable_present(li_line[1])
				main_assembly.append("MOV R"+str(reg_no1)+",R"+str(reg_no2))
			elif(li_line[1] in variables and is_temp(li_line[0])):
				reg_no1 = select_register(li_line[0],li_line[1])
				reg_no2 = select_register(li_line[1],"0")
				main_assembly.append("MOV R"+str(reg_no1)+",R"+str(reg_no2))
			elif(li_line[1] not in variables and not(is_temp(li_line[0]))):
				data_section.append(li_line[0])
				reg_no1 = select_register("addr_"+li_line[0],"0")
				main_assembly.append("LDR R"+str(reg_no1)+",addr_"+li_line[0])
				reg_no2 = select_register(li_line[0],li_line[1])
				main_assembly.append("LDR R"+str(reg_no2)+",[R"+str(reg_no1)+"]")
				main_assembly.append("MOV R"+str(reg_no2)+",#"+str(li_line[1]))
			elif(check_if_variable_present(li_line[1])!=-1 and not(is_temp(li_line[0]))):
				data_section.append(li_line[0])
				reg_no1 = select_register("addr_"+li_line[0],"0")
				main_assembly.append("LDR R"+str(reg_no1)+",addr_"+li_line[0])
				reg_no2 = select_register(li_line[0],li_line[1])
				main_assembly.append("LDR R"+str(reg_no2)+",[R"+str(reg_no1)+"]")
				#reg_no3 = select_register(li_line[0],li_line[1])
				reg_no3 = check_if_variable_present(li_line[1])
				main_assembly.append("MOV R"+str(reg_no2)+",R"+str(reg_no3))
			elif(li_line[1] in variables and is_temp(li_line[0])):
				reg_no1 = select_register(li_line[0],li_line[1])
				reg_no2 = select_register(li_line[1],"0")
				main_assembly.append("MOV R"+str(reg_no1)+",R"+str(reg_no2))
		elif(is_arithmetic_expression(li_line[1])):
			if('+' in li_line[1]):
				#print(registers)
				expression = li_line[1].split(' + ',1)
				#print(expression[0])
				reg_no1 = select_register(li_line[0],li_line[1])
				reg_no2 = check_if_variable_present(expression[0])
				reg_no3 = check_if_variable_present(expression[1])
				main_assembly.append("ADD R"+str(reg_no1)+",R"+str(reg_no2)+",R"+str(reg_no3))
			elif("-" in li_line[1]):
				expression = li_line[1].split(' - ',1)
				reg_no1 = select_register(li_line[0],li_line[1])
				reg_no2 = check_if_variable_present(expression[0])
				reg_no3 = check_if_variable_present(expression[1])
				main_assembly.append("SUB R"+str(reg_no1)+",R"+str(reg_no2)+",R"+str(reg_no3))
			elif("*" in li_line[1]):
				expression = li_line[1].split(' * ',1)
				reg_no1 = select_register(li_line[0],li_line[1])
				reg_no2 = check_if_variable_present(expression[0])
				reg_no3 = check_if_variable_present(expression[1])
				main_assembly.append("MUL R"+str(reg_no1)+",R"+str(reg_no2)+",R"+str(reg_no3))
			elif("/" in li_line[1]):
				expression = li_line[1].split(' / ',1)
				reg_no1 = select_register(li_line[0],li_line[1])
				reg_no2 = check_if_variable_present(expression[0])
				reg_no3 = check_if_variable_present(expression[1])
				main_assembly.append("DIV R"+str(reg_no1)+",R"+str(reg_no2)+",R"+str(reg_no3))
		elif(is_relational_expression(li_line[1])):
			if('==' in li_line[1]):
				expression = li_line[1].split(' == ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line
			elif('>=' in li_line[1]):
				expression = li_line[1].split(' >= ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line
			elif('<=' in li_line[1]):
				expression = li_line[1].split(' <= ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line
			elif('>' in li_line[1]):
				expression = li_line[1].split(' > ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line
			elif('>' in li_line[1]):
				expression = li_line[1].split(' < ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line

	else:
		if(not(is_arithmetic_expression(li_line[1])) and not(is_relational_expression(li_line[1]))):
			if(li_line[1] not in variables and is_temp(li_line[0])):
				reg_no = check_if_variable_present(li_line[0])
				main_assembly.append("MOV R"+str(reg_no)+",#"+li_line[1])
			elif(check_if_variable_present(li_line[1])!=-1 and is_temp(li_line[0])):
				reg_no1 = check_if_variable_present(li_line[0])
				reg_no2 = check_if_variable_present(li_line[1])
				main_assembly.append("MOV R"+str(reg_no1)+",R"+str(reg_no2))
			elif(li_line[1] in variables and is_temp(li_line[0])):
				reg_no1 = check_if_variable_present(li_line[0])
				reg_no2 = select_register(li_line[1],"0")
				main_assembly.append("MOV R"+str(reg_no1)+",R"+str(reg_no2))
			elif(li_line[1] not in variables and not(is_temp(li_line[0]))):
				reg_no = check_if_variable_present(li_line[0])
				main_assembly.append("MOV R"+str(reg_no)+",#"+str(li_line[1]))
			elif(check_if_variable_present(li_line[1])!=-1 and not(is_temp(li_line[0]))):
				reg_no1 = check_if_variable_present(li_line[0])
				reg_no2 = check_if_variable_present(li_line[1])
				main_assembly.append("MOV R"+str(reg_no1)+",R"+str(reg_no2))
			elif(li_line[1] in variables and is_temp(li_line[0])):
				reg_no1 = check_if_variable_present(li_line[0])
				reg_no2 = select_register(li_line[1],"0")
				main_assembly.append("MOV R"+str(reg_no1)+",R"+str(reg_no2))

		elif(is_arithmetic_expression(li_line[1])):
			if('+' in li_line[1]):
				#print(registers)
				expression = li_line[1].split(' + ',1)
				print(expression[0])
				reg_no1 = check_if_variable_present(li_line[0])
				reg_no2 = check_if_variable_present(expression[0])
				reg_no3 = check_if_variable_present(expression[1])
				main_assembly.append("ADD R"+str(reg_no1)+",R"+str(reg_no2)+",R"+str(reg_no3))
			elif("-" in li_line[1]):
				expression = li_line[1].split(' - ',1)
				reg_no1 = check_if_variable_present(li_line[0])
				reg_no2 = check_if_variable_present(expression[0])
				reg_no3 = check_if_variable_present(expression[1])
				main_assembly.append("SUB R"+str(reg_no1)+",R"+str(reg_no2)+",R"+str(reg_no3))
			elif("*" in li_line[1]):
				expression = li_line[1].split(' * ',1)
				reg_no1 = check_if_variable_present(li_line[0])
				reg_no2 = check_if_variable_present(expression[0])
				reg_no3 = check_if_variable_present(expression[1])
				main_assembly.append("MUL R"+str(reg_no1)+",R"+str(reg_no2)+",R"+str(reg_no3))
			elif("/" in li_line[1]):
				expression = li_line[1].split(' / ',1)
				reg_no1 = check_if_variable_present(li_line[0])
				reg_no2 = check_if_variable_present(expression[0])
				reg_no3 = check_if_variable_present(expression[1])
				main_assembly.append("DIV R"+str(reg_no1)+",R"+str(reg_no2)+",R"+str(reg_no3))

		elif(is_relational_expression(li_line[1])):
			if('==' in li_line[1]):
				expression = li_line[1].split(' == ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line
			elif('>=' in li_line[1]):
				expression = li_line[1].split(' >= ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line
			elif('<=' in li_line[1]):
				expression = li_line[1].split(' <= ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line
			elif('>' in li_line[1]):
				expression = li_line[1].split(' > ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line
			elif('>' in li_line[1]):
				expression = li_line[1].split(' < ',1)
				reg_no1 = check_if_variable_present(expression[0].strip())
				reg_no2 = check_if_variable_present(expression[1].strip())
				main_assembly.append("CMP R"+str(reg_no1)+",R"+str(reg_no2))
				prev_line = line

#initial setup
setup_registers()

#main code
for line in sys.stdin:
	line = line.rstrip('\n')
	if(" = " in line and ":" not in line):
		handle_assignment_statement(line)
	elif("If False" in line):
		li_line = line.split(" goto ",1)
		if("==" in prev_line):
			main_assembly.append("BNE "+li_line[1])
		elif("<" in prev_line):
			main_assembly.append("BGT "+li_line[1])
		elif(">" in prev_line):
			main_assembly.append("BLT "+li_line[1])
		elif(">=" in prev_line):
			main_assembly.append("BLE "+li_line[1])
		elif("<=" in prev_line):
			main_assembly.append("BGE "+li_line[1])
	elif("goto" in line):
		label = line.split()[1]
		main_assembly.append("B "+label)
	elif(":" in line):
		#main_assembly.append(line)
		li_line_label = line.split(": ")
		if("=" in li_line_label[1]):
			handle_assignment_statement(li_line_label[1])
			main_assembly[-1] = li_line_label[0]+": "+main_assembly[-1]
		elif("goto" in li_line_label[1]):
			label = li_line_label[1].split()[1]
			main_assembly.append("B "+label)
			main_assembly[-1] = li_line_label[0]+": "+main_assembly[-1]
		elif("If False" in li_line_label[1]):
			li_line = li_line_label[1].split(" goto ",1)
			if("==" in prev_line):
				main_assembly.append("BNE "+li_line[1])
			elif("<" in prev_line):
				main_assembly.append("BGT "+li_line[1])
			elif(">" in prev_line):
				main_assembly.append("BLT "+li_line[1])
			elif(">=" in prev_line):
				main_assembly.append("BLE "+li_line[1])
			elif("<=" in prev_line):
				main_assembly.append("BGE "+li_line[1])
			main_assembly[-1] = li_line_label[0]+": "+main_assembly[-1]
	elif("Begin Function" in line):
		function_name = line[15:]
		main_assembly.append("ADD LR, PC, #after")
		main_assembly.append("B "+function_name)
		main_assembly.append(function_name+":")
		#main_assembly.append(line)
	elif("End Function" in line):
		main_assembly.append("MOV PC, LR")
		main_assembly.append("after:")

teardown()
print_assembly()



