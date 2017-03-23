#importing stuff
import serial, time
#arduino = serial.Serial('COM7', 115200, timeout=.1)
time.sleep(1) #give the connection a second to settle
#arduino.write("1")
import numpy as np
import cv2
bl = 100		#Don't change this, make sure blacks value is highest
R = 35
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
rup = (255,255,255)
glow = (50,0,0)
gup = (70,255,255)
blow = (60,0,10)
bup = (110,255,255)
#bot colors are magenta(m) and yellow(y)
mlow = (80,100,100)
mup = (80,100,100)
ylow = (25,146,190)
yup = (62,174,250)
#Video init
#camera = cv2.VideoCapture(0)		#change this
#initial calculations
#(grabbed, snap) = camera.read()		#first snap for initial calc
snap = cv2.imread('V:/Works and Stuff/Sophomore 16-17/RCS/Robovision/Trails/1.png')
#camera.release()
#snap = cropped = snap[70:170, 440:540]	#resizing the snap
#HSV conversion
hsv = cv2.cvtColor(snap, cv2.COLOR_BGR2HSV)
#masking using color and then identifying shape to calc credits
mask = []
centers = {}
mask.append(cv2.inRange(hsv,bllow,blup)) 
mask.append(cv2.inRange(hsv,rlow,rup))
mask.append(cv2.inRange(hsv,glow,gup))
mask.append(cv2.inRange(hsv,blow,bup))
print len(mask)
#doing everything for one set of surce and destination
def pathfinder (masks, maskd):
	print("hi")
	#camera = cv2.VideoCapture(0)

	#Source mask
	cnts = cv2.findContours(masks.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
	centers = None
	if len(cnts) > 0:
		cnts = max(cnts, key=cv2.contourArea)
		((x, y), radiuss) = cv2.minEnclosingCircle(cnts)
		M = cv2.moments(cnts)
		radiuss = int(radiuss)
		centers = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
		cv2.circle(snap, (centers), 10, (0, 255, 255), -1)
	#Destination mask
	cntd = cv2.findContours(maskd.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
	centerd = None
	if len(cntd) > 0:	
		cntd = max(cntd, key=cv2.contourArea)
		((x, y), radiusd) = cv2.minEnclosingCircle(cntd)
		M = cv2.moments(cntd)
		radiusd = int(radiusd)
		centerd = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
		cv2.circle(snap, (centerd), R, (0, 255, 255), 2)
	#checking snaps
	
	(srcx, srcy) = centers
	(destx,desty) = centerd
	cv2.line(snap,(srcx,srcy),(destx,desty),(255,0,255),5)
	cv2.imshow('snap',snap)
	cv2.waitKey(0)
	cv2.destroyAllWindows()
	gradx = destx-srcx
	grady = desty-srcy
	pslope = float(grady)/float(gradx)	#slope of the path
	print pslope
	#video loop
	#camera = cv2.VideoCapture(0)
	cam = True
	while (cam):

		botlow = (100,0,0)
		botup = (255,255,255)
		maskb = (cv2.inRange(hsv,botlow,botup))
		cntb = cv2.findContours(maskb.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[-2]
		if len(cntb)>0:
			cntb = max(cntb, key=cv2.contourArea)
			((x, y), radiusb) = cv2.minEnclosingCircle(cntb)
			M = cv2.moments(cntb)
			radiusb = int(radiusb)
			centerb = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))
			cv2.circle(snap, (centerb), 10, (0, 255, 255), 2)
		'''rows,cols = snap.shape[:2]
		print len(snap.shape)
		ctr = np.array(cntb).reshape((-1,1,2)).astype(np.int32)
		[vx,vy,x,y] = cv2.fitLine(ctr, cv2.DIST_L2,0,0.01,0.01)
		lefty = int((-x*vy/vx) + y)
		righty = int(((cols-x)*vy/vx)+y)
		cv2.line(snap,(cols-1,righty),(0,lefty),(0,255,0),2)
		'''
		(botx,boty) = centerb
		cv2.line(snap,(destx,desty),(botx, boty),(255,0,0),5)
		bgradx = botx - destx
		bgrady = boty - desty
		bslope = float(bgrady)/float(bgradx)
		print("B:"+str(bslope))
		slopediff = pslope - bslope
		print slopediff
		factor = (float(botx)-float(destx))*(float(botx)-float(destx))+(float(boty)-float(desty))*(float(boty)-float(desty))-(R*R)	
		print factor
		if factor<0:
			#stop
			ser.write(b'3')
			print("stop")
			cam = False
			sleep(1)
			ser.write(b'4')
			#camera.release()
		elif slopediff>0:
			#turn left
			print("left")
		else:
			#turn right
			print("right")
		cv2.imshow('snap',snap)
		cv2.waitKey(0)
		cv2.destroyAllWindows()

while(True):
	#camera.release()

	for i in range(0,4):
		s = 0
		d = 2
		pathfinder(mask[s],mask[d])
		temp = s
		s = d
		d = temp
