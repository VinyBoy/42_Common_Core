#!/usr/bin/env python3
# filepath: /home/oztozdem/github_ozkainry/Webserv/cgi-bin/random.py

import random
import os
import urllib.parse

query = os.environ.get("QUERY_STRING", "")
params = urllib.parse.parse_qs(query)

min_val = int(params.get('min', ['1'])[0])
max_val = int(params.get('max', ['100'])[0])

number = random.randint(min_val, max_val)

print(f"""<!DOCTYPE html>
<html>
<head>
		<meta charset="UTF-8">
		<meta name="viewport" content="width=device-width, initial-scale=1.0">
		<title>Random Number Generator - Webserv</title>
		<style>
				body {{
						font-family: "Segoe UI", Roboto, sans-serif;
						background: linear-gradient(135deg, #0F2027 0%, #203A43 50%, #2C5364 100%);
						color: #333;
						display: flex;
						justify-content: center;
						align-items: center;
						min-height: 100vh;
						margin: 0;
						text-align: center;
				}}

				.container {{
						background: rgba(255, 255, 255, 0.95);
						color: #2C5364;
						padding: 40px;
						border-radius: 20px;
						max-width: 500px;
						box-shadow: 0 15px 35px rgba(0, 0, 0, 0.3);
						border: 1px solid rgba(0, 212, 255, 0.2);
				}}

				h1 {{
						color: #00D4FF;
						font-size: 36px;
						letter-spacing: 2px;
						text-shadow: 0 2px 4px rgba(0, 212, 255, 0.3);
						margin-bottom: 30px;
						border-bottom: 2px solid #00D4FF;
						padding-bottom: 0.5rem;
				}}

				.number {{
						font-size: 72px;
						color: #00D4FF;
						font-weight: bold;
						text-shadow: 2px 2px 8px rgba(0, 212, 255, 0.5);
						margin: 30px 0;
						padding: 20px;
						background: rgba(0, 212, 255, 0.1);
						border-radius: 15px;
						border: 2px solid rgba(0, 212, 255, 0.3);
				}}

				.range {{
						font-size: 18px;
						color: #2C5364;
						margin: 20px 0;
						font-weight: bold;
				}}

				form {{
						margin-top: 30px;
						display: flex;
						flex-direction: column;
						gap: 15px;
						align-items: center;
				}}

				.input-group {{
						display: flex;
						gap: 10px;
						align-items: center;
				}}

				input[type="number"] {{
						padding: 12px 15px;
						border: 2px solid rgba(0, 212, 255, 0.3);
						border-radius: 10px;
						font-size: 16px;
						background: rgba(255, 255, 255, 0.8);
						color: #2C5364;
						text-align: center;
						width: 80px;
				}}

				input[type="number"]:focus {{
						outline: none;
						border-color: #00D4FF;
						box-shadow: 0 0 10px rgba(0, 212, 255, 0.3);
				}}

				button {{
						background: linear-gradient(135deg, #00D4FF 0%, #0099CC 100%);
						color: white;
						border: none;
						padding: 15px 30px;
						font-size: 16px;
						font-weight: bold;
						border-radius: 50px;
						cursor: pointer;
						transition: all 0.3s;
						box-shadow: 0 5px 15px rgba(0, 212, 255, 0.3);
				}}

				button:hover {{
						transform: scale(1.1);
						box-shadow: 0 8px 20px rgba(0, 212, 255, 0.5);
				}}

				.back-btn {{
						display: inline-block;
						padding: 12px 25px;
						background: linear-gradient(135deg, #9b59b6, #8e44ad);
						color: white;
						text-decoration: none;
						border-radius: 50px;
						margin-top: 20px;
						font-weight: bold;
						transition: transform 0.3s;
						box-shadow: 0 5px 15px rgba(155, 89, 182, 0.3);
				}}

				.back-btn:hover {{
						transform: scale(1.1);
						box-shadow: 0 8px 20px rgba(155, 89, 182, 0.5);
				}}

				label {{
						font-weight: bold;
						color: #2C5364;
				}}
		</style>
</head>
<body>
		<div class="container">
				<h1>🎲 Random Number Generator</h1>
				<div class="number">{number}</div>
				<div class="range">📊 Range: {min_val} - {max_val}</div>
				
				<form method="GET">
						<div class="input-group">
								<label for="min">Min:</label>
								<input type="number" id="min" name="min" value="{min_val}" min="1" max="9999">
								<label for="max">Max:</label>
								<input type="number" id="max" name="max" value="{max_val}" min="1" max="9999">
						</div>
						<button type="submit">🎯 Generate New Number</button>
				</form>
				
				<a href="/cgi.html" class="back-btn">⚙️ Back to CGI</a>
		</div>
</body>
</html>""")