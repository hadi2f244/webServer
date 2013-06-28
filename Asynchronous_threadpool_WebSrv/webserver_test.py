from telnetlib import *
total=0 #this is a int index to show we recieve all the data
for i in range(1000):
     t2=Telnet("localhost",2424)
     t2.write("GET /index.php")
for i in range(1000):
     t2=Telnet("localhost",2424)
     t2.write("GET /index.php")
     total+=len(t2.read_all())
