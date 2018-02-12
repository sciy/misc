#Model persistence

#After training a scikit-learn model, it is desirable to
# have a way to persist the model for future use without having to retrain. 
# http://scikit-learn.org/stable/modules/model_persistence.html
>>> import pickle
>>> s = pickle.dumps(clf)
>>> clf2 = pickle.loads(s)
>>> clf2.predict(X[0:1]) # array([0])
>>> y[0] #0

#In the specific case of the scikit, it may be more interesting to use joblib’s replacement of pickle,
#   which is more efficient on objects that carry large numpy arrays internally as is often the case
#   for fitted scikit-learn estimators, but can only pickle to the disk and not to a string.
#https://www.zhihu.com/question/27187105
>>> from sklearn.externals import joblib
>>> joblib.dump(clf, 'filename.pkl')
>>> clf = joblib.load('filename.pkl')

#若此语句将产生大量的模型文件
#http://blog.csdn.net/mach_learn/article/details/40430469
#save model
>>> joblib.dump(clf,'../../data/model/randomforest.pkl',compress=3)
#load model to clf
>>> clf = joblib.load('../../data/model/randomforest.pkl')
