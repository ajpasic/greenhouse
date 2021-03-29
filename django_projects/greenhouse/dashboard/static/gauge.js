google.charts.load('current', {'packages':['gauge']});
google.charts.setOnLoadCallback(drawChart);

function drawChart() {

	var data = google.visualization.arrayToDataTable([
	['Label', 'Value'],
	['Temperature', 80],
	['Humidity', 55],
	['Lighting', 68]
	]);

	var options = {
		width: document.getElementById('system-monitor').width, height: document.height/4,
		redFrom: 90, redTo: 100,
		yellowFrom:75, yellowTo: 90,
		minorTicks: 5,
	};

	var chart = new google.visualization.Gauge(document.getElementById('chart_div'));

	chart.draw(data, options);

	setInterval(function() {
	data.setValue(0, 1, 40 + Math.round(60 * Math.random()));
	chart.draw(data, options);
	}, 13000);
	setInterval(function() {
	data.setValue(1, 1, 40 + Math.round(60 * Math.random()));
	chart.draw(data, options);
	}, 5000);
	setInterval(function() {
	data.setValue(2, 1, 60 + Math.round(20 * Math.random()));
	chart.draw(data, options);
	}, 26000);
}

function updateTemperatureSetpoint(val) {
	document.getElementById('temperatureInput').value = val;
	// make fetch request to ESP32
}

function updateHumiditySetpoint(val) {
	document.getElementById('humidityInput').value = val;
	// make fetch request to ESP32
}