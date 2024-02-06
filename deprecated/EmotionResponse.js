var baseUrl = 'http://54.81.146.159:5005';
var state="off";
var art_piece="";
var inthandle;
var inthandle2;
var emotion = '#343a40';
var currentArt = "";
var gundUrl = 'https://collection.thegund.org/Media/images/'
var artList = [];
var artLink = [];


// DROPDOWN FOR ART PIECE
getAllArts();

function siteDropdown(artList, artLink) { //currently working --tam
	var dropdown = "";
	var countValue = 0;
	artList.forEach(function(key){
		dropdown += "<option value='"+artLink[countValue]+"'>"+key+"</option>";
		// imageList += "<img id='"+
// 		<img id="slide-1" src="gund_img/gund1.jpeg" alt="img" draggable="false">
		countValue += 1;
	})
	
	var imageList = "";
	var count2 = 0;
	artLink.forEach(function(key){
		imageList += "<img id='"+key+"' src='"+gundUrl+key+"' alt='img' draggable='false'>";
	})

	document.querySelector('#slct').innerHTML = dropdown;
	document.querySelector('.slider').innerHTML = imageList;
	return;
}

function completeGetArts(results){
	if (results["status"] != "success") {
		// document.querySelector('#output').innerHTML = ErrQuery+": get sites";
		return;
	}
	artList = results['arts'];
	artLink = results['links'];
	siteDropdown(artList, artLink);
}

function getAllArts(){
	fetch(baseUrl+'/response/getAllArts', {
		method: 'get'	
	})
	.then (response => response.json())
    .then (data =>completeGetArts(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}

// apply the event listener to all images
document.querySelectorAll('.link').forEach(element => {
	element.addEventListener('click', event => {
		var emoID = event.currentTarget.id;
		var e = document.getElementById('slct');
		currentArt = e.options[e.selectedIndex].text;
		addEmotion(currentArt, emoID);
		
		// change current displayed art
	});
});

// 

function completeAddEmotion(results){
	var art_piece = results['art_piece'];
	var emotion = results['emotion'];
	console.log("Art: "+art_piece+", Emotion: "+emotion);	
	alert("Response recorded!")
}

function addEmotion(currentArt, emotionID) {
	fetch(baseUrl+'/response/addEmotion/'+currentArt+'/'+emotionID, {
        method: 'get'
    })
    .then (response => response.json() )
    .then (data =>completeAddEmotion(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}


// CHANGE IMAGE CAROUSEL IMAGE
var dropdownList = document.getElementById('slct');


dropdownList.addEventListener('change', event => {
	currentLink = dropdownList.options[dropdownList.selectedIndex].value;
	console.log(currentLink);
	document.querySelector('.slider').innerHTML = "<img id='"+currentLink+"' src='"+gundUrl+currentLink+"' alt='img' draggable='false'>";
});
