from scipy.stats import ks_2samp
import numpy as np
# [1] https://docs.scipy.org/doc/scipy-0.14.0/reference/generated/scipy.stats.kstest.html
# [2] https://docs.scipy.org/doc/scipy/reference/generated/scipy.stats.ks_2samp.html
# [3] https://stackoverflow.com/questions/10884668/two-sample-kolmogorov-smirnov-test-in-python-scipy
#  If the K-S statistic is small or the p-value is high, then
#     we cannot reject the hypothesis that the distributions of the two samples are the same.

def plot_ks_curves_old(data1, data2, fnam=''):
    # stolen from [2]
    data1 = np.sort(data1)
    data2 = np.sort(data2)
    n1 = data1.shape[0]
    n2 = data2.shape[0]
    # ...
    data_all = np.sort(np.concatenate([data1, data2]))
    cdf1 = np.searchsorted(data1, data_all, side='right') / (1.0*n1)
    cdf2 = np.searchsorted(data2, data_all, side='right') / (1.0*n2)
    '''
        In [x]: np.searchsorted([1, 2, 2.9, 3.1, 4, 4.5, 5, 8.5], 3)
        Out[x]: 3
    '''
    d = np.max(np.absolute(cdf1 - cdf2))  # this is the KS value
    #
    plt.plot( 1.0*array(range(n1+n2))/(n1+n2), cdf1 )
    plt.plot( 1.0*array(range(n1+n2))/(n1+n2), cdf2 )
    plt.plot( 1.0*array(range(n1+n2))/(n1+n2), abs(cdf1-cdf2) )
    plt.plot([0, 1], [0, 1], 'k--')
    plt.xlim([0.0, 1.0]); plt.ylim([0.0, 1.0])
    plt.xlabel('normed score'); plt.ylabel('cumulative probablity')
    #
    font = {'family': 'serif',
            'color':  'darkred',
            'weight': 'normal',
            'size': 10,
            }
    plt.text(0.7, 0.35, 'KS={}'.format(round(d,3)), fontdict=font)
    #
    if fnam != '':
        plt.savefig(fnam)
        clf()
    else:
        show()
    return d


def plot_ks_curves(data1, data2, fnam=''):
    data1 = np.sort(data1)
    data2 = np.sort(data2)
    n1 = data1.shape[0]
    n2 = data2.shape[0]
    data_all = np.sort(np.concatenate([data1, data2]))
    # ...
    k1, k2 = 1., 1.
    cursor = linspace( k1*min(data_all), k2*max(data_all), num=100 )
    cdf1 = np.searchsorted(data1, cursor, side='right') / (1.0*n1)
    #cursor2 = linspace( min(data2), max(data2), num=100 )
    cdf2 = np.searchsorted(data2, cursor, side='right') / (1.0*n2)
    '''
        In [x]: np.searchsorted([1, 2, 2.9, 3.1, 4, 4.5, 5, 8.5], 3)
        Out[x]: 3
    '''
    d = np.max(np.absolute(cdf1 - cdf2))  # this is the KS value
    #
    plt.plot( 0.01*array(range(100)), cdf1 )
    plt.plot( 0.01*array(range(100)), cdf2 )
    plt.plot( 0.01*array(range(100)), abs(cdf1-cdf2) )
    #plt.plot([0, 1], [0, 1], 'k--')
    plt.xlim([0.0, 1.0]); plt.ylim([0.0, 1.0])
    plt.xlabel('normed score'); plt.ylabel('cumulative probablity')
    #
    font = {'family': 'serif',
            'color':  'darkred',
            'weight': 'normal',
            'size': 10,
            }
    plt.text(0.7, 0.35, 'KS={}'.format(round(d,3)), fontdict=font)
    #
    if fnam != '':
        plt.savefig(fnam)
        clf()
    else:
        show()
    return d

np.random.seed(1234567890)
x = np.random.normal(0, 1, 1000)
y = np.random.normal(0, 1, 1000)
z = np.random.normal(1.1, 0.9, 1000)

ks_2samp(x, y) #Ks_2sampResult(statistic=0.022999999999999909, pvalue=0.95189016804849647)
ks_2samp(x, z) #Ks_2sampResult(statistic=0.41800000000000004, pvalue=3.7081494119242173e-77)

plot_ks_curves(x, y)
plot_ks_curves(x, z)
