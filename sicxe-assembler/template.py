"""
**************************************************************************
# SASM[-S][-l]<asmfile><objfile>
# -l standard output?
# -S SIC instead of SIC XE?

FILE: template.py

AUTHOR: Kevin Xiao

ASSIGNMENT: Lab 8

DATE DUE: Last Class

DESCRIPTION: 

***************************************************************************
"""
import re
import sys



INST = {}
INST["ADD"] = 3, "18", False
INST["ADDF"] = 3, "58", True
INST["ADDR"] = 2, "90", True
INST["AND"] = 3, "40", False
INST["CLEAR"] = 2, "B4", True
INST["COMP"] = 3, "28", False
INST["COMPF"] = 3, "88", True
INST["COMPR"] = 2, "A0", True
INST["DIV"] = 3, "24", False
INST["DIVF"] = 3, "64", True
INST["DIVR"] = 2, "9C", True
INST["FIX"] = 1, "C4", True
INST["FLOAT"] = 1, "C0", True
INST["HIO"] = 1, "F4", True
INST["J"] = 3, "3C", False
INST["JEQ"] = 3, "30", False
INST["JGT"] = 3, "34", False
INST["JLT"] = 3, "38", False
INST["JSUB"] = 3, "48", False
INST["LDA"] = 3, "00", False
INST["LDB"] = 3, "68", True
INST["LDCH"] = 3, "50", False
INST["LDF"] = 3, "70", True
INST["LDL"] = 3, "08", False
INST["LDS"] = 3, "6C", True
INST["LDT"] = 3, "74", True
INST["LDX"] = 3, "04", False
INST["LPS"] = 3, "D0 P", True
INST["MUL"] = 3, "20", False
INST["MULF"] = 3, "60", True
INST["MULR"] = 2, "98", True
INST["NORM"] = 1, "C8", True
INST["OR"] = 3, "44", False
INST["RD"] = 3, "D8", False
INST["RMO"] = 2, "AC", True
INST["RSUB"] = 3, "4C", False
INST["SHIFTL"] = 2, "A4", True
INST["SHIFTR"] = 2, "A8", True
INST["SIO"] = 1, "F0", True
INST["SSK"] = 3, "EC", True
INST["STA"] = 3, "0C", False
INST["STB"] = 3, "78", True
INST["STCH"] = 3, "54", False
INST["STF"] = 3, "80", True
INST["STI"] = 3, "D4", True
INST["STL"] = 3, "14", False
INST["STS"] = 3, "7C", True
INST["STSW"] = 3, "E8", False
INST["STT"] = 3, "84", True
INST["STX"] = 3, "10", True
INST["SUB"] = 3, "1C", False
INST["SUBF"] = 3, "5C", True
INST["SUBR"] = 2, "94", True
INST["SVC"] = 2, "B0", True
INST["TD"] = 3, "E0", False
INST["TIO"] = 1, "F8", True
INST["TIX"] = 3, "2C", False
INST["TIXR"] = 2, "B8", True
INST["WD"] = 3, "DC", False

def readfile(filename):
    output = []
    f = open(filename, "r")
    for line in f:
        newLine = []
        match = re.search('([.]?)', line)
        if match:
            newLine.append(match.group(1)) # . check
        match = re.search(
            '([\w]*)[\s]*([\+]?)[\s]*([\w]*)[\s]*([@#]?)[\s]*([\w]*)[\s]*([,\']?)[\s]*([\w\s]*)([\']?)'
			, line)
        if match:
            newLine.append(match.group(1)) # label
            newLine.append(match.group(2)) # +
            newLine.append(match.group(3)) # mnemonic
            newLine.append(match.group(4)) # @#
            newLine.append(match.group(5)) # operand
            newLine.append(match.group(6)) # ,'
            newLine.append(match.group(7)) # more operand
            newLine.append(match.group(8)) # ' detection
            
        output.append(newLine)
        if match.group(3) == "END":
            break
    f.close()
    return output

# ================================== #
# =========The First Pass=========== #
# ================================== #

def firstpass(array):
    errorFlag = False
    endFlag = False

    # ==== ALL MATTERS RELATING TO START ==== #
    startIndex = None
    for i in range(len(array)):
        line = array[i]
        string = line[3]     
        if string.upper() == 'START':

        # v Error Handling v #
            if not((line[2] == "") and (line[4] == "")):
                print "WARNING! Unnecessary '+, #, @' at START"
                print line
            if line[4] == '+':
                print "WARNING! START not affected by '+'"
                print line
            if line[5] == "":
                print "WARNING! No START address given; defaulting to 0"
                print line
                line[5] = str(0)
            if len(line[5]) > 5:
                print "ERROR! START address longer than 5 characters" 
                print line
                errorFlag = True
            addr = line[5].upper()
            if not re.match("^[A-F|0-9]*$", addr):
                print "ERROR! START address contains non-hex characters"
                print line
                errorFlag = True
            if errorFlag:
                sys.exit(1)
        # ^^Error Handling^^ #

            startIndex = i
            line[0] = hex(int(line[5], 16))[2:].upper()
            break
    if startIndex == None:
        #print "ERROR! START directive not found"
        #sys.exit(1)
        print "WARNING! START directive not found; defaulting to 0"
        startIndex = 0
        array[0][0] = hex(0)[2:].upper()
        
    # THE ANALYSIS OF ADDRESSES #
    currentAddr = array[startIndex][0]
    for i in range(startIndex + 1, len(array)):
        line = array[i]
        if line[0] == ".":
            pass
        elif line[3] == "":
            print "WARNING! Missing mnemonic: skipping line " + str(i)
            print line
        else:
            line[0] = currentAddr
            increment = handleIncrement(line, i)
            if increment == "END":
                endFlag = True
                break
            currentAddr = hex(int(line[0], 16) + increment)[2:].upper()
            if len(currentAddr) > 5:
                print "ERROR! Program too large: line " + str(i)
                print line
                sys.exit(1)
    if endFlag:
        return array, startIndex
    else:
        print "ERROR! END directive not found"
        sys.exit(1)
# ==== FIRST PASS ADDRESS CALCULATOR ==== #
def handleIncrement(line, i):
    increment = 0
    mnemonic = line[3].upper()

    # v Error Handling v #
    if mnemonic == "START":
        print "ERROR! START has already been called: line " + str(i)
        print line
        sys.exit(1)
    if mnemonic == "BASE":
        if not re.match("^[\w]*$", line[7]):
            print "ERROR! Unexpected non-label character: line " + str(i)
            print line
            sys.exit(1)
        return 0
    if mnemonic == "NOBASE":
        return 0
    if mnemonic == "WORD":
        if not((line[2] == "") and (line[4] == "")):
            print "WARNING! Unnecessary '+, #, @': line " + str(i)
            print line
        return 3
    if mnemonic == "RESB":
        if not((line[2] == "") and (line[4] == "")):
            print "WARNING! Unnecessary '+, #, @': line " + str(i)
            print line
        return int(line[5])
    if mnemonic == "RESW":
        if not((line[2] == "") and (line[4] == "")):
            print "WARNING! Unnecessary '+, #, @': line " + str(i)
            print line
        return int(line[5])*3
    if mnemonic == "BYTE":
        if not((line[2] == "") and (line[4] == "")):
            print "WARNING! Unnecessary '+, #, @': line " + str(i)
            print line
        if line[5].upper() == "C":
            if not ((line[6] == "'")and(line[8] == "'")):
                print "ERROR! Unclosed quotes: line " + str(i)
                print line
                sys.exit(1)
            return len(line[7])
        if line[5].upper() == "X":
            if not ((line[6] == "'")and(line[8] == "'")):
                print "ERROR! Unclosed quotes: line " + str(i)
                print line
                sys.exit(1)
            if not re.match("^[A-F|0-9]*$", line[7]):
                print "ERROR! Unexpected non-hex character: line " + str(i)
                print line
                sys.exit(1)
            return (len(line[7]) / 2) + (len(line[7]) % 2)
        if not re.match("^[0-9]*$", line[5]):
            print "ERROR! Unexpected non-integer: line " + str(i)
            print line
            sys.exit(1) 
        return int(line[5])
    # ^^Error Handling^^ #

    
    if mnemonic == "END":
        return "END"

    if mnemonic == "":
        print "ASSEMBLY ERROR! Empty mnemonic passed: line " + str(i)
        print line
        return 0
    
    if not INST.has_key(mnemonic):
        print "ERROR! Invalid mnemonic: line " + str(i)
        print line
        sys.exit(1)

    increment = INST[mnemonic][0]
    if line[2] == "+":
        increment = increment + 1
    
    return increment

# ========================= #
# ==== THE SECOND PASS ==== #
# ========================= #

def secondpass(array, startIndex):
    endOp = array[startIndex][0]
    firstLine = startIndex + 1
    newArray = []
    newArray.append(array[startIndex][1])
    firstAddress = array[firstLine][0]
    while len(firstAddress) < 6:
        firstAddress = '0' + firstAddress
    newArray.append(firstAddress)
    lastAddress = array[len(array)-1][0]
    size = hex(int(lastAddress, 16) - int(firstAddress, 16))[2:].upper()
    while len(lastAddress) < 6:
        lastAddress = '0' + lastAddress
    newArray.append(size)
    

    # Build Label Array #
    labels = {}
    for i in range(firstLine, len(array)):
        line = array[i]
        if line[1] != "":
            if labels.has_key(line[1]):
                print "ERROR! Repeat label: line " + str(i)
                print line
                sys.exit(1)
            if not re.match('^[a-zA-Z]?$', line[1][:1]):
                print "ERROR! Label must begin with letter: line " + str(i)
                print line
                sys.exit(1)
            labels[line[1]] = line[0]

    # Build Label Array #

    baseExist = False
    baseAddress = None

    # ======= The Mega Loop ======= #
    
    for i in range(firstLine, len(array)):
        objectCode = ""
        line = array[i]
        mnemonic = line[3].upper()
        

        # DIRECTIVES #
        if mnemonic == "END":
            if re.match("^[0-9]*$", line[5]):
                endOp = hex(int(line[5]))[2:].upper()
            elif labels.has_key(line[5]):
                endOp = labels[line[5]]
            else:
                print "ERROR! Invalid address: line " + str(i)
                print line
                sys.exit(1)
        if mnemonic == "BASE":
            if re.match("^[0-9]*$", line[5]):
                baseAddress = hex(int(line[5]))[2:].upper()
                baseExist = True
            else:
                if labels.has_key(line[5]):
                    baseAddress = labels[line[5]]
                else:
                    print "ERROR! Nonexistant label: line " + str(i)
                    print line
                    sys.exit(1)
        elif mnemonic == "NOBASE":
            baseExist = False
        elif mnemonic == "WORD":
            if not re.match("^[0-9]+$", line[5]):
                print "ERROR! Unexpected non-integer: line " + str(i)
                print line
                sys.exit(1)
            if int(line[5]) > 16777215:
                print "ERROR! Integer too large for 3 bytes: line " + str(i)
                print line
                sys.exit(1)
            objectCode = hex(int(line[5]))[2:].upper()
            while len(objectCode) < 6:
                objectCode = '0' + objectCode
        elif mnemonic == "BYTE":
            if line[5] == "X":
                objectCode = hex(int(line[7], 16))[2:].upper()
                if len(objectCode) % 2 == 1:
                    objectCode = '0' + objectCode
            elif line[5] == "C":
                objectCode = line[7].encode("hex")
            else:
                objectCode = line[5]



        

        # =< 2 FORMAT INSTRUCTIONS #
        elif INST.has_key(mnemonic):
            objectCode = objectCode + INST[mnemonic][1]
            regs = {'A': '0', 'X': '1', 'L': '2', 'B': '3', 'S': '4', 'T': '5', 'F': '6'}
            if INST[mnemonic][0] <= 2:
                r1 = line[5].upper()
                r2 = line[7].upper()[:1]
                r1match = (r1 == 'B') or (r1 == 'S') or (r1 == 'T') or (r1 == 'F') or (r1 == 'A') or (r1 == 'X') or (r1 == 'L')
                r2match = (r2 == 'B') or (r2 == 'S') or (r2 == 'T') or (r2 == 'F') or (r2 == 'A') or (r2 == 'X') or (r2 == 'L')
                
                objectCode = hex(int(objectCode, 16))[2:].upper()
               
                if (mnemonic == "CLEAR") or (mnemonic == "TIXR"):
                    if not r1match:
                        print "ERROR! Expecting valid register: line " + str(i)
                        print line
                        sys.exit(1)
                    objectCode = objectCode + regs[r1] + '0'
                elif mnemonic == "SVC":
                    if not (int(r1) <= 16) and (int(r1) >= 1):
                        print "ERROR! Expecting 1 <= n <= 16: line " + str(i)
                        print line
                        sys.exit(1)
                    objectCode = objectCode + r1
                elif (mnemonic == "SHIFTL") or (mnemonic == "SHIFTR"):
                    if not r1match:
                        print "ERROR! Expecting valid register: line " + str(i)
                        print line
                        sys.exit(1)
                    if not line[6] == ",":
                        print "ERROR! Expecting ',': line " + str(i)
                        print line
                        sys.exit(1)
                    if not (int(r2) <= 16) and (int(r2) >= 1):
                        print "ERROR! Expecting 1 <= n <= 16: line " + str(i)
                        print line
                        sys.exit(1)
                    objectCode = objectCode + r1 + r2
                elif (INST[mnemonic][0] == 2):
                    
                    if not ((r1match and r2match) and line[6] == ','):
                        print "ERROR! Expecting valid registers: line " + str(i)
                        print line
                        sys.exit(1)
                    
                    objectCode = objectCode + regs[r1] + regs[r2]
            

             # 3/4 FORMAT INSTRUCTIONS #
            else:
                increment = 3
                if line[4] == "@":
                    increment = 2
                if line[4] == "#":
                    increment = 1
                objectCode = hex(int(objectCode, 16) + increment)[2:].upper()
                
                # === ADDRESS CALCULATION === #
                # PROGRAM COUNTER #
                if re.match("^[0-9A-F]+$", array[i+1][0]):
                    programCounter = array[i+1][0]
                else:
                    j = i
                    while not re.match("^[0-9A-F]+$", array[j+1][0]):
                        j += 1
                    programCounter = array[j+1][0]
                # PROGRAM COUNTER #
                address = ""
                eFlag = False
                xbpe = 0

                if line[2] == "+":
                    xbpe += 1
                    eFlag = True
                if re.match('^[0-9]*$', line[5]):
                    maxValue = 4095
                    if eFlag:
                        maxValue = 1048575
                    if int(line[5]) > maxValue:
                        print "ERROR! Constant too large: line " + str(i)
                        print line
                        sys.exit(1)
                    address =  hex(int(line[5]))[2:].upper()
                else:
                    if mnemonic == "RSUB":
                        address = "000"
                        if eFlag:
                            address = "00000"
                    elif labels.has_key(line[5]):
                        address = labels[line[5]]

                        # Simple addressing mode hiearchy #
                        
                        if (len(address) > 3) and (not eFlag):
                            
                            disp = int(address, 16) - int(programCounter, 16)
                            
                            if (disp > 2047) or (disp < -2048):
                                if baseExist:
                                    disp = int(address, 16) - int(baseAddress, 16)
                                    if ((disp > 2047) or (disp < -2048)) and (not eFlag):
                                        # SIC mode #
                                        if int(address, 16) > 32767:
                                            print "Error! Address too long: line " + str(i)
                                            print line
                                            sys.exit(1)
                                        else:
                                            objectCode = hex(int(objectCode, 16) - 3)[2:].upper()
                                    else:
                                        address = "%03X" % (disp & 0xfff)
                                        #address = hex(int(disp, 16))[2:].upper()
                                        xbpe += 4
                                else:
                                    # SIC mode #
                                    if int(address, 16) > 32767:
                                        print "Error! Address too long: line " + str(i)
                                        print line
                                        sys.exit(1)
                                    else:
                                        objectCode = hex(int(objectCode, 16) - 3)[2:].upper()
                            else:
                                address = "%03X" % (disp & 0xfff)
                                #address = hex(int(disp, 16))[2:].upper()
                                xbpe += 2
                        #address = address                

                    else:
                        print "Error! Nonexistant label: line " + str(i)
                        print line
                        sys.exit(1)

                

                if line[6] == "," and line[7].upper() == "X":
                    xbpe += 8
                maxlength = 3
                if eFlag:
                    maxlength = 5
                while len(address) < maxlength:
                    address = '0' + address
                if len(objectCode) < 2:
                    objectCode = '0' + objectCode
                
                objectCode = objectCode + hex(xbpe)[2:].upper() + address
                
        line.append(objectCode)
        if (mnemonic == "RESB") or (mnemonic == "RESW"):
            entry = line[0], "===="
            newArray.append(entry)
        elif objectCode != "":
            entry = line[0], objectCode
            newArray.append(entry)

    
    
    
    newArray.append(endOp)
    return array, newArray
        

        
    # ======== The Mega Loop ======== #


# =================== #
# =======MAIN======== #
# =================== #
	
def main():
    

    array = readfile(sys.argv[1])
    firstArray, startIndex = firstpass(array)
    secondArray, asmArray = secondpass(firstArray, startIndex)
    

    f = open(sys.argv[2], 'w')
    f.write('H')
    while len(asmArray[0]) < 6:
        asmArray[0] = asmArray[0] + ' '
    f.write(asmArray[0])
    f.write(asmArray[1].decode('hex'))
    while len(asmArray[2]) < 6:
        asmArray[2] = '0' + asmArray[2]
    f.write(asmArray[2].decode('hex'))
    i = 3
    newRecord = True
    length = 0
    b = ""
    
    while True:
        
        if i == len(asmArray) - 1:
            break
        address, objcode = asmArray[i]
        if newRecord:
            f.write('T')
            while len(address) < 6:
                address = '0' + address
            f.write(address.decode('hex'))
            newRecord = False
        if objcode == "====":
            while objcode == "====":
                i = i + 1
                if i == len(asmArray) - 1:
                    break
                address, objcode = asmArray[i]
            length = hex(length)[2:].upper()
            f.write(length.decode('hex'))
            f.write(b.decode('hex'))
            print b
            length = 0
            b = ""
            newRecord = True
        else:
            length = length + len(objcode)/2
            if length > 64:
                while length < 64:
                    b = b + objcode[:2]
                    objcode = objcode[2:]
                    length = length + 1
                length = hex(length)[2:].upper()
                f.write(length.decode('hex'))
                f.write(b.decode('hex'))
                print b
                length = 0
                b = objcode
                newRecord = True
                i = i + 1
            else:
                b = b + objcode
                i = i + 1
        #asdf            
    
    
    #f.write('48'.decode('hex'))
    f.write('E')
    i = len(asmArray)-1
    endOp = hex(int(asmArray[i], 16))[2:].upper()
    while len(endOp) < 6:
        endOp = '0' + endOp
    f.write(endOp.decode('hex'))
    f.close()

    #for line in secondArray:
        #print line
    
    
if __name__ == "__main__":
    main()
	

