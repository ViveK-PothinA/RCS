import cv2
import numpy as np

img = cv2.imread('4.jpg',0)
ret,thresh = cv2.threshold(img,127,255,0)
#contours,hierarchy = cv2.findContours(thresh, 1, 2)
_,contours,hierarchy = cv2.findContours(thresh,cv2.RETR_LIST,cv2.CHAIN_APPROX_SIMPLE)
cnt = contours[0]
M = cv2.moments(cnt)
print M

rect = cv2.minAreaRect(cnt) 
box = cv2.boxPoints(rect) 
box = np.int0(box)
img = cv2.drawContours(img,[box],0,(0,0,255),2)

cv2.imshow('image', img)
while(1):
  k = cv2.waitKey(0)
  if(k == 27):
    break
 
cv2.destroyAllWindows()
