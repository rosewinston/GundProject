//Admin Portal for Gund Gallery exhibitionDB
var exhibitionList = [];
const baseUrl = '138.28.162.217:5005';
const imageUrl = "https://collection.thegund.org/Media/images/"

/* Set up events */
$(document).ready(function() {
	// Add a click event for the filter button
	document.querySelector("#filter-btn").addEventListener("click", (e) => {
		var searchStr = 	document.querySelector("#search").value;
    	findMatches(searchStr);
	});

    $(".dropdown-menu li a").click(function() {
        var selection = $(this).text();
        $(this).parents(".btn-group").find('.btn').html(selection + ' <span class="caret"></span>');
    });

	findMatches(" ");

});

/* Search and display exhibition functions */

// Build output table from comma delimited list
function formatMatches(json) {

    var result = '<table class="table table-success table-striped""><tr><th>Name</th><th>Link</th><th>Action</th><tr>';
    json.forEach(function(entry, i) {
        result += "<tr><td class='Name'>" + entry['Name'] + "</td><td class='Link'>" + entry['Link'];
        result += "<td><button type='button' class='btn btn-primary btn-sm edit' data-bs-toggle='modal' data-bs-target='#editExhibition' ";
        result += "onclick=\"editExhibition(" + i + ")\">Edit</button> ";
        result += "<button type='button' class='btn btn-primary btn-sm ' onclick=\"deleteEntry("+ entry['ID'] +")\">Delete</button></td></tr>";
    });
    result += "</table>";

    return result;
}

function displayMatches(results) {

    exhibitionList = results["results"];
    console.log("Results:"+JSON.stringify(exhibitionList));
    document.getElementById("searchresults").innerHTML = formatMatches(exhibitionList);
    
}

function findMatches(search) {
	// only include / after find if search not empty
	search = search.trim();
    if (search != "") search = "/" + search;

	console.log("Search:" + search);
    fetch(baseUrl + '/exhibition/find' + search, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => displayMatches(json))
        .catch(error => {
            {
                alert("Find Error: Something went wrong: " + error);
            }
        })
}

/* Add exhibition functions */
function processAdd(results) {
    console.log("Add:", results["status"]);
	if (results["status"]=="success"){
        document.getElementById("addname").value = "";
        document.getElementById("addlink").value = "";
         findMatches("");
    } else {
        alert(results["status"]);
    }

}

function addExhibition() {
    console.log("Attempting to add an entry");
    console.log("Exhibitionname:" + $('#addname').val());
    $('#searchresults').empty();
    fetch(baseUrl + '/exhibition/add/' + document.getElementById("addname").value + "/" + document.getElementById("addlink").value, {
            method: 'get'
        })
        .then(response => response.json())
        .then(json => processAdd(json))
        .catch(error => {
            {
                alert("Add Error: Something went wrong: " + error);
            }
        })
}


function editExhibition(row) {
    console.log("start edit data: "+row+JSON.stringify(exhibitionList[row]));
    console.log("Name of record: " + exhibitionList[row]["Name"]);
    editid = exhibitionList[row]["ID"];
	
	document.getElementById("editname").value = exhibitionList[row]["Name"];
	document.getElementById("editlink").value = exhibitionList[row]["Link"];
	
	//Save ID in modal
	var modal = document.querySelector("#editExhibition");
	modal.setAttribute("editid",editid);
}


function updateExhibition() {

	// Get ID in the modal
	var modal = document.querySelector("#editExhibition");
	id = modal.getAttribute("editid");
	
    console.log("Attempting to edit an entry:"+id); 

    fetch(baseUrl + '/exhibition/update/' + id + '/' + document.getElementById("editname").value + '/' + document.getElementById("editlink").value, {
                method: 'get'
            })
        .then(alert("Record for " + document.getElementById("editname").value + " updated"))
        .catch(error => {
            {
                alert("Edit Error: something went wrong:" + error);
            }
        });
        
    findMatches(" ");

}


function deleteEntry(id) {

    console.log("Attempting to delete an entry:" + id);
    fetch(baseUrl + '/exhibition/delete/' + id, {
            method: 'get'
        })
        .then(alert("Deleted Record: " + id))
        .catch(error => {
            {
                alert("Delete Error: Something went wrong:" + error);
            }
        });
     findMatches(" ");

}
