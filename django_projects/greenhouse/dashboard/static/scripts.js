// Gauge code

/*

google.charts.load('current', {'packages':['gauge']});
google.charts.setOnLoadCallback(drawChart);

function drawChart() {
	var data = google.visualization.arrayToDataTable([
	['Label', 'Value'],
	['Temperature', 25],
	['Humidity', 10]
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

*/

// POLLING

setInterval(function() {
	fetchJSON('http://192.168.1.86/data')
}, 1000);

// FETCH REQUEST -- GET DATA

function fetchJSON(pathToResource) {
	fetch(pathToResource, {
		method: 'GET',
	})
	.then(function(response) {
		if (!response.ok) {
			throw Error(response.statusText);
		}
		return response.json();
	})
	.then(result => {
		document.getElementById("system_temperature").innerText = result.temperature;
		document.getElementById("system_humidity").innerText = result.humidity;
		document.getElementById("water_level").innerText = result.water;
		document.getElementById("light_enabled").innerText = result.light;
	})
	.catch(error => console.log('look like there was a problem\n', error))
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

// FETCH REQUEST -- SET DATA
function setTemperature() {
	console.log(document.getElementById("temperature_setpoint").value)
	fetch("http://192.168.1.86/temperature", {
		method: 'POST',
		body: String(document.getElementById("temperature_setpoint").value)
	})
	.then(function(response) {
		if (!response.ok) {
			throw Error(response.statusText);
		}
		return response;
	})
	.catch(error => console.log('look like there was a problem\n', error))
}

function setHumidity() {
	fetch("http://192.168.1.86/humidity", {
		method: 'POST',
		body: String(document.getElementById("humidity_setpoint").selectedIndex),
	})
	.then(function(response) {
		if (!response.ok) {
			throw Error(response.statusText);
		}
		return response;
	})
	.catch(error => console.log('look like there was a problem\n', error))
}

function setLight() {
	fetch("http://192.168.1.86/light", {
		method: 'POST',
		body: String(document.getElementById("light_setpoint").value),
	})
	.then(function(response) {
		if (!response.ok) {
			throw Error(response.statusText);
		}
		return response;
	})
	.catch(error => console.log('look like there was a problem\n', error))
}

function waterPlant() {
	fetch("http://192.168.1.86/water", {
		method: 'POST',
		body: String(document.getElementById("water_setpoint").value)
	})
	.then(function(response) {
		if (!response.ok) {
			throw Error(response.statusText);
		}
		return response;
	})
	.catch(error => console.log('look like there was a problem\n', error))
}