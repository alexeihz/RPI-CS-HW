'''
This is the start to the solution to the problem of find all people
named in the internet movide database.  

One important note.  In opening the file we need to specify the
encoding the text.  The default is what's known as utf-8, but this
only handles English characters well.  For the IMDB file, we need to
open with a more language-independent, international standard.  This
is 'ISO-8859-1'.

As we will use the time.time() function to measure how long our
computation takes.  This function tells the seconds since an "epoch",
which is 1/1/1970 on Unix-based systems (including Macs and Linux
machines) and 1/1/1601 on Windows machines.  By recording in the
software the time before the calculations start, the time when the
calculations end, and subtracting we get the elapsed time.
'''
import time
nameCount = set()
totalName = set()
imdb_file = input("Data file name: ").strip()
print(imdb_file)
lastName = input("Prefix: ")
print(lastName)
name_list = []
for line in open(imdb_file, encoding = "ISO-8859-1"):
    words = line.strip().split('|')
    name = words[0].strip()
    if(lastName in name[0:len(lastName)]):
        nameCount.add(name.split(",")[0])
    totalName.add(name.split(",")[0])
print(len(totalName),"last names")
print(len(nameCount),"start with",lastName)