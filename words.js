window.onload = function(argument) {
	var baseUrl = 'http://138.28.162.217:5005';
	var exhibitionList;
	var exhibitionLink;
	var exhibition="";
	var exb = document.getElementsByName('exhibition');
	var id = exb[0].getAttribute( 'id' );
	var wordsRetrieved = "";
	var words = {};
	var words_attr = [];
	var canvas = document.getElementById('c');
	const fullscreenButton = document.getElementById('fullscreen-button');
	let page = document.documentElement;

	function completeGetExhibitions(results){
		if (results["status"] != "success") {
			return;
		}
		exhibitionList = results['exhibitions'];
		exhibitionLink = results['links'];
		changeTitle(id,exhibitionList);
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

	function changeTitle(id,exhibitionList){
		var exbTitle = exhibitionList[id];
		var title = "<div value='"+id+"'>"+exbTitle+"</div>";
		document.querySelector('.title').innerHTML = title;
		exhibition = exbTitle;
		console.log(exhibition);
		wordCloud();
	}

	getAllExhibitions();
	fullscreenButton.addEventListener('click', setFullscreen);
	
	window.addEventListener("keydown", (event) => {
		if (event.key == "x") {
			closeFullscreen();
		}
	});

	function setFullscreen(){
		if (page.requestFullscreen) {
			page.requestFullscreen();
		} else if (page.mozRequestFullScreen) { /* Firefox */
			page.mozRequestFullScreen();
		} else if (page.webkitRequestFullscreen) { /* Safari */
			page.webkitRequestFullscreen();
		} else if (page.msRequestFullscreen) { /* Internet Explorer */
			page.msRequestFullscreen();
		}
		canvas.classList.add("hidecursor");
	}

	function closeFullscreen(){
		document.exitFullscreen();
		canvas.classList.remove("hidecursor");
	}

	function wordCloud(){
		canvas.width = window.innerWidth;
		canvas.height = window.innerHeight;
		console.log(canvas.height);
		if (canvas.getContext) {
			var c = canvas.getContext('2d'),
				w = canvas.width,
				h = canvas.height;
			c.strokeStyle = 'red';
			c.lineWidth = 5;
			fetchWords(); 
			console.log(wordsRetrieved);
		console.log(words);

	}
		function fetchWords() {
   			fetch(baseUrl + '/retrieve/words/'+exhibition, {
   			method: 'get'
   			})
   			.then(response => response.json())
   			.then(data => formatWords(data))
   			.catch(error => {
   	 		{alert("Error: Something went wrong:" + error); }
  	 		})

   		}
		console.log(words);
		function formatWords(data){
			var result = data;
			var formattedString = "";
			var first = true; 
			if (result["status"]=="success"){
				var wordList = result["words"]; 
				wordList.forEach(function (wordElement) {
					if (first){
						formattedString+=wordElement; 
						first = false; 
					}else{
						formattedString+=" " + wordElement; 
					}
					
				});
				console.log(typeof formattedString); 
				console.log(typeof moby);
				wordsRetrieved = formattedString; 
				console.log(typeof wordsRetrieved);
				string_handle(wordsRetrieved);
			}else{
				alert("Error: Word Cloud Retrieve Failed"); 
			}
		}
		
		//function to randomly assign a color to a given word 
		function colorAssign(){
			//color options from IBM Design Colorblind Friendly Palette
			var colorArray = ['#648FFF', '#785EF0', '#DC267F', '#FE6100', '#FFB000'];
			var colorRand = colorArray[Math.floor(Math.random()* 5)]; 
			return colorRand; 
		}
		
		
		//for (key in words) {	
			//words_attr.push(new Word(key));
		//}
		
		// constructor
		Word = function(key) {
			this.text = key;
			this.x = Math.random() * w;
			this.y = Math.random() * h;
			this.font = words[key] * 50 + 'px arial'
			this.speed = (words[key]);
			this.color = colorAssign();
		}
		
		//check to see if words are being constructed and passed successfully
		console.log(words_attr.length);
		console.log(words);

		function animation() {
			for (var i = 0; i < words_attr.length; i++) {
				c.font = words_attr[i].font;
				c.fillText(words_attr[i].text, words_attr[i].x, words_attr[i].y);
				words_attr[i].width = c.measureText(words_attr[i].text).width;
				c.fillStyle = words_attr[i].color; 
				c.stroke();
			}
			move();
		}

		function move() {
			for (var i = 0; i < words_attr.length; i++) {
				if (words_attr[i].x > w) {
					words_attr[i].x = -words_attr[i].width;
					words_attr[i].y = Math.random()*h;
				}else{
					words_attr[i].x += words_attr[i].speed;
				}
			}
		}

		setInterval(function() {
			c.clearRect(0,0,w,h);
			animation();
		},24);

	}
	console.log(words);
	function string_handle(str) {
    var lamda = 1;
		var word_array = str.split(" ");
		console.log(typeof word_array);
		
    // Give each word a random occurance counrt
		for (var i = 0; i < word_array.length; i++) {
      var u = Math.random();
      occurance =  -Math.log(u)/(lamda);
      // Should set. this to the number of occurances of word
			words[word_array[i]] = occurance;
		}
	
		for (key in words) {	
			words_attr.push(new Word(key));
		}
		
		return words;
	}

}

