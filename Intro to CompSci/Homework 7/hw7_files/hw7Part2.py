import json
if __name__ == "__main__":
    #variable initializtion
    movies = json.loads(open("movies.json").read())
    ratings = json.loads(open("ratings.json").read())
    minYear = int(input("Min year => "))
    print(minYear)
    maxYear = int(input("Max year => "))
    print(maxYear)
    w1 = input("Weight for IMDB => ")
    print(w1)
    w1 = float(w1)
    w2 = input("Weight for Twitter => ")
    print(w2)
    w2 = float(w2)
    moviesBetweenMinMax = dict()
    #loops through the movies, finds the movies that were released between the minimum and maximum years, and adds them to a dictionary
    for movie in movies:
        if(int(movies[movie]['movie_year']) >= minYear and int(movies[movie]['movie_year']) <= maxYear):
            moviesBetweenMinMax[movie] = movies[movie]

    #loops through the new dictionary, calculates the new rating based on imdb and twitter, and adds the new rating to a dictionary
    newMovieRating = dict()
    for i in range(len(moviesBetweenMinMax)):
        movieKey = list(moviesBetweenMinMax.keys())[i]
        if(movieKey in list(ratings.keys())):
            ratingKey = ratings[movieKey]
            if(len(ratingKey)>=3):
                average_twitter_rating = sum(ratingKey) / len(ratingKey)
                imdb_rating = moviesBetweenMinMax[movieKey]["rating"]
                rating = (w1* imdb_rating + w2 * average_twitter_rating)/(w1+w2)
                newMovieRating[(rating,movieKey)] = moviesBetweenMinMax[movieKey] 
    
    ratingsNormal = sorted(list(newMovieRating))
    ratingsReversed = sorted(list(newMovieRating),reverse=True)
    
    print("10 Highest rated movies")
    for k in range(10):
        print(newMovieRating[ratingsReversed[k]]["name"] + " ("+ str(newMovieRating[ratingsReversed[k]]["movie_year"]) +")")
        print(" "*10 + "Rating: {0:.2f}".format(ratingsReversed[k][0]) )
        print(" "*10 + "Genres: " + ", ".join(newMovieRating[ratingsReversed[k]]["genre"]))
    
    print()
    print("10 lowest rated movies")
    for k in range(10):
        print(newMovieRating[ratingsNormal[k]]["name"] + " ("+ str(newMovieRating[ratingsNormal[k]]["movie_year"]) +")")
        print(" "*10 + "Rating: {0:.2f}".format(ratingsNormal[k][0]) )
        print(" "*10 + "Genres: " + ", ".join(newMovieRating[ratingsNormal[k]]["genre"]))