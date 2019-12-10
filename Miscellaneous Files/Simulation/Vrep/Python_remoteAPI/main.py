# Make sure to have the server side running in V-REP: 
# in a child script of a V-REP scene, add following command
# to be executed just once, at simulation start:
#
# simRemoteApi.start(19999)
#
# then start simulation, and run this program.
#
# IMPORTANT: for each successful call to simxStart, there
# should be a corresponding call to simxFinish at the end!

try:
    import vrep
except:
    print ('--------------------------------------------------------------')
    print ('"vrep.py" could not be imported. This means very probably that')
    print ('either "vrep.py" or the remoteApi library could not be found.')
    print ('Make sure both are in the same folder as this file,')
    print ('or appropriately adjust the file "vrep.py"')
    print ('--------------------------------------------------------------')
    print ('')
    exit(0)

import time
import math
import numpy as np 
import matplotlib.pyplot as plt  

def execute_SIM(clientID):
    ret = vrep.simxStartSimulation(clientID,vrep.simx_opmode_oneshot)
    print("\nSimulation Started...")
    counter=0
    frequency = 4
    a = 40                 #Amplitude Coeff                         
    b = 1*math.pi          #Curve Coeff                               
    c = 0                   #Turn Coeff            
    num_segments = 4       #Number of servos
    gamma=-c/num_segments  
    beta=b/num_segments
    amplitude=a*abs(math.sin(beta/2))

    ret,servo_head=vrep.simxGetObjectHandle(clientID,'Head_M',vrep.simx_opmode_blocking)
    ret,servo_b1=vrep.simxGetObjectHandle(clientID,'B1_M',vrep.simx_opmode_blocking)
    ret,servo_b2=vrep.simxGetObjectHandle(clientID,'B2_M',vrep.simx_opmode_blocking)
    ret,servo_tail=vrep.simxGetObjectHandle(clientID,'Tail_M',vrep.simx_opmode_blocking)

    ret=vrep.simxSetJointTargetPosition(clientID,servo_head,0*math.pi/180,vrep.simx_opmode_streaming)
    ret=vrep.simxSetJointTargetPosition(clientID,servo_b1,0*math.pi/180,vrep.simx_opmode_streaming)
    ret=vrep.simxSetJointTargetPosition(clientID,servo_b2,0*math.pi/180,vrep.simx_opmode_streaming)
    ret=vrep.simxSetJointTargetPosition(clientID,servo_tail,0*math.pi/180,vrep.simx_opmode_streaming)

    i=0
    while(i<5000):
        if ((counter<=360) and (counter>=0)):
            ret=vrep.simxSetJointTargetPosition(clientID,servo_head,(amplitude*math.sin(frequency*counter*math.pi/180+0*beta)+gamma)*math.pi/180,vrep.simx_opmode_streaming)
            ret=vrep.simxSetJointTargetPosition(clientID,servo_b1,(amplitude*math.sin(frequency*counter*math.pi/180+1*beta+math.pi/2)+gamma)*math.pi/180,vrep.simx_opmode_streaming)
            ret=vrep.simxSetJointTargetPosition(clientID,servo_b2,(amplitude*math.sin(frequency*counter*math.pi/180+2*beta)+gamma)*math.pi/180,vrep.simx_opmode_streaming)
            ret=vrep.simxSetJointTargetPosition(clientID,servo_tail,(amplitude*math.sin(frequency*counter*math.pi/180+3*beta+math.pi/2)+gamma)*math.pi/180,vrep.simx_opmode_streaming)
            counter+=1
        elif(counter>360):
            counter=0
        i+=1
        time.sleep(0.015)
    time.sleep(0.1)
    vrep.simxStopSimulation(clientID,vrep.simx_opmode_oneshot)
    print ("\nSimulation STOPED.")

if __name__ == "__main__":
    print ('Program started')
    vrep.simxFinish(-1) # just in case, close all opened connections
    clientID=vrep.simxStart('127.0.0.1',19997,True,True,5000,5) # Connect to V-REP
    if clientID!=-1:
        print ('Connected to remote API server')
        execute_SIM(clientID)
    else:
        print ('Failed connecting to remote API server')
        exit(0)
