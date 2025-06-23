from cs50 import SQL
from flask import Flask, redirect, render_template, request
# add jsonify

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Solve this problem


def validate_input(name, month, day):
    valid_months = range(1, 13)
    valid_days = range(1, 31)

    # Ensure month and day are not of 'NoneType'
    if not name or not month or not day:
        return False

    # Try and except test
    try:
        month = int(month)  # flagged as problem
    except ValueError:
        return False
    try:
        day = int(day)
    except ValueError:
        return False

    # Parsing input with try and catch -- and passed
    # Check if month / day are within valid values
    if (month in valid_months) and (day in valid_days):
        return True

    return False

# supports GET and POST methods


@app.route("/", methods=["GET", "POST"])
def index():
    # on post method
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # validate the input
        if validate_input(name, month, day):
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        return redirect("/")

    else:
        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)


@app.route("/modify_mode", methods=["POST"])
def modify_mode():
    name = request.form.get("name")
    month = request.form.get("month")
    day = request.form.get("day")

    edit = request.form.get("edit")
    delete = request.form.get("delete")

    # validate input first
    if validate_input(name, month, day):
        if delete:
            db.execute("DELETE FROM birthdays WHERE name LIKE ? AND month=? AND day=?", name, month, day)
        elif edit:
            db.execute("UPDATE birthdays SET month=?, day=? WHERE name=?", month, day, name)

    birthdays = db.execute("SELECT * FROM birthdays")
    return render_template("modify_mode.html", birthdays=birthdays)
