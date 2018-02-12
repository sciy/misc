# In gradient-boosting there is actually one weight assigned to each terminal region (aka leaf).
# Those estimates are stored directly in trees and updated during the fitting of the gradient boosting model.
# https://github.com/scikit-learn/scikit-learn/blob/master/sklearn/ensemble/gradient_boosting.py#L197
# understanding the gradient boosting tree in fitted model on stackoverflow.com

for i in range(nEst):
    tree = gbdt.estimators_[i, 0].tree_
    leaf_mask = (tree.children_left == -1) # TREE_LEAF  # TREE_LEAF == -1
    w_i = tree.value[leaf_mask, 0, 0]
    print(i, w_i)
