wff = "a>b>c>d"
# wff = "a"
wff2 = "a"


# for each connective
connectives = '>'

# returns index of wff
def findConnective(wff, indexes):
    if (len(wff) == 1):
        return -1                                   # it's an atomic
    for i in range(len(wff)):                       # looping through all chars in wff
        if set([i]) & set(indexes):                     # if operator has already been used
            continue
        else:                                           # if operator has not been usedl
            for j in range(len(connectives)):           # looping through all of the connectives
                if wff[i] == connectives[j]:            # if the wff contains the connective
                    indexes.append(i)                   # keeps track of which operators have already been used
                    return i

# returns number of connectives
def numConnectives(wff):
    count = 0
    for c in wff:
        if c == connectives:
            count += 1
    return count

# for i in range(numConnectives(wff)):


# returns what's on left of operator
def createLeft(wff, opIndex):
    # print("left", opIndex)
    if opIndex == -1:
        return wff          # return the atomic
    else:
        return wff[:opIndex]

# returns what's on right of operator
def createRight(wff, opIndex):
    # print("right",opIndex)
    if opIndex == -1:
        return wff          # return the atomic
    else:
        return wff[opIndex+1:]

# def rec(wff, left, right, opIndex):
#     if numConnectives(left) == 0 and numConnectives(right) == 0:
#         return left; # return atomic
#     if numConnectives(left) == 0:
#         return left
#     if numConnectives(right) == 0:
#         return right
#     else:
#         print("Left", numConnectives(left))
#         print("Right", numConnectives(left))
#         # LopIndex = findConnective(left)
#         # LnewL = createLeft(left, LopIndex)
#         # LnewR = createRight(left, LopIndex)
#         # RopIndex = findConnective(right)
#         # RnewL = createLeft(right, RopIndex)
#         # RnewR = createRight(right, RopIndex)
#         # return ("("+ rec(left, LnewL, LnewR, LopIndex) + ")" + wff[opIndex] + "(" + rec(right, RnewL, RnewR, RopIndex) + ")")

# def rec(wff):
#     indexes = []    # list storing indexes of connectives used
#     if len(wff) == 1:
#         return wff
#     else:
#         opIndex = findConnective(wff, indexes)
#         # print(opIndex)
#         left = createLeft(wff, opIndex)
#         right = createRight(wff, opIndex)
#         return ("("+rec(left)+ wff[opIndex] +rec(right)+")")

def rec(wff):
    # indexes = []    # list storing indexes of connectives used
    ind = []    # list storing indexes of connectives used
    if len(wff) == 1:
        return wff
    else:
        for i in range(numConnectives(wff)):
            opIndex = findConnective(wff, ind)  # operator index
            left = createLeft(wff, opIndex)     # left formula
            right = createRight(wff, opIndex)   # right formula
            leftW = rec(left)
            rightW = rec(right)
            # print(leftW + rightW)
            return("(" + str(leftW)+ wff[opIndex] + str(rightW) + ")")
            print("(" + str(leftW) + wff[opIndex] + str(rightW)+")")
        # return ("("+left+ wff[opIndex] +right+")")

indexes = []
for i in range(numConnectives(wff)):
    opIndex = findConnective(wff, indexes)
    # print(indexes)
    left = createLeft(wff, opIndex)
    right = createRight(wff, opIndex)
    # if (rec(left) == None):

    #     print("left is none")
    #     rec(left)
    # if (rec(right) == None):
    #     print("right is none")
    # str(rec(left)) + str(rec(right))
    print("(" + str(rec(left)) + wff[opIndex] + str(rec(right)) + ")")


# A>B>C>D

# ()()()
# ()((A>B)>C)
# (A>(B>C))()
# ((A>B)>C)()
# (()())
# ((()))
