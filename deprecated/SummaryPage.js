var baseUrl = 'http://54.81.146.159:5005';
var state="off";
var graph = 0;
var unique_arts

summaryEmotion();

function listToMatrix(list, elementsPerSubArray) {
    var matrix = [], i, k;
    for (i = 0, k = -1; i < list.length; i++) {
      if (i % elementsPerSubArray === 0) {
        k++;
        matrix[k] = [];
      }
      matrix[k].push(list[i]);
    }
    return matrix;
}

function getCol(matrix, col){
    var column = [];
    for(var i=0; i<matrix.length; i++){
        column.push(matrix[i][col]);
    }
    return column;
}


function summaryEmotion(){
	fetch(baseUrl+'/response/summaryEmotion', {
		method: 'get'	
	})
	.then (response => response.json())
    .then (data => graphEmotion(data))
    .catch(error => {
        {alert("Error: Something went wrong:"+error);}
    })
}

function graphEmotion(result){
	var arts = result['arts'];
	var emotions = result['emotions'];
	var counts = result['counts'];
	
	var unique_arts = arts.filter((item, i, ar) => ar.indexOf(item) === i);
	var unique_emotions = emotions.filter((item, i, ar) => ar.indexOf(item) === i);
	var mat = listToMatrix(counts, unique_arts.length);
	
	var ctx = document.getElementById('chart').getContext('2d');
	// ctx.canvas.width = 300;
	ctx.canvas.height = 650;
	
	var chart = new Chart(ctx, {
		type: 'bar',
		data: {
			labels: unique_arts,
			datasets: [{
				label: unique_emotions[0],
				data: mat[0],
				backgroundColor: '#648fff'
			}, {
				label: unique_emotions[1],
				data: mat[1],
				backgroundColor: '#785ef0'
			}, {
				label: unique_emotions[2],
				data: mat[2],
				backgroundColor: '#dc267f'
			}, {
				label: unique_emotions[3],
				data: mat[3],
				backgroundColor: '#fe6100'
			}]
		},
		options: {
			responsive: true,
			scales: {
      			xAxes: [{
        			stacked: true,
        			gridLines: {
          				display: false,
        			}
      			}],
      			yAxes: [{
        			stacked: true,
        			ticks: {
          				beginAtZero: true,
        			},
        			type: 'linear',
      			}]
    		},
    		maintainAspectRatio: false,
    		// plugins: {
//             	title: {
//                 	display: true,
//                 	text: 'Custom Chart Title'
//             	}
//         	}
		}
	})
	
	
	
}
