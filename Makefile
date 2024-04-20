# MakeFile for gallery
# server using C++ Microservice
# sudo mkdir /var/www/html/gallery
# sudo chown ubuntu /var/www/html/gallery

CC= g++

CFLAGS= -std=c++14  -Wno-deprecated-declarations

RM= /bin/rm -f

all: PutHTML gallery

	
wordEntry.o: DatabaseFiles/wordEntry.cpp DatabaseFiles/wordEntry.h
	$(CC) -c $(CFLAGS) DatabaseFiles/wordEntry.cpp
	
galleryDB.o: DatabaseFiles/galleryDB.cpp DatabaseFiles/galleryDB.h
	$(CC) -c $(CFLAGS) -I/usr/include/cppconn DatabaseFiles/galleryDB.cpp

gallery.o: gallery.cpp httplib.h
	$(CC) -c $(CFLAGS) gallery.cpp
	
exhibitionEntry.o: DatabaseFiles/exhibitionEntry.cpp DatabaseFiles/exhibitionEntry.h
	$(CC) -c $(CFLAGS) DatabaseFiles/exhibitionEntry.cpp

gallery: gallery.o galleryDB.o wordEntry.o exhibitionEntry.o
	$(CC) gallery.o galleryDB.o wordEntry.o exhibitionEntry.o -o gallery -L/usr/local/lib -lmariadbcpp
	



PutHTML:
	cp GalleryFeedback.html /var/www/html/gallery/
	cp galleryFeedback.js /var/www/html/gallery/
	cp -R css /var/www/html/gallery/
	cp gallery.js /var/www/html/gallery/
	cp GalleryLanding.html /var/www/html/gallery/
	cp LandingPage.js /var/www/html/gallery/
	cp -R gund_img /var/www/html/gallery/
	cp AdminPortal/AdminPortal.html /var/www/html/gallery/
	cp AdminPortal/adminPortal.js /var/www/html/gallery/
	cp words.html /var/www/html/gallery/
	cp words1.html /var/www/html/gallery/
	cp words2.html /var/www/html/gallery/
	cp words3.html /var/www/html/gallery/
	cp words.css /var/www/html/gallery/
	cp words.js /var/www/html/gallery/
	cp assets/favicon.ico /var/www/html/gallery/assets

	
	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/gallery/

clean:
	rm -f *.o gallery 
