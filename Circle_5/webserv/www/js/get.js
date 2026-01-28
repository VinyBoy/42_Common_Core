function escapeHtml(text) {
	const div = document.createElement('div');
	div.textContent = text;
	return div.innerHTML;
}

function testUrl(url) {
	const responseBox = document.getElementById('responseBox');
	responseBox.innerHTML = '<div style="color: #00D4FF;">🔄 Loading response for: ' + url + '</div>';

	fetch(url)
		.then(response => {
			const headers = [];
			headers.push(`HTTP/1.1 ${response.status} ${response.statusText}`);

			for (let [key, value] of response.headers.entries()) {
				headers.push(`${key}: ${value}`);
			}

			return response.text().then(body => {
				const headerText = headers.join('\n');
				const bodyText = escapeHtml(body);

				responseBox.innerHTML = `<div style="color: #00D4FF; font-weight: bold;">📡 Response for: ${url}</div>\n\n<div style="color: #00D4FF;">${headerText}</div>\n\n<div style="color: #00D4FF; border-top: 1px solid #ccc; padding-top: 10px;">${bodyText}</div>`;
				responseBox.style.whiteSpace = 'pre-wrap';
			});
		})
		.catch(error => {
			responseBox.innerHTML = `<div style="color: #e74c3c;">❌ Error fetching ${url}</div>\n<div style="color: #00D4FF;">${error.message}</div>`;
			responseBox.style.whiteSpace = 'pre-wrap';
		});
}

document.getElementById('urlTestForm').addEventListener('submit', function (e) {
	e.preventDefault();
	const url = document.getElementById('testUrl').value;
	if (url) {
		testUrl(url);
		document.getElementById('testUrl').value = '';
	} else {
		alert('Please enter a URL to test');
	}
});

window.addEventListener('load', function () {
	testUrl('/get.html');
});