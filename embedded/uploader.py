import random
import time
import requests
import json
from dotenv import load_dotenv
import os

load_dotenv()

URL = f"https://{os.getenv('FLASK_HOST')}:5000/uploads"
id_device = "BFD-0LS-X0Y"

headers = {
    'Content-Type': 'application/json',
    'X-API-Key': os.getenv('API_KEY')
}

def upload_data(sensor,value):
    body = {
        'metric_type': sensor,
        'value': value,
        'id_device': id_device
    }
    try:
        r = requests.post(URL,data=json.dumps(body),headers=headers, verify=False)
    except requests.exceptions.ConnectionError as e:
        print(e)
    
