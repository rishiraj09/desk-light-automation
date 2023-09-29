
var distance;
var status;
var ts;


function callAPI() {
    var myHeaders = new Headers();
    var requestOptions = {
      method: "GET",
      headers: myHeaders,
    };
  
    var latestData;
  
    fetch(
      "https://rxxa5z0s7l.execute-api.eu-west-3.amazonaws.com/dev",
      requestOptions
    )
      .then((response) => response.text())
      .then((result) => storeData(JSON.parse(result)));
  }

  function storeData(data){
    distance = data[0]["distance"]
    state = data[0]["status"]
    ts = data[1]["timestamp"]
    
    var date = ""
    for (i = 0; i < 10; i++)
        date += ts[i]
    
    var time = ""
    for (i = 11; i < ts.length; i++)
        time += ts[i]
    
    document.getElementById("lastLightOn").innerHTML = date + "<br><span class='text-warning'> At: </span>" + time

    if (state == "CLOSED"){
        document.getElementById("statusCard").classList.remove("bg-success");
        document.getElementById("statusCard").classList.add("bg-warning");
        document.getElementById("status").innerText = state;
    }
    else if (state == "OPEN"){
        document.getElementById("statusCard").classList.remove("bg-warning");
        document.getElementById("statusCard").classList.add("bg-success");
        document.getElementById("status").innerText = state;
    }
    else{
        document.getElementById("statusCard").classList.remove("bg-warning");
        document.getElementById("statusCard").classList.remove("bg-success");
        document.getElementById("statusCard").classList.add("bg-danger");
        document.getElementById("status").innerText = "Connection error!";
    }

    document.getElementById("distance").innerText = distance.toPrecision(3) / 10 + " cm"

    var lastDay = "";
    lastDay += date[0]
    lastDay += date[1]

    var lightOnNumberD = 0

    for (i = 0; i < data.length; i++){
      var tday = "";
      tday = data[i]["timestamp"][0] + data[i]["timestamp"][1]
      if(tday == lastDay){
        lightOnNumberD++
      }
    }

    var lastHour = "";
    lastHour += time[0]
    lastHour += time[1]

    var lightOnNumberH = 0

    for (i = 0; i < data.length; i++){
      var thour = "";
      thour = data[i]["timestamp"][11] + data[i]["timestamp"][12]
      if(thour == lastHour){
        lightOnNumberH++
      }
    }

    var lightOnDistances = [];
    var s = 0;
    for(i = 0; i < data.length; i++){
      if(data[i]["status"] == "OPEN" && data[i]["distance"] != -2){
        lightOnDistances.push(data[i]["distance"])
        s += data[i]["distance"]
      }
    }
    var meanDistance = s / lightOnDistances.length

    document.getElementById("LD").innerText = lightOnNumberD
    document.getElementById("LH").innerText = lightOnNumberH
    document.getElementById("MD").innerText = meanDistance.toPrecision(3) / 10 + " cm"
  }

  function init(){
    callAPI();
  }