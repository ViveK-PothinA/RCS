'''
**************************************************************************
*                  IMAGE PROCESSING (e-Yantra 2014)
*                  ================================
*  This software is intended to teach image processing concepts
*
*  MODULE: Functions
*  Filename: drawImage.py
*  Version: 1.0.0  
*  Date: November 3, 2014
*  
*  Author: Arun Mukundan, e-Yantra Project, Department of Computer Science
*  and Engineering, Indian Institute of Technology Bombay.
*  
*  Software released under Creative Commons CC BY-NC-SA
*
*  For legal information refer to:
*        http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode 
*     
*
*  This software is made available on an “AS IS WHERE IS BASIS”. 
*  Licensee/end user indemnifies and will keep e-Yantra indemnified from
*  any and all claim(s) that emanate from the use of the Software or 
*  breach of the terms of this agreement.
*  
*  e-Yantra - An MHRD project under National Mission on Education using 
*  ICT(NMEICT)
*
**************************************************************************
'''

############################################
## Import OpenCV
import numpy as np
import cv2
############################################

############################################
## Create the image
img = np.zeros((500,500,3), np.uint8)
############################################

############################################
## Do the processing
# Draw a line
cv2.line(img,(10,10),(490,10),(255,0,0),5)

# Draw a rectangle
cv2.rectangle(img,(20,20),(480,80),(0,255,0),3)

# Draw a circle
cv2.circle(img,(150,150), 50, (0,0,255), -1) 	# Filled
cv2.circle(img,(350,150), 50, (0,0,255),  3)    # Outline

# Draw an ellispe
cv2.ellipse(img,(250,200),(200,100),0,0,180,(100,100,0),3)
############################################

############################################
## Show the image
cv2.imshow('image',img)
############################################

############################################
## Close and exit
cv2.waitKey(0)
cv2.destroyAllWindows()
############################################
