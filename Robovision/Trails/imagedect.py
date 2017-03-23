import cv2
import numpy as np
#reading the image
img = cv2.imread('4.jpg',1)
#converting the image into HSV
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

#detected upper and lower range using converter.py
#lower_range = np.array([110,100,100], dtype=np.uint8)
#upper_range = np.array([130,255,255], dtype=np.uint8)
#creating a mask for the image
#mask = cv2.inRange(hsv, lower_range, upper_range)
 
lower_range1 = np.array([110,100,100], dtype=np.uint8)
upper_range1 = np.array([130,255,255], dtype=np.uint8)
lower_range2 = np.array([0,0,0], dtype=np.uint8)
upper_range2 = np.array([140,50,100], dtype=np.uint8)
mask1 = cv2.inRange(hsv, lower_range1, upper_range1)
mask2 = cv2.inRange(hsv, lower_range2, upper_range2)
print(type(mask2))
#mask = mask1+mask2

#print(mask2[0])
cv2.imshow('mask1', mask1)
cv2.imshow('mask2',mask2)
res = cv2.bitwise_or(mask1,mask1, mask= mask2)
cv2.imshow('mask',res)
while(1):
  k = cv2.waitKey(0)
  if(k == 27):
    break
 
cv2.destroyAllWindows()