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

// document.getElementById('submit-btn').addEventListener("click", addWord); 

getAllExhibitions();

/* Code to operate radio buttons */
// $('#radio-buttons label').click( function() {
// 	$(this).addClass('btn-primary').removeClass('btn-light');
// 	console.log("click button");
// 	// var wz = document.getElementById('wlan_zone');
// 	// console.log(wz.value,this.value)
// 	// wz.value = this.value;
// 	// console.log(wz.value,this.value)

// 	// const buttons = document.getElementById("zone_buttons");
// 	// for (const child of buttons.children) {
// 	// 	if (child.value != this.value) {
// 	// 		console.log("remove");
// 	// $(child).addClass('btn-light').removeClass('btn-primary');
// 	// 	}
// 	// }
// });

function setupButtons(){
    $('.radio-buttons label').click(function() {
		$(this).addClass('btn-primary').removeClass('btn-light');
        var id = $('#'+$(this).attr('for')).attr('id');
   	 	var val = $('#'+$(this).attr('for')).val();
		// const buttons = document.getElementById("exb_buttons");
		// 	for (const child of buttons.children) {
		// 		if (child.value != this.value) {
		// 			console.log("remove");
		// 	$(child).addClass('btn-light').removeClass('btn-primary');
		// 		}
		// 	}
		updateSettings(id,val);
		// console.log($(this));
    });
};

function updateSettings(id,value){
    console.log('clicked : ' +id+' ,Value: '+value);
}

//Create the radio buttons for the site, containing each exhibition with an associated link 
function siteDropdown(exhibitionList, exhibitionLink) { 
	var buttons = "";
	var countValue = 0;
	var classInfo = "btn btn-light col-6 col-sm-4 btn";
	exhibitionList.forEach(function(key){
		buttons += '<input type="radio" class="btn-check" name="options" id="'+countValue+'" autocomplete="off">'
		buttons += "<label class='"+classInfo+"' for='"+countValue+"'id='exb_buttons'>"+key+"</label>";
		countValue += 1;
	})
	
	var imageList = "";
	exhibitionLink.forEach(function(key){
		imageList += "<img id='"+key+"' src='"+key+"' alt='img' draggable='false'>";
	})

	document.querySelector('#radio-buttons').innerHTML = buttons;
	setupButtons();
	// document.querySelector('.slider').innerHTML = imageList;
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

// document.getElementById("slct").addEventListener("click",selectExhibition);

// Code that changes the image on the slider when dropdown option is selected
// var dropdownList = document.getElementById('slct');
// dropdownList.addEventListener('change', event => {
// 	currentLink = dropdownList.options[dropdownList.selectedIndex].value;
// 	console.log(currentLink);
// 	document.querySelector('.slider').innerHTML = "<img id='"+currentLink+"' src='"+currentLink+"' alt='img' draggable='false'>";
// });