//Halaman web
const char MAIN_page[]= R"=====(
<!doctype html>
<html>

<head>
  <title>Pembacaan GM-Counter</title>
  <script src = "https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>  
  <style>
  canvas{
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }

  #dataTable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
  }

  #dataTable td, #dataTable th {
    border: 1px solid #ddd;
    padding: 8px;
  }

  #dataTable tr:nth-child(even){background-color: #f2f2f2;}

  #dataTable tr:hover {background-color: #ddd;}

  #dataTable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #4CAF50;
    color: white;
  }
  </style>
</head>

<body>
    <div style="text-align:center;"><b>Realtime Update</b></div>
    <div class="chart-container" position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>
<div>
  <table id="dataTable">
    <tr><th>Time</th><th>Intensitas(CPM)</th></tr>
  </table>
</div>
<br>
<br>  

<script>

var values = [];
var timeStamp = [];
function showGraph()
{

    var ctx = document.getElementById("Chart").getContext('2d');
    var Chart2 = new Chart(ctx, {
        type: 'line',
        data: {
            labels: timeStamp,  
            datasets: [{
                label: "CPM",
                fill: false,  //Try with true
                backgroundColor: 'rgba( 90, 124, 235 , 1)', 
                borderColor: 'rgba( 90, 124, 235 , 1)', 
                data: values,
            }],
        },
        options: {
            title: {
                    display: true,
                    text: "Grafik realtime CPM"
                },
            maintainAspectRatio: false,
            elements: {
            line: {
                    tension: 0 
                }
            },
            scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero:true
                        }
                    }]
            }
        }
    });

}


window.onload = function() {
  console.log(new Date().toLocaleTimeString());
  showGraph(5,10,4,58);
};


setInterval(function() {
  getData();
}, 5000); 
 
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
     
  var time = new Date().toLocaleTimeString();
  var InValue = this.responseText; 
      values.push(InValue);
      timeStamp.push(time);
      showGraph();  
  
    var table = document.getElementById("dataTable");
    var row = table.insertRow(1); 
    var cell1 = row.insertCell(0);
    var cell2 = row.insertCell(1);
    cell1.innerHTML = time;
    cell2.innerHTML = InValue;
    }
  };
  xhttp.open("GET", "readInput", true); 
  xhttp.send();
}
    
</script>
</body>

</html>

)=====";
