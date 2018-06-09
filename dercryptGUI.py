import tkinter as tk
import hashlib
import encryption 

class getPass():

	
	
	def counter_label(self,label):
		def count():
			try:
				self.counter -=1
				label.config(text="time left: "+str(self.counter))
				if self.counter == 0:
					self.top.destroy()	

				label.after(1000,count)
			except:
				pass
			
		count()
		
	def __init__(self):
		try:
              #main window
			self.counter = 50
			self.top = tk.Tk()
			self.top.title("Decryption window")
			self.but = tk.Button(self.top,text ="ok", command = self.checkPass)
			self.but.pack(side = tk.BOTTOM)
			self.lab = tk.Label(self.top,text="Enter password:")
			self.lab.pack(side =tk.LEFT)
			self.Timer = tk.Label(self.top,fg="red")
			self.Timer.pack()
			self.counter_label(self.Timer)
			self.ent = tk.Entry(self.top,bd=5,show="*")
			self.ent.pack(side = tk.RIGHT)
			self.top.mainloop()
		except:
			pass

	def checkPass(self):	
		#try:
		enc = encryption.encryption_module()
		decryption_mode = 0
		encryption_mode = 1
		config = open("Config","r")
		#enc.configEnc(decryption_mode)
		#config.decryption()
		password = (config.readlines()[1].split(':')[1][:-1])
		p = hashlib.md5(self.ent.get().encode()).hexdigest()
		if(password == p):
			enc.do_encrypt(decryption_mode)
		else:
			print ("password not correct")
		#enc.configEnc(encryption_mode)#config.encrypt
		config.close()
		#except IOError:
		#	print ("file error")
		#except:
		#	print ("error")
		#	self.top.destroy()
		self.top.destroy()
		

