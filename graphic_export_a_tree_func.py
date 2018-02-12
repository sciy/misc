#将gbdt的子树导出为图片

def export_an_estimator(gbdt, nam, featrs, i=-1):
    # export gbdt.estimators_[i,0] as a picture
    # nam is used to save the picture as a file
    # featrs is a list of feature name to show:
    # export_an_estimator(aModel, 'aName', aData.columns.tolist())
    #
    from sklearn import tree
    from subprocess import check_call
    #from IPython.display import Image as PImage
    #from PIL import Image, ImageDraw, ImageFont
    ##...
    if i >= 0:
        estree = gbdt.estimators_[i, 0]
        filenam = "tree_{}_{}".format(nam, i)
        with open(filenam+".dot", 'w') as f: # graph exporting
            tree.export_graphviz(
                estree,
                rounded = True,
                filled = True,
                out_file = f,
                feature_names = featrs,
                )
        check_call(['dot', '-Tjpg', filenam+'.dot', '-o', filenam+'.jpg'])
        return
    #..
    for i,estree in enum(gbdt.estimators_):
        estree = estree[0]
        filenam = "tree_{}_{}".format(nam, i)
        with open(filenam+".dot", 'w') as f: # graph exporting
            filenam = "tree_{}_{}".format(nam, i)
            tree.export_graphviz(
                estree,
                rounded = True,
                filled = True,
                out_file = f,
                feature_names = featrs,
                )
        check_call(['dot', '-Tjpg', filenam+'.dot', '-o', filenam+'.jpg'])
