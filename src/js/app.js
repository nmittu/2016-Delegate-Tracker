var url = "http://www.realclearpolitics.com/json/ap_results/2016_primaries/superdelegates.json";


function send(){
	var XHR = new XMLHttpRequest();
	XHR.open("GET", url, false);
	XHR.send();
	
	var json = JSON.parse(XHR.responseText);
	//console.log(XHR.responseText);
	var dictionary = {
		"CLINTON": (json.delegates.clinton -  json.superdelegates.clinton).toString()+ " + " + json.superdelegates.clinton.toString() + " = " + json.delegates.clinton.toString(),
		"SANDERS": (json.delegates.sanders -  json.superdelegates.sanders).toString()+ " + " + json.superdelegates.sanders.toString() + " = " + json.delegates.sanders.toString(),
		"TRUMP": json.delegates.trump.toString(),
		"CRUZ": json.delegates.cruz.toString(),
		"RUBIO": json.delegates.rubio.toString(),
		"KASICH": json.delegates.kasich.toString(),
		"CARSON": json.delegates.carson.toString()
	};
	
	Pebble.sendAppMessage(dictionary,
		function(e){
			console.log('Index Sent');
		},
		function(e){
			console.log('Error Sending Weather To Pebble!');
		}
	);
}

Pebble.addEventListener('ready',
  function(e){
    console.log('PebbleKit JS ready!');
		
		send();
	}
);