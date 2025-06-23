import datetime
import uuid


from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

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


def query_curr_cash():
    spec_row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash = spec_row[0]["cash"]
    return cash


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
    session["cash"] = query_curr_cash()

    symbols = db.execute(
        "SELECT DISTINCT symbol, SUM(shares) AS shares FROM transactions GROUP BY symbol")
    total = session["cash"]
    indexes = []

    for symbol in symbols:
        if symbol["shares"] > 0:
            searched_symb = lookup(symbol["symbol"])
            searched_symb["shares"] = symbol["shares"]
            total += searched_symb["price"] * searched_symb["shares"]
            indexes.append(searched_symb)
        else:
            continue

    return render_template("index.html", indexes=indexes, cash=usd(session["cash"]), total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("missing symbol")
        elif not shares:
            return apology("missing shares")

        try:
            shares = int(shares)
        except ValueError:
            return apology("TODO")

        # if symbol and shares are filled
        searched_symb = lookup(symbol)

        if searched_symb == None:
            return apology("invalid symbol")
        elif shares < 1:
            return apology("invalid shares")

        # else, continue with submission
        total_price = searched_symb["price"] * shares
        aft_exp = session["cash"] - total_price  # cash after expense

        if aft_exp < 0:
            return apology("can't afford")

        session["cash"] -= total_price
        unique_id = str(uuid.uuid4())
        clock_now = datetime.datetime.now()

        db.execute("UPDATE users SET cash=? WHERE id=?", session["cash"], session["user_id"])

        # On uuid.uuid4() - https://www.geeksforgeeks.org/python/generating-random-ids-using-uuid-python/
        db.execute("INSERT INTO transactions (id, user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?, ?)",
                   unique_id, session["user_id"], symbol.upper(), shares, usd(searched_symb["price"]), "buy")

        db.execute("INSERT INTO date (transaction_id, month, day, year) VALUES (?, ?, ?, ?)",
                   unique_id, clock_now.month, clock_now.day, clock_now.year)

        return redirect("/")
    else:
        # do this
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_transactions = db.execute(
        "SELECT symbol, shares, price, month, day, year FROM transactions JOIN date ON transactions.id = date.transaction_id WHERE user_id = ?", session["user_id"])
    print(user_transactions)
    return render_template("history.html", user_transactions=user_transactions)


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
    if request.method == "POST":
        # do this
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("missing symbol")

        searched_symb = lookup(symbol)

        if searched_symb != None:
            # add parameters here
            return render_template("quoted.html", name=searched_symb["name"], price=usd(searched_symb["price"]), symbol=searched_symb["symbol"])

        return apology("invalid symbol")

    else:
        # do this
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # do this for POST method
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # if the fields are empty
        if not username:
            return apology("missing username")
        elif not password:
            return apology("missing password")

        # if no fields are empty...

        # check if password and confirmation matches
        if password != confirmation:
            return apology("passwords don't match")

        # check for username duplicates
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       username, generate_password_hash(password))
        except ValueError:
            return apology("username taken")

        return redirect("/register")
    else:
        # do this for GET method
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # returns symbols + shares
    symbols = db.execute(
        "SELECT DISTINCT symbol, SUM(shares) AS shares FROM transactions GROUP BY symbol")
    indexes = []

    for symbol in symbols:
        if symbol["shares"] > 0:
            indexes.append(symbol)  # append only when shares are greater than zero
        else:
            continue

    dist_symbols = db.execute("SELECT DISTINCT symbol FROM transactions")
    distinct_symbols = []  # list of distinct symbols for <option>

    for dist_symbol in dist_symbols:
        distinct_symbols.append(dist_symbol["symbol"])

    # code on method="post"
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("missing symbol")
        elif not shares:
            return apology("missing shares")

        if symbol not in distinct_symbols:
            return apology("symbol not owned")

        try:
            shares = int(shares)
        except ValueError:
            return apology("invalid shares")

        if shares < 1:
            return apology("shares must be positive")

        searched_symb = lookup(symbol)

        for i in indexes:
            if i.get("symbol") == str(symbol):
                searched_symb["shares"] = i.get("shares")
                break

        if shares > searched_symb["shares"]:
            return apology("too many shares")

        session["cash"] += searched_symb["price"] * shares
        unique_id = str(uuid.uuid4())
        clock_now = datetime.datetime.now()

        # success indicator
        db.execute("INSERT INTO transactions (id, user_id, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?, ?)",
                   unique_id, session["user_id"], symbol.upper(), -shares, usd(searched_symb["price"]), "sell")

        db.execute("INSERT INTO date (transaction_id, month, day, year) VALUES (?, ?, ?, ?)",
                   unique_id, clock_now.month, clock_now.day, clock_now.year)

        db.execute("UPDATE users SET cash=?", session["cash"])

        return redirect("/")
    else:
        return render_template("sell.html", indexes=indexes)


"""
Note:
Triple quoted strings are used as comment by many developers but it is actually not a comment,
it is similar to regular strings in python but it allows the string to be in multi-line. You
will find no official reference for triple quoted strings to be a comment.
"""


@app.route("/changepass", methods=["GET", "POST"])
@login_required
def editpfp():
    if request.method == "POST":
        new_password = request.form.get("new_password")

        if not new_password:
            return apology("missing password")

        new_hash = generate_password_hash(new_password)

        db.execute("UPDATE users SET hash=? WHERE id=?", new_hash, session["user_id"])

        # success indicator
        return redirect("/")
    else:
        return render_template("changepass.html")
