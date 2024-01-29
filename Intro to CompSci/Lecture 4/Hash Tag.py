phase='"Things you wish you knew as a freshman"'
print("The phrase" , phase)
phase = phase.title()
phase =phase.replace(" ","")
phase = phase.strip('"')
print('becomes the hashtag "#'+phase + '"')