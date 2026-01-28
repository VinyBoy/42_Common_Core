#!/usr/bin/env python3
# filepath: /home/oztozdem/github_ozkainry/Webserv/cgi-bin/env.py

import os

print("""<!DOCTYPE html>
<html>
<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<title>Environment Variables - Webserv</title>
		<style>
				body {
						font-family: "Segoe UI", Roboto, sans-serif;
						background: linear-gradient(135deg, #0F2027 0%, #203A43 50%, #2C5364 100%);
						color: #333;
						margin: 0;
						padding: 20px;
						min-height: 100vh;
				}

				h1 {
						color: #00D4FF;
						font-size: 48px;
						letter-spacing: 3px;
						text-shadow: 2px 2px 8px rgba(0, 212, 255, 0.5);
						text-align: center;
						margin-bottom: 30px;
				}

				.container {
						background: rgba(255, 255, 255, 0.95);
						color: #2C5364;
						padding: 30px;
						border-radius: 20px;
						max-width: 1200px;
						margin: 0 auto;
						box-shadow: 0 15px 35px rgba(0, 0, 0, 0.3);
						border: 1px solid rgba(0, 212, 255, 0.2);
				}

				h2 {
						color: #00D4FF;
						font-size: 24px;
						letter-spacing: 2px;
						margin-bottom: 20px;
						text-shadow: 0 2px 4px rgba(0, 212, 255, 0.3);
						border-bottom: 2px solid #00D4FF;
						padding-bottom: 0.5rem;
						text-align: center;
				}

				table {
						width: 100%;
						border-collapse: collapse;
						margin-top: 20px;
						background: rgba(255, 255, 255, 0.8);
						border-radius: 10px;
						overflow: hidden;
						box-shadow: 0 5px 15px rgba(0, 0, 0, 0.1);
				}

				th, td {
						padding: 12px 15px;
						text-align: left;
						border-bottom: 1px solid rgba(0, 212, 255, 0.2);
				}

				th {
						background: linear-gradient(135deg, #00D4FF 0%, #0099CC 100%);
						color: white;
						font-weight: bold;
						letter-spacing: 1px;
				}

				tr:nth-child(even) {
						background: rgba(0, 212, 255, 0.1);
				}

				tr:hover {
						background: rgba(0, 212, 255, 0.2);
						transition: background 0.3s ease;
				}

				td:first-child {
						font-weight: bold;
						color: #2C5364;
				}

				.back-btn {
						display: inline-block;
						padding: 15px 40px;
						background: linear-gradient(135deg, #00D4FF 0%, #0099CC 100%);
						color: white;
						text-decoration: none;
						border-radius: 50px;
						margin: 20px auto;
						font-weight: bold;
						transition: transform 0.3s;
						box-shadow: 0 5px 15px rgba(0, 212, 255, 0.3);
						text-align: center;
						display: block;
						width: fit-content;
				}

				.back-btn:hover {
						transform: scale(1.1);
						box-shadow: 0 8px 20px rgba(0, 212, 255, 0.5);
				}
		</style>
</head>
<body>
		<h1>🌐 CGI Environment</h1>
		<div class="container">
				<h2>📋 Environment Variables</h2>
				<table>
						<tr>
								<th>Variable</th>
								<th>Value</th>
						</tr>""")

for key, value in sorted(os.environ.items()):
		print(f"						<tr><td>{key}</td><td>{value}</td></tr>")

print("""				</table>
				<a href="/cgi.html" class="back-btn">⚙️ Back to CGI</a>
		</div>
</body>
</html>""")