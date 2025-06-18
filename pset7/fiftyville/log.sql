-- Keep a log of any SQL queries you execute as you solve the mystery.

-- To check format of street names
SELECT street
    FROM crime_scene_reports
    LIMIT 10;

-- To get a detailed description of the crime report for July 28, 2024
SELECT description
    FROM crime_scene_reports
    WHERE month = 7 AND day = 28 AND year = 2024;

-- To check the transcripts of interviews conducted on July 28, 2024
SELECT name, transcript
    FROM interviews
    WHERE month = 7 AND day = 28 AND year = 2024;

-- To check all the cars that left the bakery's parking lot from 10:15 am to 10:25 am
SELECT hour, minute, license_plate, activity
    FROM bakery_security_logs
    WHERE month = 7 AND day = 28 AND year = 2024
    AND hour = 10 AND (minute >= 15 AND minute <= 25);

-- To check the table for atm_transactions
SELECT *
    FROM atm_transactions
    LIMIT 10;

-- To check withdrawals in Legett Street on July 28, 2024
SELECT account_number, atm_location, transaction_type, amount
    FROM atm_transactions
    WHERE month = 7 AND day = 28 AND year = 2024
    AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';

-- To check for less than a minute phone calls on July 28, 2024
SELECT caller, receiver, duration
    FROM phone_calls
    WHERE month = 7 AND day = 28 AND year = 2024
    AND duration <= 60;

-- Practicing syntax for larger query
SELECT name, account_number
    FROM people
    JOIN bank_accounts
    ON people.id = bank_accounts.person_id
    LIMIT 10;

-- To check WHO did the withdrawals as previously searched for narrowing down purposes
SELECT name, account_number, phone_number, license_plate
    FROM people
    JOIN bank_accounts
    ON people.id = bank_accounts.person_id

    WHERE account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE month = 7 AND day = 28 AND year = 2024
        AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');

-- To narrow the suspects list more
SELECT name, account_number, phone_number, license_plate
    FROM people
    JOIN bank_accounts
    ON people.id = bank_accounts.person_id

    WHERE (account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE month = 7 AND day = 28 AND year = 2024
        AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')

    AND license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND year = 2024
        AND hour = 10 AND (minute >= 15 AND minute <= 25))

    AND phone_number IN
        (SELECT caller
        FROM phone_calls
        WHERE month = 7 AND day = 28 AND year = 2024
        AND duration <= 60));

-- Results narrow down to Bruce and Diana

-- Check for airport names in Fiftyville
SELECT full_name FROM airports WHERE full_name LIKE 'Fiftyville%';
SELECT full_name FROM airports WHERE city = 'Fiftyville';

-- Check for destination of flights where the origin is Fiftyville
-- full_name pertains to airport destination from Fiftyville
SELECT month, day, year, hour, minute, full_name, city, flights.id
    FROM flights
    JOIN airports
    ON airports.id = flights.destination_airport_id

    WHERE origin_airport_id = (SELECT id FROM airports
        WHERE city = 'Fiftyville') AND
        month = 7 AND day = 29 AND year = 2024
        ORDER BY hour, minute ASC;
-- add LIMIT 1
-- To check who hopped on a flight (most likely earliest possible) away from Fiftyville
SELECT name FROM people
    WHERE passport_number IN (SELECT passport_number FROM passengers
    WHERE flight_id = (SELECT flights.id FROM flights
    JOIN airports
    ON airports.id = flights.destination_airport_id

        WHERE origin_airport_id = (SELECT id FROM airports
        WHERE city = 'Fiftyville') AND
        month = 7 AND day = 29 AND year = 2024
        ORDER BY hour, minute ASC));

-- Narrowing suspects using passport_number
SELECT name, account_number, phone_number, license_plate, passport_number
    FROM people
    JOIN bank_accounts
    ON people.id = bank_accounts.person_id

    WHERE (account_number IN
        (SELECT account_number
        FROM atm_transactions
        WHERE month = 7 AND day = 28 AND year = 2024
        AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')

    AND license_plate IN
        (SELECT license_plate
        FROM bakery_security_logs
        WHERE month = 7 AND day = 28 AND year = 2024
        AND hour = 10 AND (minute >= 15 AND minute <= 25))

    AND phone_number IN
        (SELECT caller
        FROM phone_calls
        WHERE month = 7 AND day = 28 AND year = 2024
        AND duration <= 60)

    AND passport_number IN
        (SELECT passport_number FROM passengers
        WHERE flight_id = (SELECT flights.id FROM flights
        JOIN airports
        ON airports.id = flights.destination_airport_id

        WHERE origin_airport_id = (SELECT id FROM airports
        WHERE city = 'Fiftyville') AND
        month = 7 AND day = 29 AND year = 2024
        ORDER BY hour, minute ASC)));

-- Find out the city the thief escaped to
SELECT full_name, city
    FROM airports
    JOIN flights
    ON airports.id = flights.destination_airport_id

    WHERE (origin_airport_id = (SELECT id FROM airports
        WHERE city = 'Fiftyville' AND
        month = 7 AND day = 29 AND year = 2024)

    AND flights.id = (SELECT flight_id FROM passengers
    WHERE passport_number = (SELECT passport_number FROM
    people WHERE name = 'Bruce')));

-- Find out who the thief accomplice is...
SELECT name FROM people
    WHERE phone_number = (SELECT receiver FROM phone_calls
    WHERE caller = (SELECT phone_number FROM people
    WHERE name = 'Bruce')
    AND month = 7 AND day = 28 AND year = 2024
    AND duration <= 60);

-- had an initial error where it returns the first call logged by Bruce hehe
