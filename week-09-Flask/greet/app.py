
#  Run This file using flask run app.js

from flask import Flask, render_template, request

#  Creating Flask app, since name can be changed any time instead of hardcoding the name, we used __name__ .
app = Flask(__name__)


#  Function below @app.route("/") will be exectured if user visits "/" route.
@app.route("/")
def index():
    name = request.args.get("name", "world")
    # request.args.get will look for a GET request made by user with "name" key, "world" is default if no such key is found.
    return render_template("index.html", name=name)


# GET method is default, but in order to use POST method, we'll have to declare methods parameter. And also in index.html, method in form will be set as method="post" .
@app.route("/greet", methods=["POST"])
def greet():
    return render_template("greet.html", name=request.form.get("name", "world"))


# For GET :- request.args.get(key)
# For POST :- request.form.get(key)
# It is how it is we can't do anything.

''' We can use both GET and POST simultaneously using,
 if request.method == "POST":
        return render_template("greet.html", name=request.form.get("name"))
otherwise empty string will be returned, i.e., `hello, ` will be result in webpage.
'''
