connectives = ['v', '>', '&', '~']
wff = input("Enter a formula: ")

indexes = []
psets = 0               #   sets of parentheses
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

# arguments are wff and index of the connective
# returns index of far left paren
def parenLeft(wff, index):
    pcount = 0;
    # count how many parenthesis you see
    while wff[index - 2] != '(':            # while it's not the first closing
        if wff[index - 1] == ")":
            pcount+=1                      # increment the number of parenthesis you've come across
        index -=1                          # move to the left

    # then count backwards in with the closing parentheses
    while pcount != 0:
        if wff[index - 1] == '(':
            pcount-=1                       # we found a match
        index-=1

    return index                             # return where the last paren is as the start

# arguments are wff and index of the connective
# returns index of far right paren
def parenRight(wff, index):
    pcount = 0
    # count how many parenthesis you see
    while wff[index] != ')':            # while it's not the first closing
        if wff[index] == "(":
            pcount+=1
        index += 1
    # return index
    
     # count backwards, considering the closing parenths
    while pcount != 0:
        if wff[index] == ')':
            pcount -= 1
        index += 1

    return index-1                      # figure this out later

# returns a subWff
def subWff(mainwff, index):
    subW = ''
    start = 0                                       # index at which wff start
    end = 0                                         # index at which wff ends
    if index >= 0 and index < len(mainwff):          # if index is in-bounds

        # if operator is negation
        # ...
        # ...
        # if to the left is a parenthesis
        
        if index - 1 >= 0 and mainwff[index-1]==')':
            right = index+1
            left = parenLeft(mainwff, index)
            if mainwff[index+1] == '-':
                right = index+2
            subW = mainwff[left:right+1]
            return (subW, start, end)

        if index + 1 <= len(mainwff) and mainwff[index+1] == '(':
            left = index - 1
            if mainwff[index-2] == '-':
                left = index - 2
            right = parenRight(mainwff, index)
            subW = mainwff[left:right+1]
            return (subW, start, end)
                                
        # check for paren on the right
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
    returnwff = subwff
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
    # indexes[-1] += 1
    return '('+wff+')'

# * expands the tuple
# twff, start, end = subWff(wff, findOperator(wff))
# twff = addP(twff)

# # print(rejoinWff(wff, addP(subWff), start, end))
# rejoined = rejoinWff(wff, twff, start, end)

# print(rejoined)
# print(indexes)

# twff, start, end = subWff(rejoined, findOperator(rejoined))

# print(twff)

# # print(toP)


# test for left paren -------------
# wff: av((avb)vc)vd
# index: 9
# pcount should be 2

# test for right paren -------------
# wff: av(avb)vc
# index: 1
# output should be av(avb)
twff, start, end = subWff(wff, 1)
print(addP(twff))

