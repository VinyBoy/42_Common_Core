let selectedFiles = [];

const FILE_EXTENSIONS = {
    text: [
        'txt', 'html', 'css', 'js', 'json', 'md', 'xml', 'conf', 'log',
        'cpp', 'hpp', 'c', 'h', 'py', 'php', 'java', 'cs', 'rb', 'go',
        'rs', 'swift', 'kt', 'sql', 'sh', 'bat', 'ps1', 'yml', 'yaml',
        'csv', 'tsv', 'ini', 'cfg', 'properties', 'htaccess', 'gitignore'
    ],
    image: ['jpg', 'jpeg', 'png', 'gif', 'bmp', 'svg', 'webp'],
    document: ['pdf', 'doc', 'docx', 'xls', 'xlsx', 'ppt', 'pptx'],
    archive: ['zip', 'rar', '7z', 'tar', 'gz', 'bz2'],
    audio: ['mp3', 'wav', 'flac', 'aac'],
    video: ['mp4', 'avi', 'mov', 'wmv', 'flv'],
    executable: ['exe', 'bin', 'iso', 'dmg']
};

function sanitizeFilename(filename) {
    return filename
        .replace(/\s+/g, '_')
        .replace(/[<>:"/\\|?*]/g, '')
        .replace(/\.+/g, '.');
}

function showResult(message, type, targetId = 'result') {
    let resultDiv = document.getElementById(targetId);
    if (!resultDiv) {
        createResultDiv(targetId);
        resultDiv = document.getElementById(targetId);
    }

    resultDiv.innerHTML = message;
    resultDiv.className = `result-notification ${type}`;
    resultDiv.style.display = 'block';

    console.log(`Showing result: [${type.toUpperCase()}] ${message}`);

    // Auto-hide success messages after 3 seconds
    if (type === 'success' || type === 'info') {
        setTimeout(() => {
            if (resultDiv) {
                resultDiv.style.display = 'none';
            }
        }, 3000);
    }
}

function createResultDiv(targetId = 'result') {
    const resultDiv = document.createElement('div');
    resultDiv.id = targetId;
    resultDiv.style.marginTop = '20px';
    resultDiv.style.padding = '15px';
    resultDiv.style.borderRadius = '10px';
    resultDiv.style.fontWeight = 'bold';
    resultDiv.style.display = 'none';

    // Add CSS classes based on type
    if (!document.getElementById('result-styles')) {
        const style = document.createElement('style');
        style.id = 'result-styles';
        style.textContent = `
            .result-notification.success {
                background-color: #d4edda;
                color: #155724;
                border: 1px solid #c3e6cb;
            }
            .result-notification.error {
                background-color: #f8d7da;
                color: #721c24;
                border: 1px solid #f5c6cb;
            }
            .result-notification.info {
                background-color: #d1ecf1;
                color: #0c5460;
                border: 1px solid #bee5eb;
            }
            .result-notification.warning {
                background-color: #fff3cd;
                color: #856404;
                border: 1px solid #ffeaa7;
            }
        `;
        document.head.appendChild(style);
    }

    // Determine where to place the result div based on the targetId
    let container;
    if (targetId === 'custom-result') {
        // Place near custom file creation section
        const customSection = document.querySelector('.custom-file-section') ||
            document.querySelector('#customContent')?.parentElement ||
            document.querySelector('.container');
        container = customSection;
    } else if (targetId === 'upload-result') {
        // Place near file upload section
        const uploadSection = document.querySelector('.upload-section') ||
            document.querySelector('#fileInfo')?.parentElement ||
            document.querySelector('.container');
        container = uploadSection;
    } else {
        // Default placement
        container = document.querySelector('.container') || document.body;
    }

    container.appendChild(resultDiv);
}

document.addEventListener('DOMContentLoaded', function () {
    document.getElementById('fileInput').addEventListener('change', function (e) {
        selectedFiles = Array.from(e.target.files);
        displayFileInfo();
    });

    const fileSelector = document.querySelector('.file-selector');

    if (fileSelector) {
        fileSelector.addEventListener('dragover', function (e) {
            e.preventDefault();
            this.classList.add('dragover');
        });

        fileSelector.addEventListener('dragleave', function (e) {
            e.preventDefault();
            this.classList.remove('dragover');
        });

        fileSelector.addEventListener('drop', function (e) {
            e.preventDefault();
            this.classList.remove('dragover');
            selectedFiles = Array.from(e.dataTransfer.files);
            displayFileInfo();
        });
    }
});

function displayFileInfo() {
    const fileInfoDiv = document.getElementById('fileInfo');
    if (!fileInfoDiv) return;

    if (selectedFiles.length === 0) {
        fileInfoDiv.innerHTML = '';
        return;
    }

    let html = '<div class="file-info"><strong>Selected Files:</strong><br>';
    selectedFiles.forEach((file, index) => {
        const size = formatFileSize(file.size);
        const type = getFileType(file.name);
        html += `${index + 1}. ${file.name} (${size}) - ${type}<br>`;
    });
    html += '</div>';
    fileInfoDiv.innerHTML = html;
}

function getFileType(filename) {
    const ext = filename.split('.').pop().toLowerCase();

    if (FILE_EXTENSIONS.text.includes(ext)) return 'Text';
    if (FILE_EXTENSIONS.image.includes(ext)) return 'Image';
    if (FILE_EXTENSIONS.document.includes(ext)) return 'Document';
    if (FILE_EXTENSIONS.archive.includes(ext)) return 'Archive';
    if (FILE_EXTENSIONS.audio.includes(ext)) return 'Audio';
    if (FILE_EXTENSIONS.video.includes(ext)) return 'Video';
    if (FILE_EXTENSIONS.executable.includes(ext)) return 'Executable';
    return 'Binary';
}

function formatFileSize(bytes) {
    if (bytes === 0) return '0 B';
    const k = 1024;
    const sizes = ['B', 'KB', 'MB', 'GB', 'TB'];
    const i = Math.floor(Math.log(bytes) / Math.log(k));
    return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + ' ' + sizes[i];
}

function createCustomFile() {
    const filename = document.getElementById('customFilename').value.trim();
    const content = document.getElementById('customContent').value;

    if (!filename) {
        showResult('Please enter a filename', 'error', 'custom-result');
        document.getElementById('customFilename').focus();
        return;
    }

    if (!content) {
        showResult('Please enter some content for the file', 'error', 'custom-result');
        document.getElementById('customContent').focus();
        return;
    }

    if (filename.includes('..') || filename.startsWith('/') || filename.includes('\\')) {
        showResult('Invalid filename. Please use a simple filename without path separators.', 'error', 'custom-result');
        return;
    }

    let finalFilename = filename;
    if (!filename.includes('.')) {
        finalFilename = filename + '.txt';
    }

    console.log(`Creating custom file: ${finalFilename} (${content.length} characters)`);

    showResult('📤 Uploading custom file...', 'info', 'custom-result');

    uploadTextFile(finalFilename, content, 1, 1).then(result => {
        if (result.success) {
            document.getElementById('customFilename').value = '';
            document.getElementById('customContent').value = '';
            showResult(`✅ Custom file created successfully: ${finalFilename}`, 'success', 'custom-result');
            console.log(`Custom file created successfully: ${finalFilename}`);
        } else {
            showResult(`❌ Failed to create custom file: ${result.error || 'Unknown error'}`, 'error', 'custom-result');
        }
    });
}

function uploadSelectedFiles() {
    if (selectedFiles.length === 0) {
        showResult('No files selected. Please select files first!', 'warning', 'upload-result');
        return;
    }

    const totalFiles = selectedFiles.length;
    let completedUploads = 0;
    let successfulUploads = 0;

    console.log(`Starting upload of ${totalFiles} file(s)...`);
    showResult(`📤 Starting upload of ${totalFiles} file(s)...`, 'info', 'upload-result');

    selectedFiles.forEach((file, index) => {
        uploadSingleFile(file, index + 1, totalFiles).then(result => {
            completedUploads++;
            if (result.success) {
                successfulUploads++;
            }

            if (completedUploads === totalFiles) {
                console.log(`Upload completed: ${successfulUploads}/${totalFiles} files successful`);
                if (successfulUploads === totalFiles) {
                    showResult(`✅ All ${totalFiles} files uploaded successfully!`, 'success', 'upload-result');
                } else {
                    showResult(`⚠️ Upload completed: ${successfulUploads}/${totalFiles} files successful`, 'warning', 'upload-result');
                }

                selectedFiles = [];
                document.getElementById('fileInput').value = '';
                displayFileInfo();
            }
        });
    });
}

function uploadSingleFile(file, fileNumber, totalFiles) {
    return new Promise((resolve) => {
        console.log(`[${fileNumber}/${totalFiles}] Processing: ${file.name} (${formatFileSize(file.size)})`);

        const maxSize = 50 * 1024 * 1024;
        if (file.size > maxSize) {
            const errorMsg = `File too large: ${file.name} (${formatFileSize(file.size)}) - Max: ${formatFileSize(maxSize)}`;
            showResult(`❌ ${errorMsg}`, 'error', 'upload-result');
            console.error(errorMsg);
            resolve({ success: false, filename: file.name, error: 'File too large' });
            return;
        }

        const ext = file.name.split('.').pop().toLowerCase();
        const trulyTextExtensions = FILE_EXTENSIONS.text;

        if (trulyTextExtensions.includes(ext) &&
            (file.type.startsWith('text/') || file.type === 'application/json' || file.type === '')) {

            console.log(`[${fileNumber}/${totalFiles}] Detected as TEXT file: ${file.name}`);
            const reader = new FileReader();
            reader.onload = function (e) {
                uploadTextFile(file.name, e.target.result, fileNumber, totalFiles).then(resolve);
            };
            reader.onerror = function () {
                console.error(`Error reading text file: ${file.name}`);
                resolve({ success: false, filename: file.name, error: 'Failed to read file' });
            };
            reader.readAsText(file);

        } else {
            console.log(`[${fileNumber}/${totalFiles}] Detected as BINARY file: ${file.name} (type: ${file.type})`);
            uploadBinaryFile(file, fileNumber, totalFiles).then(resolve);
        }
    });
}

function uploadBinaryFile(file, fileNumber, totalFiles) {
    return new Promise((resolve) => {
        const reader = new FileReader();
        reader.onload = function (e) {
            const arrayBuffer = e.target.result;

            console.log(`[${fileNumber}/${totalFiles}] Uploading binary file: ${file.name} (${formatFileSize(arrayBuffer.byteLength)})`);

            const safeFilename = sanitizeFilename(file.name);
            fetch('/upload/' + safeFilename, {
                method: 'POST',
                body: arrayBuffer,
                headers: {
                    'Content-Type': 'application/octet-stream',
                    'Content-Length': arrayBuffer.byteLength.toString()
                }
            })
                .then(response => {
                    return response.text().then(text => ({
                        status: response.status,
                        statusText: response.statusText,
                        body: text
                    }));
                })
                .then(result => {
                    if (result.status === 201) {
                        console.log(`[${fileNumber}/${totalFiles}] Binary upload SUCCESS: ${file.name}`);
                        resolve({
                            success: true,
                            filename: file.name,
                            status: result.status
                        });
                    } else if (result.status === 413) {
                        cleanup413Error(file.name);
                        const errorMsg = `File too large: ${file.name} (max size exceeded)`;
                        console.error(`[${fileNumber}/${totalFiles}] ${errorMsg}`);
                        resolve({
                            success: false,
                            filename: file.name,
                            error: errorMsg
                        });
                    } else {
                        const errorMsg = `Binary upload failed: ${file.name} (${result.status} ${result.statusText})`;
                        console.error(`[${fileNumber}/${totalFiles}] ${errorMsg}`, result.body);
                        resolve({
                            success: false,
                            filename: file.name,
                            error: `${result.status} ${result.statusText}`,
                            details: result.body
                        });
                    }
                })
                .catch(error => {
                    const errorMsg = `Binary upload error: ${file.name} - ${error.message}`;
                    console.error(`[${fileNumber}/${totalFiles}] ${errorMsg}`, error);
                    resolve({
                        success: false,
                        filename: file.name,
                        error: error.message
                    });
                });
        };

        reader.onerror = function () {
            console.error(`Error reading binary file: ${file.name}`);
            resolve({
                success: false,
                filename: file.name,
                error: 'Failed to read binary file'
            });
        };

        reader.readAsArrayBuffer(file);
    });
}

function uploadTextFile(filename, content, fileNumber, totalFiles) {
    console.log(`[${fileNumber}/${totalFiles}] Uploading text file: ${filename} (${content.length} characters)`);

    const safeFilename = sanitizeFilename(filename);
    return fetch('/upload/' + safeFilename, {
        method: 'POST',
        body: content,
        headers: {
            'Content-Type': 'text/plain;charset=UTF-8',
            'Content-Length': content.length.toString()
        }
    })
        .then(response => {
            return response.text().then(text => ({
                status: response.status,
                statusText: response.statusText,
                body: text
            }));
        })
        .then(result => {
            if (result.status === 201) {
                console.log(`[${fileNumber}/${totalFiles}] Text upload SUCCESS: ${filename}`);
                return {
                    success: true,
                    filename: filename,
                    status: result.status
                };
            } else if (result.status === 413) {
                cleanup413Error(filename);
                const errorMsg = `File too large: ${filename} (max size exceeded)`;
                console.error(`[${fileNumber}/${totalFiles}] ${errorMsg}`);
                return {
                    success: false,
                    filename: filename,
                    error: errorMsg
                };
            } else {
                const errorMsg = `Text upload failed: ${filename} (${result.status} ${result.statusText})`;
                console.error(`[${fileNumber}/${totalFiles}] ${errorMsg}`, result.body);
                return {
                    success: false,
                    filename: filename,
                    error: `${result.status} ${result.statusText}`,
                    details: result.body
                };
            }
        })
        .catch(error => {
            const errorMsg = `Text upload error: ${filename} - ${error.message}`;
            console.error(`[${fileNumber}/${totalFiles}] ${errorMsg}`, error);
            return {
                success: false,
                filename: filename,
                error: error.message
            };
        });
}

function cleanup413Error(filename) {
    console.log(`Attempting to cleanup partial file: ${filename}`);
    const safeFilename = sanitizeFilename(filename);
    fetch('/upload/' + safeFilename, {
        method: 'DELETE'
    })
        .then(response => {
            if (response.ok) {
                console.log(`Cleaned up partial file: ${filename}`);
            } else {
                console.warn(`Could not cleanup partial file ${filename}: ${response.status}`);
            }
        })
        .catch(error => {
            console.warn(`Could not cleanup partial file ${filename}:`, error);
        });
}

function quickUpload(filename, content) {
    console.log(`Quick upload: ${filename}`);
    showResult('🚀 Quick uploading file...', 'info', 'upload-result');

    uploadTextFile(filename, content, 1, 1).then(result => {
        if (result.success) {
            console.log(`Quick upload SUCCESS: ${filename}`);
            showResult(`✅ Quick upload successful: ${filename}`, 'success', 'upload-result');
        } else {
            console.log(`Quick upload FAILED: ${filename} - ${result.error}`);
            showResult(`❌ Quick upload failed: ${filename} - ${result.error}`, 'error', 'upload-result');
        }
    });
}