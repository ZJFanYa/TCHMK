import sys
import bigNumDLL
import functions

functions.PrintStart()

paramsNum = len(sys.argv)

if not functions.checkParam(paramsNum, sys.argv):
	sys.exit(-1)

file_In1 = sys.argv[1]
operation = sys.argv[2][0]
file_In2 = sys.argv[3]
fileResult = sys.argv[4]
base = 0
modBool = False

if (paramsNum == 5):
	base = 1000000000

if (paramsNum == 6):
	if (sys.argv[5] == "-b"):
		base = 256
		binKey = sys.argv[5]
	else:
		base = 1000000000
		modFile = sys.argv[5]
		modBool = True

if (paramsNum == 7):
	if (sys.argv[5] == "-b"):
			base = 256
			binKey = sys.argv[5]
			modFile = sys.argv[6]
			modBool = True
	else:
		print "Too many parameters. Error!"
		sys.exit(-1)
		
firstNum = bigNumDLL.bigNum()
secondNum = bigNumDLL.bigNum()
resNum = bigNumDLL.bigNum()

if not firstNum.Read(file_In1, base):
		print "Error of first big number reading"
		sys.exit(-1)
if not secondNum.Read(file_In2, base):
		print "Error of second big number reading"
		sys.exit(-1)
		
if operation == "+": 
	resNum = firstNum + secondNum
elif operation == "-":
	resNum = firstNum - secondNum
elif operation == "*":
	resNum = firstNum * secondNum
elif operation == "/":
	resNum = firstNum / secondNum
elif operation == "^":
	resNum = firstNum ^ secondNum
elif operation == "|":
	resNum = firstNum % secondNum
	
if modBool:
	modBigNum = bigNumDLL.bigNum()
	resModBigNum = bigNumDLL.bigNum()
	if not modBigNum.Read(modFile, base):
		print "Error of modul big number reading"
		sys.exit(-1)
		
	resModBigNum = resBigNum % modBigNum;
	resModBigNum.Write(fileResult)
else:
	resNum.Write(fileResult)

	