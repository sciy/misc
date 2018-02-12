import numpy as np
from sklearn.metrics import roc_curve
from sklearn.metrics import auc

y = np.array([1,1,2,2])
pred = np.array([0.1, 0.4, 0.35, 0.8])
fpr, tpr, thresholds = roc_curve(y, pred, pos_label=2)
#fpr             # array([ 0. ,  0.5,  0.5,  1. ])
#tpr             # array([ 0.5,  0.5,  1. ,  1. ])
#thresholds      # array([ 0.8 ,  0.4 ,  0.35,  0.1 ])
auroc = metrics.auc(fpr, tpr)

# Plot ROC curve
plt.plot(fpr, tpr, label='ROC curve (area = %0.3f)' % auroc)
plt.plot([0, 1], [0, 1], 'k--')  # random predictions curve
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.0])
plt.xlabel('False Positive Rate or (1 - Specifity)')
plt.ylabel('True Positive Rate or (Sensitivity)')
plt.title('Receiver Operating Characteristic')
plt.legend(loc="lower right")
show()
  
# http://blog.csdn.net/u010159842/article/details/52924755
# https://stackoverflow.com/questions/34564830/roc-curve-with-sklearn-python
