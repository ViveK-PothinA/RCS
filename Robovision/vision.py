#importing stuff
#from collections import deque
from time import sleep
import serial
import numpy as np
#import argparse
import imutils
import cv2
#ser = serial.Serial('/dev/tty.usbmodem1d11', 9600) # Establish the connection on a specific port
#counter = 32 # Below 32 everything in ASCII is gibberish
#arena colors are black(bl), red(r), green(g), blue(b)
bl = 100		#Don't change this, make sure blacks value is highest
#init credits
r = 1
g = 1
b = 1
tri = 1
rect = 1
cir = 1
#HAVE TO CALIBRATE THESE
bllow = (0,0,0)
blup = (1,0,0)
rlow = (100,0,0)
rup = (130,255,255)
glow = (50,0,0)
gup = (70,255,255)
blow = (71,0,10)
bup = (95,255,255)
#bot colors are magenta(m) and yellow(y)
mlow = (80,100,100)
mup = (80,100,100)
ylow = (25,146,190)
yup = (62,174,250)
#Video init
#camera = cv2.VideoCapture(0)		#change this
#initial calculations
#(grabbed, snap) = camera.read()		#first snap for initial calc
snap = cv2.imread('V:/Works and Stuff/Sophomore 16-17/RCS/Robovision/right.tif')
#camera.release()
#snap = imutils.resize(snap, width = 600)	#resizing the snap
#HSV conversion
hsv = cv2.cvtColor(snap, cv2.COLOR_BGR2HSV)
#masking using color and then identifying shape to calc credits
mask = []
centers = {}
mask.append(cv2.inRange(hsv,bllow,blup)) 
mask.append(cv2.inRange(hsv,rlow,rup))
mask.append(cv2.inRange(hsv,glow,gup))
mask.append(cv2.inRange(hsv,blow,bup))
print type(mask)
for i in range(0,4):		#looping in all masks created
	print i
	#for removing small fluctuations
	mask[i] = cv2.dilate(mask[i], None, iterations=2) 
	mask[i] = cv2.erode(mask[i], None, iterations=2)
	#finding contour
	cnt = cv2.findContours(mask[i].copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
	#cv2.drawContours(snap,cnt,i,(0,255,0),3)
	cv2.imshow('mask'+str(i),mask[i])
	cv2.waitKey(0)
	cv2.destroyAllWindows()
	center = None
	col = 0
	if len(cnt) > 0:
		cnt = max(cnt, key=cv2.contourArea)
		((x, y), radius) = cv2.minEnclosingCircle(cnt)
		M = cv2.moments(cnt)
		center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
		radius = int(radius)
		cv2.circle(snap, (center), radius, (0, 0, 255), -1)
		cv2.imshow('snap',snap)
		cv2.waitKey(0)
		cv2.destroyAllWindows()
		#init color credit
		if i == 1:
			col = r
		elif i == 2:
			col = g
		elif i == 3:
			col = b
		else:
			col = bl
		#finding shape and creating centers dict
		if len(cnt) == 3:
			centers[col*tri] = center
		elif len(cnt) == 4:
			centers[col*rect] = center
		else:
			centers[col*cir] = center
		#i = 0 is the starting rectangle
		if i == 0:
			centers[bl*100] = center
print len(centers)
#Sort centers(desc) and make sure blacks center is highest
desc = sorted(centers.iterkeys(), reverse = True)
for key in range(0,len(desc)-2):
	(srcx, srcy) = centers.values()[key]		#source pts
	(destx,desty) = centers.values()[key+1]		#dest. pts
	#line eq stuff 
	gradx = destx-srcx
	grady = desty-srcy
	Pslope = grady/gradx	#slope of the path
	#video loop
	camera = cv2.VideoCapture(0)
	cam = True
	while (cam):							#Infinte loop
		(grabbed, frame) = camera.read()
		#frame = imutils.resize(frame, width=600)
		#masking hexagons
		my= cv2.inRange(hsv, mlow, mup)
		mm= cv2.inRange(hsv, ylow, yup)
		cntm = cv2.findContours(maskm.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
		cm = None
		cnty = cv2.findContours(masky.copy(), cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[-2]
		cy = None
		if len(cntm)>0 and len(cnty)>0:
			cntm = max(cntm, key=cv2.contourArea)
			cnty = max(cnty, key=cv2.contourArea)
			((x,y),radiusm) = cv2.minEnclosingCircle(cntm)
			mmom = cv2.moments(cntm)
			mgx = int(MM["m10"]/MM["n00"])
			mgy = int(MM["m01"] / MM["m00"])
			radiusm = int(radiusm)
			cv2.circle(frame, (mgx, mgy), radiusm, (0, 0, 255), 10)
			((x,y),radiusy) = cv2.minEnclosingCircle(cnty)
			ymom = cv2.moments(cnty)
			yx = int(MM["m10"]/MM["n00"])
			yy = int(MM["m01"] / MM["m00"])
			radiusy = int(radiusy)
			cv2.circle(frame, (yx, yy), radiusy, (0, 0, 255), 10)
			cv2.imshow('frame',frame)
			cv2.waitKey(0)
			cv2.destroyAllWindows()
			Dslope = (yy-mgy)/(yx-mgx)	#Dynamic Slope of the hexagons
			#substituting pts and comparing, and managing motors
			ys = (gradx*(yy-desty))-(grady*(yx-destx))	#substituting yellow pts
			mgs = (gradx*(mgy-desty))-(grady*(mgx-destx))	#substituting mg pts
			if ys>0 and mg<0:
				print("Forward")
				#call forward
			elif ys>0 and mg>0:
				#call right
				print ("Right")
			else:
				#call left
				print ("Left")
			#Condition for destination reached
			if (((yy-desty)*(yy-desty))+((yx-destx)*(yx-destx))-(12*12))<0:
				cam = False
	#Swapping the source and destination to ensure going to depostion box
