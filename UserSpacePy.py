from tkinter import *
import re
import time
import os
import AccessGrantedGUI
import threading
import smtplib

#self build libs
import encryption
import dercryptGUI




STRLEN = 100
sysBuffer = ""

logFile = open("DmesgLog",'w') #delete the curr content of the log
logFile.close()

regexes = open("regexes",'r') #read the DB
RegList = regexes.readlines()
regexes.close()

r = Tk()
r.withdraw() #closing the visual window of gui

encryption_mode =1

config = open("Config",'r')
configData = config.readlines() #read content of config file
config.close()

#getting data from config file
Backdoorpass=configData[2][:-1]
InstallerEmail=configData[3][:-1] 
RegList+=[configData[0][:-1].split(':')[1]] #add the path to the regexes list
BackdoorReg = re.compile(Backdoorpass) # reading the backdoor pass


BackdoorOn=False

enc = encryption.encryption_module() #load encryption_module

os.system("sudo dmesg -c>//dev//null") #clean dmesg



while True:

	#backdoor mode
	if not (re.search(BackdoorReg,sysBuffer) == None):
		BackdoorOn = not BackdoorOn
		sysBuffer = "" #we dont want commands from before
		
		myThread = threading.Thread(target=AccessGrantedGUI.window,args=(BackdoorOn,))
		myThread.start() #notify the user that he entered the mode successfuly
		
	
	os.system("dmesg | grep KL > DmesgLog") #take only our relevant messages to our log file
	DmesgLog = open("DmesgLog","r")
	lines = DmesgLog.readlines()
	DmesgLog.close()

	for line in lines:
		data = line.split(' ')[3]  #taking just the letters from the log file
		print("DATA IS " +data) #good

		CBData = ""
		try:
			CBData = r.clipboard_get() #get data from clipboard
		except:
			pass

		if len(data) == 1: #we want just the letter
			sysBuffer+=data
		elif data == "_BACKSPACE_":
			sysBuffer = sysBuffer[:-1] #slice the last char to adjust to backspace.
		if len(sysBuffer) == STRLEN:
			sysBuffer = sysBuffer[1:]  #slice the first char to adjust the length,fifo
		
		for string in RegList:
			
			currReg = re.compile(string[:-1]) #getting every regex from DB

			#check if the buffer matches a given regex from the list
			if not BackdoorOn  and (not (re.search(currReg,sysBuffer) == None) or not (re.search(currReg,CBData)==None)): 
				#encrypt sensetive files
				enc.do_encrypt(encryption_mode)
				#open window for entering a password to do decrypt
				decrypt_window =dercryptGUI.getPass()
				
				sendMail()
				exit(0)

	
	os.system("sudo dmesg -c>//dev//null") 
	time.sleep(1) #a second





def sendMail():
	global InstallerEmail
	print(InstallerEmail)
	server = smtplib.SMTP('smtp.gmail.com',587)
	server.starttls() #create an insecure connection
	server.login('sysdefendnotification@gmail.com','sysdefend1@')
	msg = 'suspicious action detected'
	server.sendmail('sysdefendnotification@gmail.com',InstallerEmail,msg) 
	server.quit()


