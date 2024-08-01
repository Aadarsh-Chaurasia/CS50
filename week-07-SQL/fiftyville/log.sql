-- -- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking out the structure of database
.tables

-- Checking out the crime schene
.schema crime_scene_report

SELECT street, description
  FROM crime_scene_reports
  WHERE year = 2023 AND month = 7 AND day = 28;

-- INFO FOUND :
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.

-- -- CHECKING OUT THE INTERVIEWS
SELECT name,transcript FROM interviews
  WHERE year = 2023 AND month = 7 AND day = 28;

-- CONCLUSION
-- time : 10:15 to 10:25
-- Used atm on 28/07/23
-- Called someone and talked less then a minute.
-- On first flight next day (29/07/23) from Fiftyville


-- CREATING NEW TABLE TO STORE THE SUSPECTS
-- It'll have field name and atAtm and atFlight.
CREATE TABLE sus (
    id INTEGER,
    name TEXT,
    phone_number INTEGER,
    passport_number INTEGER,
    account_number INTEGER
);

WITH sus_plate AS (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2023 AND month = 7 AND day = 28
    AND activity = 'exit' AND hour = 10 AND minute >= 15 AND minute <= 25
    ORDER BY minute
)
INSERT INTO sus (id, name, phone_number, passport_number, account_number)
SELECT id, name,phone_number, passport_number, account_number FROM people  JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE license_plate IN sus_plate;



-- FLAGGING THE SUSPECTS THAT CALLED THAT DAY.
ALTER TABLE sus ADD COLUMN onCall TEXT;

UPDATE sus
SET onCAll = 'yes'
WHERE name IN (
  SELECT DISTINCT name FROM sus join phone_calls on sus.phone_number = phone_calls.caller
  WHERE year = 2023 AND month = 7 AND day = 28
);



-- ADDING A CLOUMN IN SUS TABLE ONFLIGHT THAT FLAGS THE SUSPECTS THAT WERE ON FLIGHT AFTER THE THIEFT
-- KEY POINT : First Flight on 29 July 2023 from Fiftyville
ALTER TABLE sus ADD COLUMN onFlight TEXT;

UPDATE sus
SET onFlight = 'yes'
WHERE name IN (
  SELECT DISTINCT name FROM sus
  JOIN passengers ON passengers.passport_number = sus.passport_number
  JOIN flights ON passengers.flight_id = flights.id
  where flights.id in (
    select flights.id from flights
    JOIN airports ON flights.origin_airport_id = airports.id
    WHERE airports.city = 'Fiftyville'
    AND flights.year = 2023
    AND flights.month = 7 AND flights.day = 29
    ORDER BY month, day, hour, minute
    LIMIT 1
  )
);


-- ADDING A CLOUMN IN SUS TABLE atATM THAT FLAGS THE SUSPECTS THAT WERE AT ATM THAT DAY
ALTER TABLE sus ADD COLUMN atATM TEXT;

UPDATE sus
SET atATM = 'yes'
WHERE name IN (
  SELECT DISTINCT name FROM sus
  JOIN atm_transactions ON sus.account_number = atm_transactions.account_number
  WHERE year = 2023 AND month = 7 AND day = 28
  AND atm_location = "Leggett Street"
  AND transaction_type = "withdraw"
);


-- CATCHING THE THIEF
-- Thief will have onCall, atATM, onFlight all 3 as yes !
SELECT name FROM sus
  WHERE onCall = 'yes'
  AND atATM = 'yes'
  AND onFlight = 'yes';

-- ### Thief is Bruce ###


-- Checking whom did Bruce called that day.

SELECT DISTINCT name FROM people
WHERE people.phone_number in
(
  SELECT receiver FROM phone_calls
  JOIN people ON people.phone_number = phone_calls.caller
  WHERE year = 2023 AND month = 7 AND day = 28
  AND people.name = 'Bruce'
  AND duration < 60
);

-- ### Bruce called Robin for less then a minute ####

SELECT city FROM airports
WHERE airports.id in (
  SELECT destination_airport_id FROM flights
    WHERE flights.id in
      (
        SELECT flight_id FROM passengers
        JOIN people ON people.passport_number = passengers.passport_number
        WHERE people.name = 'Bruce'
      )
);

-- ### Bruce escaped to New York City ####

-- REMOVING sus TABLE FROM ORIGINAL FILE
DROP TABLE sus;
