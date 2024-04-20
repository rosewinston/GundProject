const baseUrl = window.location.origin + ":5005";
// const gundUrl = "https://collection.thegund.org/Media/images/";
var state="off";
var myname="";
var exhibition="";
var mytoken = "";
var inthandle;
var inthandle2;
var color = '#343a40';
var exhibitionList = [];
var exhibitionLink = [];
var word = ""; 

document.getElementById('submit-btn').addEventListener("click", addWord); 

getAllExhibitions();

//Create the dropdown list for the site, containing each exhibition with an associated link 
function siteDropdown(exhibitionList, exhibitionLink) { 
	var dropdown = "";
	var countValue = 0;
	exhibitionList.forEach(function(key){
		dropdown += "<option id='"+countValue+"' value='"+exhibitionLink[countValue]+"'>"+key+"</option>";
		countValue += 1;
	})
	
	var imageList = "";
	exhibitionLink.forEach(function(key){
		imageList += "<img id='"+key+"' src='"+key+"' alt='img' draggable='false'>";
	})

	document.querySelector('#slct').innerHTML = dropdown;
	document.querySelector('.slider').innerHTML = imageList;
	return;
}

function completeGetExhibitions(results){
	if (results["status"] != "success") {
		// document.querySelector('#output').innerHTML = ErrQuery+": get sites";
		return;
	}
	exhibitionList = results['exhibitions'];
	exhibitionLink = results['links'];
	siteDropdown(exhibitionList, exhibitionLink);
}

function getAllExhibitions(){
	fetch(baseUrl+'/response/getAllExhibitions', {
		method: 'get'	
	})
	.then (response => response.json())
    .then (data =>completeGetExhibitions(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}

// adds word to database and sends the associated exhibition along with it
function addWord() {
	var word = document.getElementById('word-response').value;
	if (word=="") {
		alert("Please enter a word");
		return;
	}
	var e = document.getElementById('slct');
	var exhibition = e.options[e.selectedIndex].text;
	console.log(exhibition);
	fetch(baseUrl+'/response/word/'+exhibition+'/'+word, {
        method: 'get'
    })
    .then (response => response.json() )
    .then (data =>completeAddWord(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}

function completeAddWord(results){
	var eID = results['eID'];
	var word = results['word'];
	console.log("Exhibition ID: "+eID+", Word: "+word);	
	alert("Success! Response recorded!")
	clearTextbox();
}

// Clears up the textbox once the word is sent
function clearTextbox() {
    document.getElementById('word-response').value = "";
}

// Function and listener for selecting exhibition
function selectExhibition(){
	var e = document.getElementById("slct");
	var exhibitionName = e.options[e.selectedIndex].text;
	var label = "Share a word that encapsulates how "+exhibitionName+" made you feel!"
	document.querySelector('label').innerHTML = label;
}

document.getElementById("slct").addEventListener("click",selectExhibition);

// Code that changes the image on the slider when dropdown option is selected
var dropdownList = document.getElementById('slct');
dropdownList.addEventListener('change', event => {
	currentLink = dropdownList.options[dropdownList.selectedIndex].value;
	console.log(currentLink);
	document.querySelector('.slider').innerHTML = "<img id='"+currentLink+"' src='"+currentLink+"' alt='img' draggable='false'>";
});