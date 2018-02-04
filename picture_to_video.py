#  !/usr/bin/env python
#  -*- coding:utf-8 -*-

import glob as gb
import cv2

base = '/media/mw/Seagate_Drive/1/'
dirlist = os.listdir(base)

x,y = 4800,3600
videoWriter = cv2.VideoWriter('collect.mp4', cv2.VideoWriter_fourcc(*'MJPG'), 0.5, (x,y))
print(datetime_str())

for dirname in sort(dirlist):
    if dirname[0] != '2': continue
    print(dirname)
    thisdir1 = base + dirname + '/*.jpg'
    thisdir2 = base + dirname + '/*.JPG'

    for path in gb.glob(thisdir1):
        img = cv2.imread(path)
        img = cv2.resize(img,(x,y))
        videoWriter.write(img)

    for path in gb.glob(thisdir2):
        img = cv2.imread(path)
        img = cv2.resize(img,(x,y))
        videoWriter.write(img)

videoWriter.release()
print(datetime_str())
print('DONE!')
