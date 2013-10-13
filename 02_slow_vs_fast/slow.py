def slow1(l):
    result = 0
    for index, x in enumerate(l):
        result += index * x
    return result

def slow2(l):
    result = 0
    for index in range(len(l)):
        result += index * l[index]
    return result
