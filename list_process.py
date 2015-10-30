def outter_flatten(lst):
    """only flat the outter level"""
    new_lst = []
    for x in lst:
        if isinstance(x, list):
            for y in x: new_lst.append(y)
        else:
            new_lst.append(x)
    return new_lst

# In [-]: a
# Out[-]: [[[1, 2, 3], [1, 2, 3]], [[4, 5, 6], [4, 5, 6]], [[7, 8, 9], [7, 8, 9]]]
# In [-]: shape(a)
# Out[-]: (3, 2, 3)
# In [-]: outter_flatten(a)
# Out[-]: [[1, 2, 3], [1, 2, 3], [4, 5, 6], [4, 5, 6], [7, 8, 9], [7, 8, 9]]
# In [-]: shape(outter_flatten(a))
# Out[-]: (6, 3)
# #-----------
# In [-]: len(shape(a))
# Out[-]: 3
# In [-]: a=outter_flatten(a)
# In [-]: len(shape(a))
# Out[-]: 2
# In [-]: a=outter_flatten(a)
# In [-]: len(shape(a))
# Out[-]: 1
# In [-]: a
# Out[-]: [1, 2, 3, 1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 7, 8, 9]

def equally_divide(lst, segment_len):
    if len(lst)%segment_len != 0: lst = lst[:len(lst)/segment_len*segment_len]
    return [lst[i:i+segment_len] for i in range(0, len(lst), segment_len)]

# In [-]: a
# Out[-]: [1, 2, 3, 1, 2, 3, 4, 5, 6, 4, 5, 6, 7, 8, 9, 7, 8, 9]
# In [-]: a=equally_divide(a,3)
# Out[-]: [[1, 2, 3], [1, 2, 3], [4, 5, 6], [4, 5, 6], [7, 8, 9], [7, 8, 9]]
# In [-]: a=equally_divide(a,2)
# Out[-]: [[[1, 2, 3], [1, 2, 3]], [[4, 5, 6], [4, 5, 6]], [[7, 8, 9], [7, 8, 9]]]
# In [-]: shape(a)
# Out[-]: (3, 2, 3)

# array <-> list
# In [-]: a=[1,2,3]
# In [-]: array(a)
# Out[-]: array([1, 2, 3])
# In [-]: list(array(a))
# Out[-]: [1, 2, 3]

def min_N(a, n):
    if not isinstance(a, list): return False
    if n>len(a): n=len(a)
    b = a[:]
    for i in range(len(a)): b[i] = (b[i], i)
    b.sort(key = lambda x: x[0], reverse = False)
    return [b[i][0] for i in range(n)], [b[i][1] for i in range(n)]

def max_N(a, n):
    if not isinstance(a, list): return False
    if n>len(a): n=len(a)
    b = a[:]
    for i in range(len(a)): b[i] = (b[i], i)
    b.sort(key = lambda x: x[0], reverse = True)
    return [b[i][0] for i in range(n)], [b[i][1] for i in range(n)]

#In [-]: a=[13,4,23,9,111]
#In [-]: max_N(a, 3)
#Out[-]: ([111, 23, 13], [4, 2, 0])
#
#In [-]: min_N(a, 3)
#Out[-]: ([4, 9, 13], [1, 3, 0])
#
#In [-]: min_N(a, 33)
#Out[-]: ([4, 9, 13, 23, 111], [1, 3, 0, 2, 4])
