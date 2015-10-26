#  !/usr/bin/env python
#  -*- coding:utf-8 -*-

# http://www.cnblogs.com/stuarts/archive/2010/03/09/1681994.html

from pylab import *
import numpy as np

sampleTime = 0.4 # x seconds totally
sampleCount = 2048.0 # x sample points in total

x = np.linspace(0, sampleTime, sampleCount)
y = np.sin(2*pi*250*x) + 0.5*np.sin(2*pi*500*x) + 0.3*np.sin(2*pi*1000*x)
freqLine = 800
ffty = np.fft.fft(y)[0:freqLine] # rfft can be used to calculate the fft since the data is real values
fftx = np.linspace(0, freqLine/sampleTime, freqLine)

subplot(211)
plot(x,y)
xlabel('time(s)')
ylabel('amplitude')
title('time domain graph')

subplot(212)
plot(fftx, abs(ffty)) # OR abs(ffty)**2 for power spectrum
xlabel('frequency(Hz)')
ylabel('amplitude')
title('frequency domain graph')

show()
