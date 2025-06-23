-- Giving the user the default cash they have --
UPDATE users SET cash = 10000.00 WHERE id = 1;

-- Selecting the distinct symbols from a user's overall transaction
SELECT DISTINCT symbol FROM transactions;

-- Distinct symbol, shares
SELECT DISTINCT symbol, SUM(shares) FROM transactions GROUP BY symbol;
