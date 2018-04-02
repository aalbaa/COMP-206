
output: movie_recommender.o preferences.o distances.o
	gcc movie_recommender.o preferences.o distances.o -o movie_recommender
movie_recommender.o: src/movie_recommender.c preferences.o distances.o
	gcc -Iinclude -c src/movie_recommender.c
preferences.o: src/preferences.c include/preferences.h
	gcc -Iinclude -c src/preferences.c
distances.o: src/distances.c include/distances.h
	gcc -Iinclude -c src/distances.c
clean:
	rm -f movie_recommender
