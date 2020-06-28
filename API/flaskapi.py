# -*- coding: utf-8 -*-
"""
Created on Thu Jun 25 18:40:55 2020

@author: SamSung
"""

from flask import Flask, jsonify

app = Flask(__name__)

app.config["DEBUG"] = True

"""
    Hàm này dùng để trả về nhiệt độ hiện tại

"""

@app.route('/', methods=['GET'])
def home():
    return "Hello MR.NAM - Restful API with Flask"


"""
    Nếu gõ url http:/localhost:5000 -> gọi đến hàm home()
    / là Root,
    @app.route -> tạo bộ định tuyến với với đường url | Phương thức HTTP
"""



@app.route('/iot', methods=['GET'])
def getNextFromCurrent():
    current_temp = 0.0
    next_temp = 1.0
    
    return jsonify({
        'current': current_temp,
        'next_temp': next_temp
        })

@app.route('/iot/<float:temperature>', methods=['GET'])
def getNext(temperature):
    next_temp = temperature + 1.0
    return jsonify({'next': next_temp})

if __name__ == '__main__':
    app.run()