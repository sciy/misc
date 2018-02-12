# hist partition is also useful...
# divide se into k partitions, return partition edges (len=k+1)
def equilibrium_partition(se, k=5):
    if k<=1:
        print('cannot divide the data to {} partitions'.format(k))
        return -1
    r = 1.0*array(range(k+1))/k # ratios
    b = se.dropna().describe(percentiles=r)[4:5+k].values.tolist()
    b = sort(list(set(map(lambda x: np.round(x,7), list(b)))))  # remove extra items
    if len(b)>2:
        b[0], b[-1] = -inf, inf
        return b
    else:
        print('cannot divide the given data! too dense?')
        return -1


# calculate population stabillity index
# ref: https://github.com/atselikov/PopulationStabilityIndex-on-PySpark
def calc_PSI(expected, actual, bin_num):
    # e.g., expected is obtained from train set;  actual is from verification/test set.
    bin_edg = equilibrium_partition(expected, bin_num) #must divide according `expected`
    eInum = np.histogram(expected, bins=bin_edg, density=True)[0] # item numbers, bin edges
    aInum = np.histogram(actual, bins=bin_edg, density=True)[0] # divied the actual with `expected` dataset edges
    eInum /= sum(eInum) # density in hist does not work sometimes?
    aInum /= sum(aInum)
    #
    psi_tot=0
    for j in range( min(len(eInum), len(aInum)) ):
        aInumJ = aInum[j]
        eInumJ = eInum[j]
        if (aInumJ>0) and (eInumJ>0):
            psi_cut = (eInumJ-aInumJ)*np.log(eInumJ/aInumJ)
            psi_tot += psi_cut
    print('PSI: calc_psi with {} partitions is {}.'.format(bin_num, psi_tot))
    return np.round(psi_tot,7)

equilibrium_partition(pd.DataFrame({'exp':lrm_train_predprob})['exp'], 20) #usage
'''  yet another example:
In [x]: x = person_train_score
In [x]: t = equilibrium_partition(pd.DataFrame({'person':x}))
Out[x]: array([-inf, -2.0692145, -2.0566163, -2.0484575, -2.0412977, inf])
In [x]: y = np.searchsorted(t,x) # 1 <= x <= 5
Out[x]: array([2, 5, 5, ..., 5, 3, 2], dtype=int64)
'''
