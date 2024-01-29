def percentage_happy(sentence):
    numLaugh = sentence.count("laugh")
    numLove = sentence.count("love")
    numGood = sentence.count("good")
    numHappiness = sentence.count("happyness")
    numExcellent = sentence.count("excellent")
    return numLove + numExcellent + numGood + numLaugh + numHappiness

def percentage_sad(sentence):
    numBad = sentence.count("bad")
    numSad = sentence.count("sad")
    numTerrible = sentence.count("terrible")
    numHorrible = sentence.count("horrible")
    numProblem = sentence.count("problem")
    return numBad + numSad + numHorrible + numTerrible + numProblem

string = input("Enter a sentence => ")
print(string)
string = string.strip(" ")
string = string.lower()
words = string.count(" ")+1

print("Percentages. happy: {0:.3f} sad: {1:.3f}".format(percentage_happy(string)/words, percentage_sad(string)/words))
if (percentage_happy(string)/words) > (percentage_sad(string)/words):
    print("This is a happy sentence")
    
if (percentage_happy(string)/words) < (percentage_sad(string)/words):
    print("This is a sad sentence")
    
if (percentage_happy(string)/words) == (percentage_sad(string)/words):
        print("This is a neutral sentence")
