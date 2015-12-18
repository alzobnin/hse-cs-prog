def append(res, elem):
    if res[-1] != elem:
        res.append(elem)

def soundex(word):
    res = []
    res.append(word[0])
    for c in word[1:]:
        if c in "bfpv":
            append(res, "1")
        elif c in "cgjkqsxz":
            append(res, "2")
        elif c in "dt":
            append(res, "3")
        elif c in "l":
            append(res, "4")
        elif c in "mn":
            append(res, "5")
        elif c in "r":
            append(res, "6")
    res = res[:4]
    while len(res) != 4:
        res.append("0")
    return "".join(res)

word = input()
print(soundex(word))

