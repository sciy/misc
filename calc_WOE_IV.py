def calc_WOE_IV(df, col, target):
    ''' http://blog.csdn.net/mr_tyting/article/details/75212250
        :dframe df    : dataframe containing col and target columns
        :string col   : categorical indicator (feature)  to calculate WOE and IV
        :string target: good/bad indicator (feature)
        :return: WOE and IV in a dictionary
    '''
    total = df.groupby([col])[target].count()
    total = pd.DataFrame({'total': total})
    bad = df.groupby([col])[target].sum()
    bad = pd.DataFrame({'bad': bad})
    regroup = total.merge(bad, left_index=True, right_index=True, how='left')
    regroup.reset_index(level=0, inplace=True)
    N, B = sum(regroup['total']), sum(regroup['bad'])
    regroup['good'], G = regroup['total']-regroup['bad'], N-B
    #
    regroup['bad_pcnt'] = regroup['bad'].map(lambda x: x*1.0/B)
    regroup['good_pcnt'] = regroup['good'].map(lambda x: x*1.0/G)
    regroup['WOE'] = regroup.apply(lambda x: np.log(x.good_pcnt*1.0/x.bad_pcnt), axis=1)
    WOE_dict = regroup[[col,'WOE']].set_index(col).to_dict(orient='index')
    for k, v in WOE_dict.items():
        WOE_dict[k] = v['WOE']
    IV = regroup.apply(lambda x: (x.good_pcnt-x.bad_pcnt)*np.log(x.good_pcnt*1.0/x.bad_pcnt), axis = 1)
    IV = sum(IV)
    return {"WOE":WOE_dict, 'IV':IV}
