from flask import Flask, render_template, request
from cs50 import SQL


app = Flask(__name__)
db = SQL('sqlite:///name-data.db')

# db = sqlite3.connect('name-data.db').cursor()
# db.execute('''CREATE TABLE IF NOT EXISTS users(
#            id INTEGER PRIMARY KEY,
#                     name TEXT,
#                     age INTEGER
#                   )''')

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=["POST"])
def register():
    name = request.form.get('name')
    age = request.form.get('age')
    db.execute('INSERT into users (name, age) VALUES (?, ?)', name, age)
    return render_template('register.html', name=name, age=age)

@app.route('/users')
def users():
    registered_users = db.execute('SELECT name, age FROM users')
    return render_template('users.html', users=registered_users)
