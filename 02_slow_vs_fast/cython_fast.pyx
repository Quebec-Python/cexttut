def cython_fast(l):
    cdef long result, index, number
    result = 0
    for index in range(len(l)):
        number = l[index]
        result += index * number 
    return result
