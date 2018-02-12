def hist_part(data, bins='auto', dens=False):
    n, b = np.histogram(data, bins=bins, density=dens) # item numbers, bin edges
    b = sort(list(set(map(lambda x: np.round(x,7), b)))) # remove extra items
    if len(b)>2:
        b[0], b[-1] = -inf, inf
    else:
        print('cannot divide the given data! too dense?')
        return -1
    return np.histogram(data, bins=b, density=dens) # item numbers, bin edges


# calculate population stabillity index 
# ref: https://github.com/atselikov/PopulationStabilityIndex-on-PySpark
def calc_PSI(expected, actual, bins='auto'):
    eInum, eBedg = hist_part(expected, bins=bins, density=True) # item numbers, bin edges
    # divied the actual with the expected edges, aBedg would= eBedg:::
    aInum, aBedg = hist_part(actual, bins=eBedg, density=True)
    #
    eInum /= sum(eInum) # density in hist does not work sometimes?
    aInum /= sum(aInum)
    #
    psi_tot=0
    for j in range( min(len(eInum), len(aInum)) ):
        aInumJ = aInum[j]
        eInumJ = eInum[j]
        if (aInumJ>0) and (eInumJ>0):
            psi_cut  = (eInumJ-aInumJ)*np.log(eInumJ/aInumJ)
            psi_tot += psi_cut
    print('PSI: calc_psi with {} partitions is {}.'.format(bin_num, psi_tot))
    return np.round(psi_tot,7)
