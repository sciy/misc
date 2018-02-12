def deci_path(gbdt, data):
    # gbdt is the fitted GBDT for binary classifier only!
    # data are samples to predict/show
    #
    lidx = gbdt.apply(data)[:,:,0] # leaves index
    root_score = gbdt.init_.predict(data)[0,0] # same for all records
    #
    if len(shape(lidx)) > 2:
        print('Error leaves shape in calling deci_path()')
        return -1
    #
    all_scores = zeros(shape(lidx)+array([0,1])) # add a col to put root_sorce
    all_scores[:,0] = root_score
    #
    for i,iTree in enumerate(gbdt.estimators_): # loop for estimators:
        vals = iTree[0].tree_.value.ravel()     # val of all nodes of this tree
        #leaf_mask = (iTree[0].tree_.children_left == -1) # TREE_LEAF == -1
        #w_i = iTree[0].tree_.value[leaf_mask, 0, 0] # here we can obtain the values of leaves
        #print(i,w_i)                   # but the appy() return node index of the whole tree!!
        for j in range(shape(lidx)[0]): # loop for examples:
            all_scores[j,i+1] = vals[int(round(lidx[j,i]))]*gbdt.learning_rate
    '''
    fy = gbdt.decision_function(data)
    for j in range(shape(lidx)[0]):
        print('This is the example %d:'%j)
        print('\taccess these leaves of each sub-tree:', lidx[j])
        print('\tget the following values from leaves:', all_scores[j])
        print('\tsum(leaf values) = deci_func({})?: {}'.format(fy[j], sum(all_scores[j])-fy[j]<1e-6))
    '''# lidx[j]: leaves accessed in processing record_j, all_scores[j]: init_score and corresponding scores
    return all_scores, lidx
