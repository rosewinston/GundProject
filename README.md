# Lab-4-Gallery-Project

A program that interacts with a database to take in user input in the form of words, and emotions, to generate different visual representations of people's thoughts and responses to the gallery exhibit or individual art piece.

To ready the program for use on an ubuntu server enter these following commands:
- ```sudo mkdir /var/www/html/gallery```
- ```sudo chown [username] /var/www/html/gallery```
- ```make```
- ```./gallery```

Once the program is running, go to the landing page and log in to the admin portal. The username and password are hardcoded but for the sake of the software demo, the username is GalleryAdmin and the password is WYjX5aKujKh67m

In the admin portal enter the name of an art piece in the gallery, and add the identifying piece of its corresponding link on the gund gallery collections website. (https://collection.gundgallery.org)
  For example: 
    To add "Irises by Robert Mapplethorpe" you would add identifier from the photo link. (The full link of this piece is https://collection.gundgallery.org/Media/Previews/Mapplethorpe_Lilies.png and the identifier is "Mapplethorpe_Lilies.png") Once these are added, you can press save and the page will refresh, showing the new entry in the database.
    
When the program is running, all inputs will be automatically added to the database, the visualization pieces automatically take all the data from today's date for the whole gallery, and the data on the individual piece for the entire exhibition.

If you have any other questions, or have errors with the code feel free to email
winston1@kenyon.edu
