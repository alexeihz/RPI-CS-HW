
import csv
import unicodedata

def format_header(header):
    new_header = []
    for name in header:
        m = name.split("_")
        new_name = ""
        for val in m:
            new_name += val + " "
        new_header.append(new_name.strip().capitalize())
    return new_header

def read_data_file(filename, int_field_indices=[], float_field_indices=[]):
    lineno = 0
    data = []
    filereader = csv.reader(open(filename, 'rU', encoding="utf-8"), delimiter=",", quotechar='"')
    for line in filereader:
        lineno += 1
        if lineno == 1:
            ##Switch so that university name is the first column
            line[0],line[1] = line[1], line[0]
            data.append(format_header(line))
            continue
        for index in int_field_indices:
            if len(line[index].strip()) == 0:
                line[index] = 0
            else:
                line[index] = int(line[index])
        for index in float_field_indices:
            if len(line[index].strip()) == 0:
                line[index] = 0.0
            else:
                line[index] = float(line[index])
                
        ##Switch so that university name is the first column
        line[0],line[1] = line[1], line[0]
        
        ## Remove accents and other unicode data from university names
        ## to avoid Submitty problems!
        udata=unicodedata.normalize('NFKD',line[0]).encode("ascii","ignore")
        line[0] = udata.decode("ascii")
        data.append( line )
    return data

def read_university_file(filename):
    return read_data_file(filename, [0,3,4,5,6,7,8,9,10,11,13], [12])
        
if __name__ == "__main__":
    print (read_university_file("university_data.csv"))
