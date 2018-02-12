#pip install pandas
#csv其实就是逗号分隔的文本而已

import pandas as pd
df = pd.read_csv('xxx.csv')
df.query('BBB=="ok"').loc[:, 'AAA'].to_csv('new_xxx.csv')
