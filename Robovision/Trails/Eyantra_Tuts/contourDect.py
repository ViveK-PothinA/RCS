import numpy as np 
import cv2
#Credits for shapes
crdtri = 0
crdrect = -1
crdcir = 0
crdhex = -2

'''
#Video capture
cap = cv2.VideoCapture(0)
#Frame reading
ret, frame = cap.read()
img = frame
#video loop
while(1):       #Ident the remaining part
'''
#image readiing 
img = cv2.imread('V:/Works and Stuff/Sophomore 16-17/RCS/Robovision/Trails/1.png')
#conversion to gray and calc thresholds
gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
ret, thresh = cv2.threshold(gray,254,255,0)
_, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
#no. of contours
print len(contours)
#shape lists initialisation
tri = []
cir = []
rect = []
hexa = []
#find out contours of the shapes and identify the shapes
for i in range(0,8):
	area = cv2.contourArea(contours[i])
	if area < 10000 and area > 1000:				#Edit these accordingly
		cv2.drawContours(img,contours,i,(0,255,0),3)
		cv2.imshow('img',img)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		approx = cv2.approxPolyDP(contours[i],0.04*cv2.arcLength(contours[i],True),True)
		x = len(approx)
		print x
		if x == 3:					#appending shapes
			tri.append(i)
		elif x == 4:
			rect.append(i)
		elif x == 6:
			hexa.append(i)			#Our bot's shape
		else:
			cir.append(i)	 
print tri
print rect
print hexa
print cir

