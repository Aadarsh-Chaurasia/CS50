-- In outer quiery getting the name of people that are star in movies (not kevin) that has id -
-- In inner queiry getting id of movies that have star that has id of person with name Kevin Bacon and birth year 1958


SELECT DISTINCT name FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE NOT people.name = 'Kevin Bacon'
AND movies.id in (
SELECT movies.id FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN people ON people.id = stars.person_id
WHERE people.name = 'Kevin Bacon' AND people.birth = 1958);
