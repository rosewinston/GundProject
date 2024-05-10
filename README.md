# The Gund Interactive Community Word Submission Interface

A program that interacts with a database to take in user input in the form of individual words associated with one of four exhibitions

To ready the program for use on an ubuntu server enter these following commands:
- ```sudo mkdir /var/www/html/gallery```
- ```sudo chown [username] /var/www/html/gallery```
- ```make```
- ```./gallery```

Once the program is running, go to the landing page and log in to the admin portal. The username and password are hardcoded but for the sake of the software demo, the username is GalleryAdmin and the password is WYjX5aKujKh67m

The admin portal contains 4 slots for exhibitions, with these exhibitions able to be edited to replace their name and their associated photo link. Alongside these four slots is a button to access the word float page associated with the exhibition.
    
When the program is running, all inputs will be automatically added to the database, the visualization pieces automatically take all the data from each exhibition and loads on its associated page.

On each exhibitions words page, there is a fullscreen button which hides the cursor in addition to fullscreening the application, in order to exit this mode you must press the "x" key, which will close fullscreen and restore the cursor.

If you have any other questions, or have errors with the code feel free to email
winston1@kenyon.edu

Known Issues:
- Words scale relatively to each other but that intial scale is random and inconsistent.
- If window opened in non-fullscreen on words.html the canvas will crop incorrectly, this can be fixed by a simple refresh in fullscreen mode.
