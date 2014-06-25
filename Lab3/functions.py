import bigNumDLL
import sys

def PrintStart():
	print "Realization of arithmetic operations with big numbers"
	print "addition, substraction, multiplication, dividing, involution, taking the remainder"
	print "Main string should be in a such way: "
	print "[fileName1_in] [operation] [fileName2_in] [resFileName] [key] [modFileName]"
	print "	fileName1_in - file with the first big number"
	print "	operation"
	print "		""+"" - addition"
	print "		""-"" - substraction"
	print "		""*"" - multiplication"
	print "		""/"" - dividing"
	print "		""^"" - involution"
	print "		""|"" - taking the remainder"
	print "	fileName2_in - file with the second big number"
	print "	resFileName - file with the big number-result"
	print "	-b - binary processing"
	print "	else - text processing"
	print "	modFileName - file with a big number - modul"
		
def checkParam(paramsNum, arguments):
	if (paramsNum < 5):
		print "There is lake of parameters. Main string was entered wrongly."
		return False

	if (paramsNum > 7):
		print "Too many parameters. Main string was entered wrongly."
		return False

	if(len(sys.argv[2]) > 1):
		print "Wrong operation"
		return False

	return True	

		

		

