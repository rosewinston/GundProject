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
   	 	var val = $(this).text();
		// Remove the 'btn-primary' class from siblings and add 'btn-light'
		$(this).siblings('label').removeClass('btn-primary').addClass('btn-light');
		selectExhibition(id,val);
    });
};

function selectExhibition(ExhibitionID,value){
    console.log('EID : ' +ExhibitionID+' ,Name: '+value);
	var question = "Share a word that encapsulates how "+value+" made you feel!"
	document.querySelector('#question').innerHTML = question;
	exhibition = value;
	changeImage(ExhibitionID);
	document.getElementById("word_submission").style.visibility = "visible"; 
	document.getElementById("img_container").style.visibility = "visible"; 
	
}

function changeImage(eID){
	var image="";
	for (let i=0; i<4; i++) {
		var ExbLink = exhibitionLink[i];
		if (i==eID) {
		image = "<img id='"+ExbLink+"' src='"+ExbLink+"' alt='img' draggable='false'>";
		}
	}
	document.querySelector('#img_container').innerHTML = image;
}

//Create the radio buttons for the site, containing each exhibition with an associated link 
function siteButtons(exhibitionList) { 
	var buttons = "";
	var countValue = 0;
	var classInfo = "btn btn-light col-5 btn";
	exhibitionList.forEach(function(key){
		if (key!=""){
		buttons += '<input type="radio" class="btn-check" name="options" id="'+countValue+'" autocomplete="off">'
		buttons += "<label class='"+classInfo+"' for='"+countValue+"'id='exb_buttons' style='margin-top: 10px; font-size:20px;'>"+key+"</label>";
		}
		countValue += 1;
	})
	
	

	document.querySelector('#radio-buttons').innerHTML = buttons;
	setupButtons();
	// document.querySelector('.slider').innerHTML = imageList;
	return;
}

function completeGetExhibitions(results){
	if (results["status"] != "success") {
		document.querySelector('#output').innerHTML = ErrQuery+": get sites";
		return;
	}
	exhibitionList = results['exhibitions'];
	exhibitionLink = results['links'];
	siteButtons(exhibitionList, exhibitionLink);
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
}