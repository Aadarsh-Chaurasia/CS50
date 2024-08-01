-- query to list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred.

-- select title from movies join stars on movies.id = stars.movie_id join people on stars.person_id = people.id where people.name = 'Bradley Cooper' and people.name = 'Jennifer Lawrence';
-- This will not work because we are checking 2 names for same person.

-- using GROUP BY and HAVING

SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name IN ('Bradley Cooper','Jennifer Lawrence')
GROUP BY movies.id
HAVING count(DISTINCT people.name) >=2;
