var baseUrl = 'http://54.81.146.159:5005';
var state="off";
var myname="";
var art_piece="";
var mytoken = "";
var inthandle;
var inthandle2;
var color = '#343a40';
var username = "";
var password = "";
var word = ""; 

document.getElementById('submit-btn').addEventListener("click", getWord);

function getWord() {
   word = document.getElementById('word-response').value;
   fetch(baseUrl + '/response/word/'+word, {
    method: 'get'
   })
   .then(response => response.json())
   .then(data => completeGetWord(data))
   .catch(error => {
    {alert("Error: Something went wrong:" + error); }
   })
}


function completeGetWord(results){
	var word = results['word'];
	console.log("Word: "+word);
	clearTextbox();
	alert("Success! Word added");
}

// Clears up the textbox once the word is sent
function clearTextbox() {
    document.getElementById('word-response').value = "";
}
