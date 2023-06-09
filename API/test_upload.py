import random
import time
import requests
import json
from dotenv import load_dotenv
import os

load_dotenv()

URL = "http://localhost:5000/uploads"
id_device = "BFD-0LS-X0Y"

headers = {
    'Content-Type': 'application/json',
    'X-API-Key': os.getenv('API_KEY')

}

while True:
    value = random.randint(0, 100)
    body = {
        'metric_type': 1,
        'value': value,
        'id_device': id_device
    }
    r = requests.post(URL,data=json.dumps(body),headers=headers)
    print(r,r.text)
    time.sleep(1)
