#  !/usr/bin/env python
#  -*- coding:utf-8 -*-

# http://www.cnblogs.com/stuarts/archive/2010/03/09/1681994.html

from pylab import *
import numpy as np

nSampleNum = 5120
ncount = 2048.0
df = nSampleNum / ncount
sampleTime = ncount / nSampleNum
freqLine = 800

x = np.linspace(0,sampleTime,ncount)
sinx = np.sin(2*pi*250*x) + 0.5*np.sin(2*pi*500*x) + 0.3*np.sin(2*pi*1000*x)

fft = np.fft.fft(sinx)[0:freqLine]
fftx = np.linspace(0,df*freqLine,freqLine)
subplot(211)
plot(x,sinx)
xlabel('time(s)')
ylabel('amplitude')
title('time domain graph')

subplot(212)
plot(fftx,abs(fft))
xlabel('freqency(Hz)')
ylabel('amplitude')
title('frequency domain graph')

show()
