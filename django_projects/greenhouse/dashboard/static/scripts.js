function updatePage(result) {
	document.getElementById('temperature').innerHTML = result.temperature;
}

function logResult(result) {
	console.log(result);
	return result;
}

function logError(error) {
	console.log('Looks like there was a problem\n', error);
}

function validateResponse(response) {
	if (!response.ok) {
		throw Error(response.statusText);
	}
	return response;
}

function readResponseAsJson(response) {
	return response.json();
}

function fetchJSON(pathToResource) {
	fetch(pathToResource)
	.then(validateResponse)
	.then(readResponseAsJson)
	.then(logResult)
	.then(updatePage)
	.catch(logError)
}