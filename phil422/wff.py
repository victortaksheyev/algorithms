connectives = ['v', '>', '&', '~']
wff = input("Enter a formula: ")


indexes = []
# string = a v b v c

#finds first operator within the wff and returns its index
def findOperator(wff):
    for i in range(len(wff)):                            # looping through all chars in wff
        if set([i]) & set(indexes):                      # if operator has already been used
            # print("internsection")
            continue
        else:                                           # if operator has not been usedl
            for j in range(len(connectives)):           # looping through all of the connectives
                if wff[i] == connectives[j]:            # if the wff contains the connective
                    indexes.append(i)                   # keeps track of which operators have already been used
                    return i

# returns a subWff
def subWff(mainwff, index):
    subW = ''
    start = 0                                       # index at which wff start
    end = 0                                         # index at which wff ends
    if index >= 0 and index < len(mainwff):          # if index is in-bounds

        # if operator is negation
        # ...
        # ...

        # need to create a string that contains character before the index to the character after the index
        # take into consideration the presence of negation, treat it as part of wff
        if index - 2 >= 0:
            if mainwff[index-2] == '-':           # if the index is equal to negation
                subW = mainwff[(index-2):index+1]   #include negation
                start = index - 2
            else:
                subW = mainwff[(index-1):index+1]   # no negation
                start = index - 1
        elif index - 1 >= 0:
            subW = mainwff[index-1:index+1]   # no negation
            start = index - 1
        
        if index + 2 < len(mainwff):
            if mainwff[index+1] == '-':
                subW += mainwff[index+1:index+3]
                end = index+2
            else:
                subW += mainwff[index+1]
                end = index+1
        elif index+1 < len(mainwff):
            subW += mainwff[index+1]
            end = index+1
    return (subW, start, end)

# params:   main wff (user entered)
#           start of the subwff
#           end of 
def rejoinWff(wff, subwff, start, end):
    returnwff = subWff
    # joining from the left
    if start != 0:
        # ex)   wff     =     b v c
        #       subwff  =     b v c
        returnwff = wff[0:start] + returnwff
    # joining from the right
    if end != len(wff) - 1:
        returnwff = returnwff + wff[end+1:]
    return returnwff


# takes in a string to add opening and closing parenths to
def addP(wff):
    indexes[-1] += 1
    return '('+wff+')'

# * expands the tuple
print("Index",indexes)
# print(addParenths(subWff(wff, findOperator(wff))))
print("Index",indexes)

subWff, start, end = subWff(wff, findOperator(wff))
subWff = addP(subWff)

print(rejoinWff(wff, addP(subWff), start, end))



