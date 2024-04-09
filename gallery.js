var baseUrl = 'http://138.28.162.217:5005';
var state="off";
var myname="";
var art_piece="";
var mytoken = "";
var inthandle;
var inthandle2;
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

document.getElementById('admin-join').addEventListener("click", adminLogin);

function completeLogin(data) {
    var status = results['status'];
    if (status != "success") {
        alert("Incorrect Username or Password");
        return;
    }
    else {
        window.location.href = "AdminPortal/AdminPortal.html";
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

//

//Color Page js
document.addEventListener("click", e => {
    const isDropdownButton = e.target.matches("[data-dropdown-button]")
    if (!isDropdownButton && e.target.closest('[data-dropdown]') != null) return

    let currentDropdown
    if (isDropdownButton) {
        currentDropdown = e.target.closest('[data-dropdown]')
        currentDropdown.classList.toggle('active')
    }

    document.querySelectorAll("[data-dropdown].active").forEach(dropdown => {
        if (dropdown === currentDropdown) return
        dropdown.classList.remove('active')
    })
})

document.getElementById('submit-btn').addEventListener("click", getWord);

function getWord() {
   word = document.getElementById('word-response').value;
   fetch(baseUrl + '/response/'+word, {
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
}


//
