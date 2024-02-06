var baseUrl = 'http://138.28.162.217:5005/';
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

// LANDING PAGE JS

// Get the modal
var modal = document.getElementById('admin');

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
    if (event.target == modal) {
        modal.style.display = "none";
    }
}

document.getElementById('admin-login').addEventListener("click", adminLogin);

function completeLogin(results) {
    var status = results['status'];
    if (status != "success") {
        alert("Incorrect Username or Password");
        return;
    }
    else {
		console.log("Admin Portal time!");
        window.location.replace("AdminPortal.html");
    }
}

function adminLogin() {
   username = document.getElementById('uname').value;
   password = document.getElementById('pword').value;
   fetch(baseUrl + 'admin/join/' + username + '/' + password, {
    method: 'get'
   })
   .then(response => response.json())
   .then(data => completeLogin(data))
   .catch(error => {
    {alert("Error: Something went wrong:" + error); }
   })
}
