from dotenv import load_dotenv
import os
from flask import Flask, request, jsonify
import mysql.connector

app = Flask(__name__)

load_dotenv()

MYSQL_HOST = os.getenv('MYSQL_HOST')
MYSQL_USER = os.getenv('MYSQL_USER')
MYSQL_PASSWD = os.getenv('MYSQL_PASSWD')
MYSQL_DATABASE = os.getenv('MYSQL_DATABASE')
API_SECRET = os.getenv('API_KEY')

db = mysql.connector.connect(
    host=MYSQL_HOST,
    user=MYSQL_USER,
    password=MYSQL_PASSWD,
    database=MYSQL_DATABASE
)

cursor = db.cursor()

def check_device(id_device):
    cursor.execute("SELECT id_device FROM device WHERE id_device = %s", (id_device,))
    result = cursor.fetchone()

    if result is None:
        return False
    else:
        return True

#@app.before_request
def authenticate():
    api_key = request.headers.get('X-API-Key')

    if not api_key or api_key != API_SECRET:
        return jsonify({'message': 'Invalid API key'}), 401

@app.route('/uploads', methods=['POST'])
def upload_data():
    data = request.json

    metric_type = data['type']
    value = data['value']
    id_device = data['id_sensor']

    if not check_device(id_device):
        return jsonify({'message': 'Invalid device ID'}), 400

    query = "INSERT INTO sensor_data (id_device, metric_type, value) VALUES (%s, %s, %s)"
    values = (id_device, metric_type, value)
    cursor.execute(query, values)
    db.commit()

    return jsonify({'message': 'success'}), 200

if __name__ == '__main__':
    app.run()