from flask import Flask, render_template, request
import subprocess
import os

app = Flask(__name__)

@app.route('/')
def home():
    return render_template('index.html')


@app.route('/scan', methods=['POST'])
def scan():
    target = request.form['target']

    scanner_path = os.path.join("build", "scanner")

    result = subprocess.check_output([scanner_path, target]).decode()

    return render_template('result.html', result=result)


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

