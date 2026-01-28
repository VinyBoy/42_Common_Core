document.addEventListener('DOMContentLoaded', function() {
    const deleteForm = document.getElementById('deleteForm');
    if (deleteForm) {
        deleteForm.addEventListener('submit', deleteFile);
    }

    const filenameInput = document.getElementById('filename');
    if (filenameInput) {
        filenameInput.focus();
    }
});

function deleteFile(event) {
    event.preventDefault();
    
    const filename = document.getElementById('filename').value.trim();
    
    if (!filename) {
        showResult('Enter a filename', 'error');
        return;
    }

    if (filename.includes('..') || filename.startsWith('/')) {
        showResult('Invalid filename', 'error');
        return;
    }

    showResult('Deleting...', 'info');

    const deleteUrl = '/' + filename;
    
    console.log(`Attempting to delete: ${deleteUrl}`);

    fetch(deleteUrl, {
        method: 'DELETE',
        headers: {
            'Content-Type': 'application/json'
        }
    })
    .then(response => {
        console.log(`DELETE response status: ${response.status}`);
        return response.text().then(text => ({
            status: response.status,
            statusText: response.statusText,
            body: text
        }));
    })
    .then(result => {
        console.log('DELETE result:', result);
        
        if (result.status === 200 || result.status === 204) {
            showResult(`✅ File "${filename}" deleted successfully!`, 'success');
            document.getElementById('filename').value = '';
            console.log(`Successfully deleted: ${filename}`);
        } else if (result.status === 404) {
            showResult(`❌ File "${filename}" not found`, 'error');
            console.log(`File not found: ${filename}`);
        } else if (result.status === 403) {
            showResult(`❌ Permission denied to delete "${filename}"`, 'error');
            console.log(`Permission denied: ${filename}`);
        } else if (result.status === 405) {
            showResult(`❌ DELETE Method not allowed "${filename}"`, 'error');
            console.log(`Method not allowed: ${filename}`);
        } else {
            const errorMsg = result.body.substring(0, 100);
            showResult(`❌ Error ${result.status}: ${errorMsg}`, 'error');
            console.error(`Delete failed with status ${result.status}:`, result.body);
        }
    })
    .catch(error => {
        const errorMsg = `Network error: ${error.message}`;
        showResult(`❌ ${errorMsg}`, 'error');
        console.error('Network error during delete:', error);
    });
}

function showResult(message, type) {
    const resultDiv = document.getElementById('result');
    if (!resultDiv) return;
    
    resultDiv.innerHTML = message;
    resultDiv.className = type;
    resultDiv.style.display = 'block';
    
    console.log(`Showing result: [${type.toUpperCase()}] ${message}`);

    if (type === 'success') {
        setTimeout(() => {
            resultDiv.style.display = 'none';
        }, 5000);
    }
}
