import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

def place_order(userid, symbol, type, shares):
    share_data = lookup(symbol)
    if share_data == None:
        return apology('Enter Valid Share')
    # Checking if lil bro can afford it or not.
    price = float(share_data["price"])
    cash = int(db.execute('SELECT cash FROM users WHERE id = ?', userid)[0]["cash"])
    if shares*price > cash:
        return apology(f'You broke lil bruh..!')

    # Updating transactions table
    current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')  # Current time in 'YYYY-MM-DD HH:MM:SS' format
    db.execute('INSERT INTO transactions (userid,symbol, price, shares,type, time) VALUES (?, ?, ?, ?, ?, ?)', userid,symbol, price, shares,type, current_time)
    # type: 1 ->buy, -1 ->sell

    # Updating user_shares table
    initial_shares = db.execute('SELECT shares FROM user_shares WHERE userid = ? AND symbol = ?', userid, symbol)
    if initial_shares:
        # If the user already has shares for this symbol, update the share count and average cost
        initial_price = float(db.execute('SELECT price FROM user_shares WHERE userid = ? AND symbol = ?', userid, symbol)[0]["price"])
        initial_shares = int(initial_shares[0]["shares"])
        updated_shares = initial_shares + type*shares
        if updated_shares == 0:
            avg = 0
            db.execute('DELETE FROM user_shares WHERE symbol = ?', symbol)
            return redirect('/')

        avg = (initial_price*initial_shares + price*type*shares)/(updated_shares)
        print(updated_shares)
        print(avg)
        db.execute('UPDATE user_shares SET shares = ?, price = ? WHERE userid = ? AND symbol = ?',updated_shares, avg, userid, symbol)
    else:
        # If the user does not have shares for this symbol, insert a new record
        db.execute('INSERT INTO user_shares (userid, symbol, shares, price) VALUES (?, ?, ?, ?)', userid, symbol, shares, price)
    # Updating cash
    rem_cash = cash - (price*type*shares)
    db.execute('UPDATE users SET cash = ? WHERE id = ?', rem_cash, userid)

    return redirect('/')

def getUserData(userid):
    # data, data.symbol, data.shares, data.buy_price, data.current_price, data.pnl
    user_shares = db.execute("SELECT symbol, shares, price FROM user_shares WHERE userid = ?", userid)
    print(user_shares)
    user_data = []
    total = 0

    for share in user_shares:
        data = {}
        data["symbol"] = share['symbol']
        data["shares"] = share['shares']
        data["buy_price"] = share['price']
        data["current_price"] = lookup(share['symbol'])['price']
        print(data)
        data["pnl"] = float(data["current_price"]) * int(data["shares"]) - int(data["shares"]) * float(data["buy_price"])
        data["total"] = float(data["current_price"]) * int(data["shares"])
        total += data["total"]
        user_data.append(data)
    return user_data, total



@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    userid = session.get("user_id")
    user_data, total = getUserData(userid)
    # user["username"], user["current_cash"]
    user = db.execute("SELECT username, cash FROM users WHERE id = ?", userid)[0]
    user["total"] = user["cash"] + total
    print(user)
    return render_template("index.html", user=user, user_data=user_data)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        shares = request.form.get('shares')

        # Validating Order
        if shares =='':
            return apology('Enter Valid number of shares !')
        try:
            shares = int(shares)
            if shares < 1:
                return apology('Enter Valid number of shares !')
        except:
            return apology('Enter Valid number of shares!')

        shares = int(shares)

        if symbol == '':
            return apology('Share Symbol is required!')

        userid = session.get("user_id")

        # Placing Order
        return place_order(userid=userid, symbol=symbol, type=1, shares=shares)



    return render_template('buy.html')
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    userid = session.get("user_id")
    user = db.execute("SELECT username, cash FROM users WHERE id = ?", userid)[0]
    user_data = db.execute("SELECT * FROM transactions WHERE userid = ? ORDER BY time DESC", userid)

    # Setting 1 as Buy and -1 as Sell
    for i in range (0, len(user_data)):
        user_data[i]["price"] = float(user_data[i]["price"])
        if user_data[i]["type"] == 1:
            user_data[i]["type"] = "Buy"
        elif user_data[i]["type"] == -1:
            user_data[i]["type"] = "Sell"

    return render_template("history.html", user=user, user_data=user_data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == 'POST':
        symbol = request.form.get('symbol')
        data=lookup(symbol)
        if data == None:
            return apology("Don't type gibrish")
        userid = session.get("user_id")
        user = db.execute("SELECT username, cash FROM users WHERE id = ?", userid)[0]
        return render_template('quoted.html', user=user, data=data)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')

        if username == '':
            return apology("Username can not be blank !")
        if password == '':
            return apology("Password can not be blank !")
        if password != confirmation:
            return apology("Passwords do not match !")

        try:
            db.execute("INSERT into users (username, hash) VALUES (?, ?)", username, generate_password_hash(password))
            return redirect("/login")
        except ValueError as e:
            return apology("Username already exists !")


    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Checking which share boii got.
    userid = session.get("user_id")
    symbols = []
    existing_shares = db.execute('SELECT symbol FROM user_shares WHERE userid = ?', userid)
    print(existing_shares)
    for share in existing_shares:
        symbols.append(share["symbol"])

    if request.method == 'POST':
        symbol = request.form.get('symbol')
        shares = request.form.get('shares')

        share_count = db.execute('SELECT shares FROM user_shares WHERE userid = ? AND symbol = ?', userid, symbol)
        print(share_count)
        share_count = share_count[0]["shares"]
        print(share_count)

        if int(shares) > share_count:
            return apology("You don't have that many!!")

        # Validating Order
        if shares =='' or int(shares) < 0:
            return apology('Enter Valid number of shares !')
        shares = int(shares)

        if symbol == '':
            return apology('Share Symbol is required!')

        # Placing Order
        return place_order(userid=userid, symbol=symbol, type=-1, shares=shares)

    return render_template("sell.html", symbols=symbols)


'''
COMMANDS I USED IN sqlite3 DIRECTLY:

CREATE TABLE transactions (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, userid INTEGER NOT NULL,symbol TEXT NOT NULL, price TEXT NOT NULL,shares INTEGER NOT NULL,type INTEGER NOT NULL, time TEXT NOT NULL);
CREATE INDEX userid ON transactions (userid);

CREATE TABLE IF NOT EXISTS user_shares (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    userid INTEGER,
    symbol TEXT,
    shares INTEGER,
    price INTEGER,
    UNIQUE(userid, symbol)  -- To ensure no duplicate user-symbol combinations
);
CREATE INDEX userid ON user_shares (userid);
'''
