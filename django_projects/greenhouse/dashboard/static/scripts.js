// gauge

google.charts.load('current', {'packages':['gauge']});
google.charts.setOnLoadCallback(drawChart);

function drawChart() {
	var data = google.visualization.arrayToDataTable([
	['Label', 'Value'],
	['Temperature', 80],
	]);

	var options = {
		width: document.getElementById('system-monitor').width, height: document.height/4,
		redFrom: 90, redTo: 100,
		yellowFrom:75, yellowTo: 90,
		minorTicks: 5,
	};

	var chart = new google.visualization.Gauge(document.getElementById('chart_div'));

	chart.draw(data, options);

	function updateTemperature(value) {
		data.setValue(0, 1, value);
		chart.draw(data, options);
	}

	setInterval(function() {
		fetchJSON('http://192.168.1.163/temperature', updateTemperature)
	}, 1000);
}

function updateTemperatureSetpoint(val) {
	document.getElementById('temperatureInput').value = val;
	// make fetch request to ESP32
}

// fetch request


function logError(error) {
	console.log('Looks like there was a problem\n', error);
}


function logResult(result) {
	console.log(result.temperature);
	return result.temperature;
}

function readResponseAsJson(response) {
	return response.json();
}

function validateResponse(response) {
	if (!response.ok) {
		throw Error(response.statusText);
	}
	return response;
}

function fetchJSON(pathToResource, callback) {
	fetch(pathToResource, {
		method: 'GET',
	})
	.then(validateResponse)
	.then(readResponseAsJson)
	.then(logResult)
	.then(callback)
	.catch(logError)
}