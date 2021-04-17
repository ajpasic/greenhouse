// gauge

google.charts.load('current', {'packages':['gauge']});
google.charts.setOnLoadCallback(drawChart);

function drawChart() {
	var data = google.visualization.arrayToDataTable([
	['Label', 'Value'],
	['Temperature', 25],
	]);

	var options = {
		width: document.getElementById('system-monitor').width, height: document.height/4,
		redFrom: 90, redTo: 100,
		yellowFrom:75, yellowTo: 90,
		minorTicks: 5,
		min: 20,
		max: 100
	};

	var chart = new google.visualization.Gauge(document.getElementById('chart_div'));
	chart.draw(data, options);

	function updateTemperature(value) {
		data.setValue(0, 1, value);
		chart.draw(data, options);
	}

	document.getElementById("get-temperature").addEventListener("click", function() {
		fetchJSON('http://192.168.1.163/temperature', updateTemperature);
	}, false);
}

// FETCH REQUEST -- DATA

function logError(error) {
	console.log('Looks like there was a problem\n', error);
}

function logResult(result) {
	console.log(result.temperature);
	return result.temperature;
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
	.then(response => response.json())
	.then(logResult)
	.then(callback)
	.catch(logError)
}

// FETCH REQUEST -- IMAGE

function fetchImage(pathToResource) {
	const image = document.getElementById('live-view');
	fetch(pathToResource, {
		method: 'GET',
	})
	.then(response => response.blob())
	.then(blob => {
		const objectURL = URL.createObjectURL(blob);
		image.src = objectURL;
		console.log(`image URL is ${String(objectURL)}`);
		console.log('image set -- debug');
	})
	.catch(logError)
}