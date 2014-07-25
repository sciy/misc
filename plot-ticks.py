# !/usr/bin/env python
# -*- coding:utf-8 -*-

# http://blog.csdn.net/rumswell/article/details/6571005
# http://blog.csdn.net/rumswell/article/details/9862089
# http://sebug.net/paper/books/scipydoc/matplotlib_intro.html

x = arange(0, 4*pi, 0.01)
y = sin(x)
figure(figsize=(8,4))
plot(x, y)
ax = gca()
show()

def pi_formatter(x, pos):#{{{
    """
    将数值转换为以pi/4为单位的刻度文本
    """
    m = round(x / (pi/4))
    n = 4
    if m%2==0: m, n = m/2, n/2
    if m%2==0: m, n = m/2, n/2
    if m == 0:
        return "0"
    if m == 1 and n == 1:
        return "$\pi$"
    if n == 1:
        return r"$%d \pi$" % m
    if m == 1:
        return r"$\frac{\pi}{%d}$" % n
    return r"$\frac{%d \pi}{%d}$" % (m,n)#}}}

# 设置两个坐标轴的范围
ylim(-1.5,1.5)
xlim(0, max(x))

# 设置图的底边距
subplots_adjust(bottom = 0.15)

grid() #开启网格
ax.xaxis.grid(True, which='major') #x坐标轴的网格使用主刻度
ax.yaxis.grid(True, which='minor') #y坐标轴的网格使用次刻度

# 主刻度为pi/4
ax.xaxis.set_major_locator( MultipleLocator(pi/4) )

# 主刻度文本用pi_formatter函数计算
ax.xaxis.set_major_formatter( FuncFormatter( pi_formatter ) )

# 副刻度为pi/20
ax.xaxis.set_minor_locator( MultipleLocator(pi/20) )

# 另一种方法：
# ax=gca()
# ax.set_xticks(np.linspace(0,1,9))
# ax.set_xticklabels( ('275', '280', '285', '290', '295',  '300',  '305',  '310', '315'))
# ax.set_yticks(np.linspace(0,1,8))
# ax.set_yticklabels( ('0.60', '0.65', '0.70', '0.75', '0.80','0.85','0.90','0.95'))

# 设置刻度文本的大小
for tick in ax.xaxis.get_major_ticks(): tick.label1.set_fontsize(20)
for tick in ax.yaxis.get_major_ticks(): tick.label1.set_fontsize(20)
