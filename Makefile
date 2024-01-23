# MakeFile for gallery
# server using C++ Microservice
# sudo mkdir /var/www/html/gallery
# sudo chown ubuntu /var/www/html/gallery

CC= g++

CFLAGS= -std=c++14  -Wno-deprecated-declarations

RM= /bin/rm -f

all: PutHTML gallery

emotionEntry.o: DatabaseFiles/emotionEntry.cpp DatabaseFiles/emotionEntry.h
	$(CC) -c $(CFLAGS) DatabaseFiles/emotionEntry.cpp
	
wordEntry.o: DatabaseFiles/wordEntry.cpp DatabaseFiles/wordEntry.h
	$(CC) -c $(CFLAGS) DatabaseFiles/wordEntry.cpp
	
galleryDB.o: DatabaseFiles/galleryDB.cpp DatabaseFiles/galleryDB.h
	$(CC) -c $(CFLAGS) -I/usr/include/cppconn DatabaseFiles/galleryDB.cpp

gallery.o: gallery.cpp httplib.h
	$(CC) -c $(CFLAGS) gallery.cpp
	
artEntry.o: DatabaseFiles/artEntry.cpp DatabaseFiles/artEntry.h
	$(CC) -c $(CFLAGS) DatabaseFiles/artEntry.cpp

gallery: gallery.o galleryDB.o emotionEntry.o wordEntry.o artEntry.o
	$(CC) gallery.o galleryDB.o emotionEntry.o wordEntry.o artEntry.o -o gallery -L/usr/local/lib -lmariadbcpp
	



PutHTML:
	cp EmotionResponse.html /var/www/html/gallery/
	cp EmotionResponse.js /var/www/html/gallery/
	cp GalleryFeedback.html /var/www/html/gallery/
	cp galleryFeedback.js /var/www/html/gallery/
	cp SummaryPage.html /var/www/html/gallery/
	cp SummaryPage.css /var/www/html/gallery/
	cp SummaryPage.js /var/www/html/gallery/
	cp -R css /var/www/html/gallery/
	cp gallery.js /var/www/html/gallery/
	cp GalleryLanding.html /var/www/html/gallery/
	cp LandingPage.js /var/www/html/gallery/
	cp -R gund_img /var/www/html/gallery/
	cp AdminPortal/AdminPortal.html /var/www/html/gallery/
	cp AdminPortal/adminPortal.js /var/www/html/gallery/
	
	cp words.html /var/www/html/gallery/
	cp words.css /var/www/html/gallery/
	cp words.js /var/www/html/gallery/

	
	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/gallery/

clean:
	rm -f *.o gallery 
