document.addEventListener('DOMContentLoaded', function () {
	const executionForm = document.getElementById('execution');
	if (executionForm) {
		executionForm.addEventListener('submit', executeScript);
	}

	const scriptInput = document.getElementById('script');
	if (scriptInput) {
		scriptInput.focus();
	}
});

function executeScript(event) {
	event.preventDefault();

	const scriptName = document.getElementById('script').value.trim();

	if (!scriptName) {
		showResult('Please enter a script name', 'error');
		return;
	}

	if (scriptName.includes('..') || scriptName.startsWith('/')) {
		showResult('Invalid script name', 'error');
		return;
	}

	showResult('🚀 Redirecting to the script...', 'info');

	const cgiUrl = '/' + scriptName;

	console.log(`Redirecting to CGI script: ${cgiUrl}`);

	setTimeout(() => {
		window.location.href = cgiUrl;
	}, 1000);
}

function showResult(message, type) {
	let resultDiv = document.getElementById('result');
	if (!resultDiv) {
		createResultDiv();
		resultDiv = document.getElementById('result');
	}

	resultDiv.innerHTML = message;
	resultDiv.className = type;
	resultDiv.style.display = 'block';

	console.log(`Showing result: [${type.toUpperCase()}] ${message}`);
}

function createResultDiv() {
	const resultDiv = document.createElement('div');
	resultDiv.id = 'result';
	resultDiv.style.marginTop = '20px';
	resultDiv.style.padding = '15px';
	resultDiv.style.borderRadius = '10px';
	resultDiv.style.fontWeight = 'bold';
	resultDiv.style.display = 'none';

	const container = document.querySelector('.container');
	if (container) {
		container.appendChild(resultDiv);
	}
}