import tkinter as tk
class window():
	def __init__(self,mode):
		self.top = tk.Tk()
		self.lab = tk.Label(self.top,text = "access"+ (" granted" if mode else " denied"),fg = ("#000fff000"if mode else "#ff0000"))
		self.lab.pack(side = tk.LEFT)
		self.top.after(5000,lambda: self.top.destroy())
		self.top.mainloop()
		
